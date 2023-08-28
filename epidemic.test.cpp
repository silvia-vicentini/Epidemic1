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

  SUBCASE("Normal use, N=300") {
    Population initial_population{299, 1, 0};
    epidemic.evolve(initial_population, 4);
    const auto state = epidemic.state();
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[1], {298, 1, 1}));
    CHECK(result(state[2], {297, 1, 2}));
    CHECK(result(state[3], {296, 1, 3}));
    CHECK(result(state[4], {295, 1, 4}));
  }
  
  SUBCASE("Normal use, N=300") {
    Epidemic epidemic{0.8, 0.2};
    Population initial_population{990, 10, 0};
    epidemic.evolve(initial_population, 4);
    const auto state = epidemic.state();
    CHECK(result(state[0], {990, 10, 0}));
    CHECK(result(state[1], {982, 16, 2}));
    CHECK(result(state[2], {970, 25, 5}));
    CHECK(result(state[3], {951, 39, 10}));
    CHECK(result(state[4], {921, 61, 18}));
  }
}
