// F2: a module instance is a component to its parent, so it exposes the same
// three entries as a clocked leaf (eval / tick_sample / tick_commit). The two
// traits on ModuleBase drive the parent's scheduling: kStateMayChange == false
// means the parent keeps no instance eval cache and never calls the clocked
// entries (a comb-only module deletes them, see the negative test).
#include "pyc_component.hpp"

#include <cassert>
#include <type_traits>

using namespace pyc::cpp;

namespace {

using mask_t = BaseElement::change_mask_t;

// A module that owns a register: all three entries exist.
struct Stateful : ModuleBase<Stateful> {
  static constexpr bool kHasState = true;
  static constexpr bool kStateMayChange = true;

  void eval() { y = q; }

  void tick_sample() { next = d; }

  mask_t tick_commit() {
    const bool changed = q != next;
    q = next;
    y = q;
    return changed ? kChanged : mask_t{0};
  }

  unsigned q = 0;
  unsigned d = 0;
  unsigned next = 0;
  unsigned y = 0;
};

// A comb-only module: the clocked entries are deleted, eval() is pure.
struct CombOnly : ModuleBase<CombOnly> {
  static constexpr bool kHasState = false;
  static constexpr bool kStateMayChange = false;

  void eval() { y = a + b; }

  void tick_sample() = delete;
  mask_t tick_commit() = delete;

  unsigned a = 0;
  unsigned b = 0;
  unsigned y = 0;
};

// The parent-facing shape: the trait decides whether the clocked entries exist,
// so one template serves both module kinds without a virtual call.
template <class Child>
struct Parent {
  Child child;

  void eval() { child.eval(); }

  void tick() {
    if constexpr (Child::kStateMayChange) {
      child.tick_sample();
      (void)child.tick_commit();
    }
  }
};

static_assert(std::is_base_of_v<BaseElement, ModuleBase<Stateful>>);
static_assert(std::is_base_of_v<BaseElement, Stateful>);
static_assert(std::is_base_of_v<BaseElement, CombOnly>);

// Conservative defaults: a hand-written model (external black box) is clocked.
struct Bare : ModuleBase<Bare> {
  void eval() {}
};
static_assert(Bare::kHasState);
static_assert(Bare::kStateMayChange);

// Same entry signatures as a clocked leaf.
static_assert(std::is_same_v<decltype(std::declval<Stateful &>().eval()), void>);
static_assert(std::is_same_v<decltype(std::declval<Stateful &>().tick_sample()), void>);
static_assert(std::is_same_v<decltype(std::declval<Stateful &>().tick_commit()), mask_t>);

void checkStateful() {
  Parent<Stateful> p;
  p.eval();
  assert(p.child.y == 0u);

  p.child.d = 0x5a;
  p.tick();
  assert(p.child.q == 0x5a);
  p.eval();
  assert(p.child.y == 0x5a);

  // No new input: the second tick must not report a change.
  p.child.tick_sample();
  assert(p.child.tick_commit() == mask_t{0});
}

void checkCombOnly() {
  Parent<CombOnly> p;
  p.child.a = 3;
  p.child.b = 4;
  p.eval();
  assert(p.child.y == 7u);

  // The trait makes the parent's clocked path disappear at compile time.
  p.tick();
  assert(p.child.y == 7u);
}

// A parent that would call the deleted entries does not compile; the negative
// translation unit (neg_module_base_comb_only.cpp) proves that.
} // namespace

int main() {
  checkStateful();
  checkCombOnly();
  return 0;
}
