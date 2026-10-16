#pragma once

#include <cstdint>
#include <vector>

#include "pyc_bits.hpp"

namespace pyc::cpp {

// DelayBank: per-clock-domain bank of pyc_delay_line instances sharing one
// generated update loop, WITHOUT merging their values in the IR.
//
// Mirrors SeqBank's contract against pyc_delay_line:
//   compute_rise()    == pyc_delay_line::posedge_tick_compute()
//   compute_generic() == pyc_delay_line::tick_compute()
//   negedge()         == pyc_delay_line::negedge_update()
//   commit()          == pyc_delay_line::tick_commit(); two per-lane
//     bitmaps are returned: tail-dirty (q changed) and advanced (pending —
//     every enabled edge shifts every tap, so tap consumers wake on it).
//
// Per-lane Depth varies, so stage storage is per-lane vectors and the ring
// index is per-lane state; everything else is bank-continuous.

template <unsigned Width>
struct DelayBankLane {
  Wire<Width> *q;
  Wire<Width> *d;
  Wire<1> *rst;
  Wire<1> *en;
  const Wire<Width> *init;
  unsigned depth;  // verifier-guaranteed > 1
};

template <unsigned Width>
class DelayBank {
public:
  using Lane = DelayBankLane<Width>;

  void add_lane(Lane lane) {
    lanes_.push_back(lane);
    stages_.emplace_back(lane.depth);
    head_.push_back(0);
    sampled_.emplace_back();
    qNext_.emplace_back();
    pendingReset_.push_back(false);
    pending_.push_back(0);
    dirty_.assign(word_count(lanes_.size()), 0);
    advanced_.assign(word_count(lanes_.size()), 0);
  }

  // Bulk form used by generated code.
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
      pendingReset_[i] = r;
      pending_[i] = static_cast<char>(r | e);
      if (r)
        qNext_[i] = *lane.init;
      else if (e) {
        sampled_[i] = *lane.d;
        qNext_[i] = stages_[i][next_head(i, lane.depth)];
      }
    }
  }

  void compute_generic(bool clkNow) {
    const bool posedge = (!clkPrev_) & clkNow;
    clkPrev_ = clkNow;
    if (__builtin_expect(!posedge, 1)) {
      clear_pending();
      return;
    }
    compute_rise();
  }

  void negedge() { clkPrev_ = false; clear_pending(); }

  // Applies pending edges; returns {tail_dirty, advanced} bitmaps. `advanced`
  // has a bit set for every lane whose history advanced this commit (tap
  // consumers wake on it), matching has_pending() per-lane.
  struct CommitResult {
    const std::vector<std::uint64_t> &tailDirty;
    const std::vector<std::uint64_t> &advanced;
  };

  CommitResult commit() {
    const std::size_t n = lanes_.size();
    dirty_.assign(word_count(n), 0);
    advanced_.assign(word_count(n), 0);
    for (std::size_t i = 0; i < n; ++i) {
      if (__builtin_expect(pending_[i] != 0, 0)) {
        const Lane &lane = lanes_[i];
        Wire<Width> &q = *lane.q;
        const bool changed = q != qNext_[i];
        if (pendingReset_[i]) {
          for (unsigned s = 0; s < lane.depth; ++s)
            stages_[i][s] = *lane.init;
          head_[i] = 0;
        } else {
          stages_[i][head_[i]] = sampled_[i];
          head_[i] = next_head(i, lane.depth);
        }
        q = qNext_[i];
        pending_[i] = 0;
        advanced_[i >> 6] |= std::uint64_t{1} << (i & 63);
        if (changed)
          dirty_[i >> 6] |= std::uint64_t{1} << (i & 63);
      }
    }
    return CommitResult{dirty_, advanced_};
  }

  // Probe write-intent bindings (mirror pyc_delay_line::pending/qNext).
  bool *lane_pending(std::size_t i) {
    return reinterpret_cast<bool *>(&pending_[i]);
  }
  Wire<Width> *lane_qnext(std::size_t i) { return &qNext_[i]; }
  // Lightweight per-lane tap view: satisfies the DelayInst interface used by
  // ProbeRegistry::addRegLazyTap* (tap(depth) / has_pending() / pending /
  // qNext members). Hold by value in generated probe registration code.
  struct TapView {
    const DelayBank *bank;
    std::size_t lane;
    Wire<Width> tap(unsigned depth) const { return bank->tap(lane, depth); }
    bool has_pending() const { return bank->pending_[lane] != 0; }
    bool *pending_ptr() const {
      return reinterpret_cast<bool *>(const_cast<char *>(&bank->pending_[lane]));
    }
    const Wire<Width> *qnext() const { return &bank->qNext_[lane]; }
  };

  TapView tap_view(std::size_t i) const { return TapView{this, i}; }

  // Committed tap read for lane i (mirror pyc_delay_line::tap).
  Wire<Width> lane_tap(std::size_t i, unsigned depth) const {
    return tap(i, depth);
  }

  // tap_next for per-tap _qNext wires: recompute exactly like
  // pyc_delay_line::tap_next for lane i.
  Wire<Width> lane_tap_next(std::size_t i, unsigned depth) const {
    const Lane &lane = lanes_[i];
    if (pendingReset_[i])
      return *lane.init;
    if (!pending_[i])
      return tap(i, depth);
    return depth == 1 ? sampled_[i] : tap(i, depth - 1);
  }

  static constexpr std::size_t word_count(std::size_t lanes) {
    return (lanes + 63) / 64;
  }

private:
  Wire<Width> tap(std::size_t i, unsigned depth) const {
    // Caller passes 1..Depth (verifier-guaranteed); ring layout matches
    // pyc_delay_line::stages/head.
    unsigned idx = head_[i] + lanes_[i].depth - depth;
    if (idx >= lanes_[i].depth)
      idx -= lanes_[i].depth;
    return stages_[i][idx];
  }
  unsigned next_head(std::size_t i, unsigned depth) const {
    unsigned h = head_[i] + 1u;
    return h == depth ? 0u : h;
  }
  void clear_pending() { pending_.assign(lanes_.size(), 0); }

  std::vector<Lane> lanes_;
  std::vector<std::vector<Wire<Width>>> stages_;
  std::vector<unsigned> head_;
  std::vector<Wire<Width>> sampled_;
  std::vector<Wire<Width>> qNext_;
  std::vector<char> pending_;        // 0/1, stable address via lane_pending
  std::vector<char> pendingReset_;   // 0/1
  std::vector<std::uint64_t> dirty_;
  std::vector<std::uint64_t> advanced_;
  bool clkPrev_ = false;
};

// VecBank: SeqBank generalized to vector-element registers (pyc_vec_reg<T>).
// T is the element type (e.g. Vec<8,4>); semantics identical to SeqBank.
template <typename T>
class VecBank {
public:
  struct Lane {
    T *q;
    T *d;
    Wire<1> *rst;
    Wire<1> *en;
    const T *init;
  };

  void add_lane(Lane lane) {
    lanes_.push_back(lane);
    qNext_.emplace_back();
    pending_.push_back(0);
    dirty_.assign(word_count(lanes_.size()), 0);
  }

  std::size_t size() const { return lanes_.size(); }

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

  void compute_generic(bool clkNow) {
    const bool posedge = (!clkPrev_) & clkNow;
    clkPrev_ = clkNow;
    if (__builtin_expect(!posedge, 1)) {
      clear_pending();
      return;
    }
    compute_rise();
  }

  void negedge() { clkPrev_ = false; clear_pending(); }

  const std::vector<std::uint64_t> &commit() {
    const std::size_t n = lanes_.size();
    dirty_.assign(word_count(n), 0);
    for (std::size_t i = 0; i < n; ++i) {
      if (__builtin_expect(pending_[i] != 0, 0)) {
        T &q = *lanes_[i].q;
        const bool changed = q != qNext_[i];
        q = qNext_[i];
        pending_[i] = 0;
        if (changed)
          dirty_[i >> 6] |= std::uint64_t{1} << (i & 63);
      }
    }
    return dirty_;
  }

  bool *lane_pending(std::size_t i) {
    return reinterpret_cast<bool *>(&pending_[i]);
  }
  T *lane_qnext(std::size_t i) { return &qNext_[i]; }

  static constexpr std::size_t word_count(std::size_t lanes) {
    return (lanes + 63) / 64;
  }

private:
  void clear_pending() { pending_.assign(lanes_.size(), 0); }

  std::vector<Lane> lanes_;
  std::vector<T> qNext_;
  std::vector<char> pending_;
  std::vector<std::uint64_t> dirty_;
  bool clkPrev_ = false;
};

}  // namespace pyc::cpp
