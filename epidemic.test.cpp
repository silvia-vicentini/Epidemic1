#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "epidemic.hpp"

#include "doctest.h"

bool result(Population const& p, Population const& v) {
  return p.S == v.S && p.I == v.I && p.R == v.R;
}

TEST_CASE("Testing the Epidemic development") {
  SUBCASE("Negative beta throws") { CHECK_THROWS(Epidemic{-0.3, 0.5}); }
  SUBCASE("Negative gamma throws") { CHECK_THROWS(Epidemic{0.5, -0.3}); }
  SUBCASE("beta > 1") { CHECK_THROWS(Epidemic{1.5, 0.5}); }
  SUBCASE("gamma > 1") { CHECK_THROWS(Epidemic{0.5, 1.5}); }
  SUBCASE("beta < gamma") { CHECK_THROWS(Epidemic{0.5, 0.8}); }
  SUBCASE("beta = gamma") { CHECK_THROWS(Epidemic{0.5, 0.5}); }

  Epidemic epidemic{0.8, 0.7};

  SUBCASE("Normal use, N=2") {
    Population initial_population{1, 1, 0};
    epidemic.evolve(initial_population, 1);
    const auto state = epidemic.state();
    CHECK(result(state[0], {1, 1, 0}));
    CHECK(result(state[1], {1, 0, 1}));
  }
}
