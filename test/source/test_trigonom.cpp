#include <doctest/doctest.h>  // for ResultBuilder, TestCase, CHECK, TEST_CASE

#include <fractions/fractions.hpp>  // for Fraction
#include <ostream>                  // for Fraction, don't remove
#include <rattrig/trigonom.hpp>     // for archimedes

using namespace rattrig;

TEST_CASE("Test archimedes (int)") {
  int q_1 = 2;
  int q_2 = 4;
  int q_3 = 6;
  CHECK_EQ(archimedes(q_1, q_2, q_3), 32);
}

TEST_CASE("Test archimedes (double)") {
  double q_1 = 2.0;
  double q_2 = 4.0;
  double q_3 = 6.0;
  CHECK_EQ(archimedes(q_1, q_2, q_3), 32.0);
}

TEST_CASE("Test archimedes (rational)") {
  fractions::Fraction<int> q_1(1, 2);
  fractions::Fraction<int> q_2(1, 4);
  fractions::Fraction<int> q_3(1, 6);
  CHECK_EQ(archimedes(q_1, q_2, q_3), fractions::Fraction<int>(23, 144));
}

// TEST_CASE("Test archimedes (rational)") {
//   boost::rational<int> q_1(1, 2);
//   boost::rational<int> q_2(1, 4);
//   boost::rational<int> q_3(1, 6);
//   CHECK_EQ(archimedes(q_1, q_2, q_3), boost::rational<int>(23, 144));
// }
