#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include "epidemic.hpp"

#include "doctest.h"

TEST_CASE("Not accettable values of beta and gamma") {
  SUBCASE("Negative beta throws") { CHECK_THROWS(Epidemic{-0.3, 0.5}); }
  SUBCASE("Negative gamma throws") { CHECK_THROWS(Epidemic{0.5, -0.3}); }
  SUBCASE("beta > 1") { CHECK_THROWS(Epidemic{1.5, 0.5}); }
  SUBCASE("beta > 1") { CHECK_THROWS(Epidemic{0.5, 1.5}); }
}
