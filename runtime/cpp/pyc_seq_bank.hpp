#pragma once

#include <cstdint>
#include <vector>

#include "pyc_bits.hpp"

namespace pyc::cpp {

// SeqBank: a per-clock-domain bank of registers that share storage layout and
// a single generated update loop, WITHOUT merging their values in the IR.
//
// Motivation (measured, DavinciTop 34 traces, paired runs):
//  - packing regs into one wide storage is a large win (-48.8% when packing
//    disabled; +6.2% when the cap widens 192 -> 1024), but it merges logical
//    state, coarsens the change-driven dirty granularity to 64-bit words, and
//    needs slice-alias plumbing for probes.
//  - the actual per-reg costs SeqBank removes are the same ones packing
//    removes: per-reg straight-line code in tick_compute/tick_commit
//    (I-cache), scattered q/qNext storage, one commit branch + fanout-mark
//    per reg, and per-object scheduler bookkeeping.
//
// Semantics contract (matches pyc_reg<W> exactly):
//  - compute_rise()    == pyc_reg::posedge_tick_compute() for every lane
//  - compute_generic() == pyc_reg::tick_compute() for every lane
//  - negedge()         == pyc_reg::negedge_update() for every lane
//  - commit()          == pyc_reg::tick_commit() for every lane; returns a
//    per-lane dirty bitmap so the change-driven fanout wake stays exactly as
//    precise as the per-reg path (no word-granularity false wakes).
//
// `q` stays the caller-owned Wire<W> (the model struct member), so comb
// reads, probe registry addWire/addReg, trace and VCD paths need zero
// adaptation.

template <unsigned Width>
struct SeqBankLane {
  Wire<Width> *q;
  Wire<Width> *d;
  Wire<1> *rst;
  Wire<1> *en;
  const Wire<Width> *init;
};

template <unsigned Width>
class SeqBank {
  static_assert(Width > 0, "SeqBank requires Width > 0");

public:
  using Lane = SeqBankLane<Width>;

  template <typename... More>
  void add_lane(Lane lane, More... more) {
    lanes_.push_back(lane);
    qNext_.emplace_back();
    pending_.push_back(0);
    dirty_.assign(word_count(lanes_.size()), 0);
    if constexpr (sizeof...(more) > 0)
      add_lane(more...);
  }

  // Bulk form used by generated code: add_lanes({a,b,c,d,e}, {f,g,h,i,j}).
  void add_lanes(std::initializer_list<Lane> lanes) {
    for (const Lane &lane : lanes)
      add_lane(lane);
  }

  std::size_t size() const { return lanes_.size(); }

  // Caller guarantees a 0->1 edge just occurred on this bank's clock.
  void compute_rise() {
    clkPrev_ = true;
    const std::size_t n = lanes_.size();
    for (std::size_t i = 0; i < n; ++i) {
      const Lane &lane = lanes_[i];
      const bool r = lane.rst->toBool();
      const bool e = lane.en->toBool();
      pending_[i] = static_cast<char>(r | e);
      if (r)
        qNext_[i] = *lane.init;
      else
        qNext_[i] = *lane.d;
    }
  }

  // Generic path: caller only knows the current clock level.
  void compute_generic(bool clkNow) {
    const bool posedge = (!clkPrev_) & clkNow;
    clkPrev_ = clkNow;
    if (__builtin_expect(!posedge, 1)) {
      clear_pending();
      return;
    }
    compute_rise();
  }

  // Falling edge bookkeeping: next compute must re-detect the edge.
  void negedge() { clkPrev_ = false; clear_pending(); }

  // Applies pending updates, writes back through the lane's q pointer, and
  // returns the per-lane dirty bitmap (bit i set == lane i's visible q
  // changed this commit). Bitmap has one bit per lane, packed into 64-bit
  // words; consumers index it with the lane index.
  const std::vector<std::uint64_t> &commit() {
    const std::size_t n = lanes_.size();
    dirty_.assign(word_count(n), 0);
    for (std::size_t i = 0; i < n; ++i) {
      if (__builtin_expect(pending_[i] != 0, 0)) {
        Wire<Width> &q = *lanes_[i].q;
        const bool changed = q != qNext_[i];
        q = qNext_[i];
        pending_[i] = false;
        if (changed)
          dirty_[i >> 6] |= std::uint64_t{1} << (i & 63);
      }
    }
    return dirty_;
  }

  static constexpr std::size_t word_count(std::size_t lanes) {
    return (lanes + 63) / 64;
  }

  // Probe/trace write-intent bindings: stable addresses for lane i's
  // pending flag and sampled next value (mirror pyc_reg::pending/qNext).
  // pending_ stores char with values exactly 0/1; on the Itanium ABI bool
  // is one byte with the same object representation, so the pointer stays a
  // valid probe write-intent flag (consumers only test truthiness).
  bool *lane_pending(std::size_t i) {
    return reinterpret_cast<bool *>(&pending_[i]);
  }
  Wire<Width> *lane_qnext(std::size_t i) { return &qNext_[i]; }

private:
  void clear_pending() { pending_.assign(lanes_.size(), 0); }

  std::vector<Lane> lanes_;
  std::vector<Wire<Width>> qNext_;
  std::vector<char> pending_;   // char (not vector<bool>) so lanes expose stable addresses
  std::vector<std::uint64_t> dirty_;
  bool clkPrev_ = false;
};

}  // namespace pyc::cpp
