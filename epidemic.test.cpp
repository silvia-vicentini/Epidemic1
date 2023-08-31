#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "epidemic.hpp"

#include "doctest.h"

namespace pf {
bool result(Population const& p, Population const& v) {
  return p.S == v.S && p.I == v.I && p.R == v.R;
}

TEST_CASE("Testing the exeptions of the parameters") {
  SUBCASE("beta < 0") { CHECK_THROWS(Epidemic{-0.3, 0.5}); }
  SUBCASE("gamma < 0") { CHECK_THROWS(Epidemic{0.5, -0.3}); }
  SUBCASE("beta > 1") { CHECK_THROWS(Epidemic{1.5, 0.5}); }
  SUBCASE("gamma > 1") { CHECK_THROWS(Epidemic{0.5, 1.5}); }
  SUBCASE("beta < gamma") { CHECK_THROWS(Epidemic{0.5, 0.8}); }
  SUBCASE("beta = gamma") { CHECK_THROWS(Epidemic{0.5, 0.5}); }
}
TEST_CASE("Testing the approximations") {
  SUBCASE("Testing the solve function") {
    Epidemic epidemic{0.6, 0.2};
    Population const initial_population{187, 4, 0};
    int const N = 191;
    const auto result = epidemic.solve(initial_population, N);
    CHECK(result.S == 186);
    CHECK(result.I == 5);
    CHECK(result.R == 1);
  }

  SUBCASE("Testing the solve function") {
    Epidemic epidemic{0.65, 0.05};
    Population const initial_population{187, 4, 0};
    int const N = 191;
    const auto result = epidemic.approx(initial_population, N);
    CHECK(result.S == 185);
    CHECK(result.I == 5);
    CHECK(result.R == 0);
  }

  SUBCASE("Testing the approx function for tot > N") {
    Epidemic epidemic{0.6, 0.2};
    Population const initial_population{187, 4, 0};
    int const N = 191;
    const auto result = epidemic.approx(initial_population, N);
    CHECK(result.S == 186);
    CHECK(result.I == 5);
    CHECK(result.R == 0);
  }

  SUBCASE("Testing the approx function for tot < N") {
    Epidemic epidemic{0.65, 0.05};
    Population const initial_population{187, 4, 0};
    int const N = 191;
    const auto result = epidemic.approx(initial_population, N);
    CHECK(result.S == 185);
    CHECK(result.I == 6);
    CHECK(result.R == 0);
  }
}

TEST_CASE("Testing the evolve function") {
  SUBCASE("Normal use, beta -> gama, N=300") {
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

  SUBCASE("Normal use, beta >> gamma, N=300") {
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
