#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "epidemic.hpp"

#include "doctest.h"

namespace pf {
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

  SUBCASE("Normal use, N=300") {
    Epidemic epidemic{0.8, 0.79};
    Population initial_population{299, 1, 0};
    int const time{15};
    const auto state = epidemic.evolve(initial_population, time);
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[1], {298, 1, 1}));
    CHECK(result(state[2], {297, 1, 2}));
    CHECK(result(state[3], {297, 1, 2}));
    CHECK(result(state[4], {296, 1, 3}));
    CHECK(result(state[13], {289, 1, 10}));
    CHECK(result(state[14], {288, 1, 11}));
    CHECK(result(state[15], {287, 1, 12}));
  }

  SUBCASE("Normal use, N=300") {
    Epidemic epidemic{0.99, 0.01};
    Population initial_population{299, 1, 0};
    int const time{15};
    const auto state = epidemic.evolve(initial_population, time);
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[1], {298, 2, 0}));
    CHECK(result(state[2], {296, 4, 0}));
    CHECK(result(state[3], {293, 7, 0}));
    CHECK(result(state[4], {286, 13, 1}));
    CHECK(result(state[13], {1, 190, 109}));
    CHECK(result(state[14], {0, 172, 128}));
    CHECK(result(state[15], {0, 155, 145}));
  }
}
}  // namespace pf
