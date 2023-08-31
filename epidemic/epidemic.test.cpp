#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "epidemic.hpp"

#include "doctest.h"

//mancano i test su vaccine!!

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
  SUBCASE("Testing the solve function: case 1") {
    Epidemic epidemic{0.6, 0.2};
    Population const initial_population{187, 4, 0};
    int const N = 191;
    const auto result = epidemic.solve(initial_population, N);
    CHECK(result.S == 186);
    CHECK(result.I == 5);
    CHECK(result.R == 1);
  }

  SUBCASE("Testing the solve function: case 2") {
    Epidemic epidemic{0.65, 0.05};
    Population const initial_population{187, 4, 0};
    int const N = 191;
    const auto result = epidemic.solve(initial_population, N);
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

  SUBCASE("Testing the lockdown function") {
    Epidemic epidemic{0.99, 0.01};
    Population initial_population{45, 210, 45};
    int const N = 300;
    const auto result = epidemic.lockdown(initial_population, N);
    CHECK(result.S == 45);
    CHECK(result.I == 189);
    CHECK(result.R == 66);
  }
}

TEST_CASE("Testing the evolve function") {
  SUBCASE("Normal use, beta -> gama, N=300") {
    Epidemic epidemic{0.8, 0.79};
    Population initial_population{299, 1, 0};
    int const time{9};
    const auto state = epidemic.evolve(initial_population, time);
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[1], {298, 1, 1}));
    CHECK(result(state[2], {297, 1, 2}));
    CHECK(result(state[3], {297, 1, 2}));
    CHECK(result(state[4], {296, 1, 3}));
    CHECK(result(state[7], {293, 1, 6}));
    CHECK(result(state[8], {293, 1, 6}));
    CHECK(result(state[9], {292, 1, 7}));
  }

  SUBCASE("Normal use, beta >> gamma, N=300") {
    Epidemic epidemic{0.99, 0.01};
    Population initial_population{299, 1, 0};
    int const time{9};
    const auto state = epidemic.evolve(initial_population, time);
    CHECK(result(state[0], {299, 1, 0}));
    CHECK(result(state[1], {298, 2, 0}));
    CHECK(result(state[2], {296, 4, 0}));
    CHECK(result(state[3], {293, 7, 0}));
    CHECK(result(state[4], {286, 13, 1}));
    CHECK(result(state[7], {219, 72, 9}));
    CHECK(result(state[8], {167, 117, 16}));
    CHECK(result(state[9], {103, 170, 27}));
  }
}
}  // namespace pf
