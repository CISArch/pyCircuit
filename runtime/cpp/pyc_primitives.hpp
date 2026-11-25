#pragma once

#include <cstdint>

#include "pyc_bits.hpp"
#include "pyc_clock.hpp"
#include "pyc_component.hpp"

namespace pyc::cpp {

// "Module-like" primitives that mirror the Verilog templates in
// `runtime/verilog/` (same names, same port names).
//
// These are intended as stable building blocks for generated C++ cycle-accurate
// models.

template <unsigned Width>
struct pyc_add {
  Wire<Width> &a;
  Wire<Width> &b;
  Wire<Width> &y;

  void eval() { y = a + b; }
};

template <unsigned Width>
struct pyc_mux {
  Wire<1> &sel;
  Wire<Width> &a;
  Wire<Width> &b;
  Wire<Width> &y;

  void eval() { y = sel.toBool() ? a : b; }
};

template <unsigned Width>
struct pyc_and {
  Wire<Width> &a;
  Wire<Width> &b;
  Wire<Width> &y;

  void eval() { y = a & b; }
};

template <unsigned Width>
struct pyc_or {
  Wire<Width> &a;
  Wire<Width> &b;
  Wire<Width> &y;

  void eval() { y = a | b; }
};

template <unsigned Width>
struct pyc_xor {
  Wire<Width> &a;
  Wire<Width> &b;
  Wire<Width> &y;

  void eval() { y = a ^ b; }
};

template <unsigned Width>
struct pyc_not {
  Wire<Width> &a;
  Wire<Width> &y;

  void eval() { y = ~a; }
};

// Register semantics shared by pycReg (scalar) and pycVecReg (vector): the
// two differ only in the value type, so staging/publish lives here once and the
// leaves are 0-line derivations that keep their generated constructor signature.
// The edge protocol lives in ClockedElement; derived classes supply sample().
template <class ValT>
class RegBase : public ClockedElement<RegBase<ValT>> {
  using Base = ClockedElement<RegBase<ValT>>;
  using change_mask_t = typename Base::change_mask_t;

public:
  RegBase() = default;
  RegBase(Wire<1> &clk, Wire<1> &rst, Wire<1> &en, ValT &d, ValT &init, ValT &q) {
    bind(clk, rst, en, d, init, q);
  }

  // One-shot wiring: the generated module declares this as a value member and
  // binds every port (clock included) in its constructor body.
  void bind(Wire<1> &clk, Wire<1> &rst, Wire<1> &en, ValT &d, ValT &init, ValT &q) {
    this->bind_clock(clk);
    this->rst.set(rst);
    this->en.set(en);
    this->d.set(d);
    this->init.set(init);
    this->q.set(q);
  }

  bool bound() const {
    return this->clk.bound() && rst.bound() && en.bound() && d.bound() &&
           init.bound() && q.bound();
  }

  // Applies a pending edge and reports whether the visible output changed.
  inline change_mask_t tick_commit() {
    if (__builtin_expect(!this->pending, 1))
      return 0;
    this->pending = false;
    ValT &q = this->q.get();
    const bool changed = q != qNext;
    if (changed)
      q = qNext;
    return changed ? Base::kChanged : change_mask_t{0};
  }

  bool sample() {
    const bool r = this->rst.get().toBool();
    const bool e = this->en.get().toBool();
    if (r)
      qNext = this->init.get();
    else
      qNext = this->d.get();
    return r | e;
  }

  Ref<Wire<1>> rst;
  Ref<Wire<1>> en;
  Ref<ValT> d;
  Ref<ValT> init;
  Ref<ValT> q;

  ValT qNext{};
};

template <unsigned Width>
class pycReg : public RegBase<Wire<Width>> {
  using Base = RegBase<Wire<Width>>;

public:
  using Base::Base;
};

template <typename T>
class pycVecReg : public RegBase<T> {
  using Base = RegBase<T>;

public:
  using Base::Base;
};

// Simulator representation of DEPTH cascaded registers. A circular buffer
// makes the normal enabled edge O(1); reset still initializes every stage so
// reset/enable and compute-before-commit semantics match pycReg chains.
template <class ValT, unsigned Depth>
class DelayBase : public ClockedElement<DelayBase<ValT, Depth>> {
  using Base = ClockedElement<DelayBase<ValT, Depth>>;
  using change_mask_t = typename Base::change_mask_t;

  static_assert(Depth > 1, "DelayBase requires Depth > 1");

public:
  DelayBase() = default;
  DelayBase(Wire<1> &clk, Wire<1> &rst, Wire<1> &en, ValT &d, ValT &init,
            ValT &q) {
    bind(clk, rst, en, d, init, q);
  }

  // One-shot wiring (see RegBase::bind).
  void bind(Wire<1> &clk, Wire<1> &rst, Wire<1> &en, ValT &d, ValT &init, ValT &q) {
    this->bind_clock(clk);
    this->rst.set(rst);
    this->en.set(en);
    this->d.set(d);
    this->init.set(init);
    this->q.set(q);
  }

  bool bound() const {
    return this->clk.bound() && rst.bound() && en.bound() && d.bound() &&
           init.bound() && q.bound();
  }

  // True while an enabled edge is waiting for tick_commit. Tap consumers must
  // wake on this (every enabled edge shifts every tap).
  inline bool has_pending() const { return this->pending; }

  // Applies a pending edge and reports whether the tail q changed; tap
  // consumers wake via has_pending() instead (see the scalar note above).
  inline change_mask_t tick_commit() {
    if (__builtin_expect(!this->pending, 1))
      return 0;
    ValT &q = this->q.get();
    const bool changed = q != qNext;
    if (pendingReset) {
      stages.fill(this->init.get());
      head = 0;
    } else {
      stages[head] = sampledInput;
      head = nextIndex(head);
    }
    q = qNext;
    this->pending = false;
    return changed ? Base::kChanged : change_mask_t{0};
  }

  inline ValT tap(unsigned depth) const {
    return stages[(head + Depth - depth) % Depth];
  }

  inline ValT tap_next(unsigned depth) const {
    if (pendingReset)
      return this->init.get();
    if (!this->pending)
      return tap(depth);
    return depth == 1 ? sampledInput : tap(depth - 1);
  }

  bool sample() {
    pendingReset = this->rst.get().toBool();
    const bool enabled = this->en.get().toBool();
    if (pendingReset) {
      qNext = this->init.get();
      return true;
    }
    if (enabled) {
      sampledInput = this->d.get();
      qNext = stages[nextIndex(head)];
    }
    return enabled;
  }

  Ref<Wire<1>> rst;
  Ref<Wire<1>> en;
  Ref<ValT> d;
  Ref<ValT> init;
  Ref<ValT> q;
  bool pendingReset = false;
  ValT qNext{};
  ValT sampledInput{};
  std::array<ValT, Depth> stages{};
  unsigned head = 0;

private:
  static constexpr unsigned nextIndex(unsigned index) {
    return index + 1u == Depth ? 0u : index + 1u;
  }
};

template <unsigned Width, unsigned Depth>
class pycDelayLine : public DelayBase<Wire<Width>, Depth> {
  using Base = DelayBase<Wire<Width>, Depth>;

public:
  using Base::Base;
};

template <typename T, unsigned Depth>
class pycVecDelayLine : public DelayBase<T, Depth> {
  using Base = DelayBase<T, Depth>;

public:
  using Base::Base;
};

template <unsigned Width, unsigned Depth>
class pycFifo : public ClockedElement<pycFifo<Width, Depth>> {
public:
  using change_mask_t = BaseElement::change_mask_t;

  // Bit numbers of the three visible outputs (rule: i-th output -> bit i).
  static constexpr change_mask_t kInReadyChanged = BaseElement::change_bit(0);
  static constexpr change_mask_t kOutValidChanged = BaseElement::change_bit(1);
  static constexpr change_mask_t kOutDataChanged = BaseElement::change_bit(2);

  pycFifo() = default;
  pycFifo(Wire<1> &clk,
           Wire<1> &rst,
           Wire<1> &in_valid,
           Wire<1> &in_ready,
           Wire<Width> &in_data,
           Wire<1> &out_valid,
           Wire<1> &out_ready,
           Wire<Width> &out_data) {
    bind(clk, rst, in_valid, in_ready, in_data, out_valid, out_ready, out_data);
  }

  // One-shot wiring (see RegBase::bind): resets the storage and publishes the
  // initial combinational ready/valid state, as the eager constructor did.
  void bind(Wire<1> &clk,
            Wire<1> &rst,
            Wire<1> &in_valid,
            Wire<1> &in_ready,
            Wire<Width> &in_data,
            Wire<1> &out_valid,
            Wire<1> &out_ready,
            Wire<Width> &out_data) {
    static_assert(Depth > 0, "pycFifo Depth must be > 0");
    this->bind_clock(clk);
    this->rst.set(rst);
    this->in_valid.set(in_valid);
    this->in_ready.set(in_ready);
    this->in_data.set(in_data);
    this->out_valid.set(out_valid);
    this->out_ready.set(out_ready);
    this->out_data.set(out_data);
    resetState();
    eval();
  }

  static constexpr unsigned depth() { return Depth; }
  unsigned debug_count() const { return count_; }
  unsigned debug_rd_ptr() const { return rd_; }
  unsigned debug_wr_ptr() const { return wr_; }

  // Combinational ready/valid generation.
  void eval() {
    Wire<1> &in_ready = this->in_ready.get();
    Wire<1> &out_valid = this->out_valid.get();
    Wire<Width> &out_data = this->out_data.get();
    const bool outReadyNow = this->out_ready.get().toBool();
    Wire<Width> out_data_int = (count_ != 0) ? storage_[rd_] : Wire<Width>(0);
    if (evalValid_ && lastEvalCount_ == count_ && lastEvalRd_ == rd_ && lastEvalOutReady_ == outReadyNow &&
        lastEvalOutData_ == out_data_int)
      return;

    bool out_valid_int = (count_ != 0);
    bool in_ready_int = (count_ < Depth) || (out_valid_int && outReadyNow);

    in_ready = Wire<1>(in_ready_int ? 1u : 0u);
    out_valid = Wire<1>(out_valid_int ? 1u : 0u);
    out_data = out_data_int;

    evalValid_ = true;
    lastEvalCount_ = count_;
    lastEvalRd_ = rd_;
    lastEvalOutReady_ = outReadyNow;
    lastEvalOutData_ = out_data_int;
  }

  void tick_sample() {
    Wire<1> &rst = this->rst.get();
    Wire<1> &in_valid = this->in_valid.get();
    Wire<Width> &in_data = this->in_data.get();
    const bool out_ready_now = this->out_ready.get().toBool();
    pending = true;
    if (rst.toBool()) {
      rdNext_ = 0;
      wrNext_ = 0;
      countNext_ = 0;
      for (unsigned i = 0; i < Depth; ++i)
        storageNext_[i] = Wire<Width>(0);
      return;
    }

    // Start from the current state.
    rdNext_ = rd_;
    wrNext_ = wr_;
    countNext_ = count_;
    for (unsigned i = 0; i < Depth; ++i)
      storageNext_[i] = storage_[i];

    bool out_valid_int = (count_ != 0);
    bool in_ready_int = (count_ < Depth) || (out_valid_int && out_ready_now);
    bool do_pop = out_valid_int && out_ready_now;
    bool do_push = in_valid.toBool() && in_ready_int;

    if (do_pop) {
      rdNext_ = bump(rdNext_);
      countNext_--;
    }
    if (do_push) {
      storageNext_[wrNext_] = in_data;
      wrNext_ = bump(wrNext_);
      countNext_++;
    }
  }

  // The mask describes state-driven changes to the three visible FIFO outputs.
  // Output wires remain updated by eval(), preserving the existing phase split.
  change_mask_t tick_commit() {
    if (!pending)
      return 0;

    const bool out_ready_now = this->out_ready.get().toBool();
    const bool oldOutValid = count_ != 0;
    const bool oldInReady = (count_ < Depth) || (oldOutValid && out_ready_now);
    const Wire<Width> oldOutData = oldOutValid ? storage_[rd_] : Wire<Width>(0);

    rd_ = rdNext_;
    wr_ = wrNext_;
    count_ = countNext_;
    for (unsigned i = 0; i < Depth; ++i)
      storage_[i] = storageNext_[i];
    pending = false;

    const bool newOutValid = count_ != 0;
    const bool newInReady = (count_ < Depth) || (newOutValid && out_ready_now);
    const Wire<Width> newOutData = newOutValid ? storage_[rd_] : Wire<Width>(0);
    change_mask_t changed = 0;
    if (oldInReady != newInReady)
      changed |= kInReadyChanged;
    if (oldOutValid != newOutValid)
      changed |= kOutValidChanged;
    if (oldOutData != newOutData)
      changed |= kOutDataChanged;
    return changed;
  }

private:
  static constexpr unsigned bump(unsigned p) { return (p + 1 >= Depth) ? 0 : (p + 1); }

  void resetState() {
    rd_ = 0;
    wr_ = 0;
    count_ = 0;
    for (auto &e : storage_)
      e = Wire<Width>(0);
  }

public:
  Ref<Wire<1>> rst;

  Ref<Wire<1>> in_valid;
  Ref<Wire<1>> in_ready;
  Ref<Wire<Width>> in_data;

  Ref<Wire<1>> out_valid;
  Ref<Wire<1>> out_ready;
  Ref<Wire<Width>> out_data;

  bool pending = false;
  bool evalValid_ = false;
  bool lastEvalOutReady_ = false;
  unsigned lastEvalCount_ = 0;
  unsigned lastEvalRd_ = 0;
  Wire<Width> lastEvalOutData_{};

private:
  Wire<Width> storage_[Depth]{};
  unsigned rd_ = 0;
  unsigned wr_ = 0;
  unsigned count_ = 0;

  Wire<Width> storageNext_[Depth]{};
  unsigned rdNext_ = 0;
  unsigned wrNext_ = 0;
  unsigned countNext_ = 0;
};

} // namespace pyc::cpp
