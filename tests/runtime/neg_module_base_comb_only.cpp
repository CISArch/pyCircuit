// Must NOT compile (F2): a comb-only module deletes its clocked entries, so a
// parent that calls them fails at compile time instead of spinning at runtime.
#include "pyc_component.hpp"

namespace {

struct CombOnly : pyc::cpp::ModuleBase<CombOnly> {
  static constexpr bool kHasState = false;
  static constexpr bool kStateMayChange = false;

  void eval() { q = d; }

  void tick_sample() = delete;
  pyc::cpp::BaseElement::change_mask_t tick_commit() = delete;

  unsigned q = 0;
  unsigned d = 0;
};

template <class Child>
struct Parent {
  Child child;
  void tick() { child.tick_sample(); }
};

} // namespace

int main() {
  Parent<CombOnly> p;
  p.tick();
  return 0;
}
