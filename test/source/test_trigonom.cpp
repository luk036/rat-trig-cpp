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

TEST_CASE("Test archimedes (zero input)") {
    int q_1 = 0;
    int q_2 = 0;
    int q_3 = 0;
    CHECK_EQ(archimedes(q_1, q_2, q_3), 0);
}

TEST_CASE("Test archimedes (negative input)") {
    int q_1 = -2;
    int q_2 = -4;
    int q_3 = -6;
    CHECK_EQ(archimedes(q_1, q_2, q_3), 32);
}

TEST_CASE("Test archimedes (zero quadrea)") {
    int q_1 = 1;
    int q_2 = 1;
    int q_3 = 2;
    CHECK_EQ(archimedes(q_1, q_2, q_3), 4);
}

TEST_CASE("Test dot (int)") {
    std::vector<int> v_1 = {1, 2};
    std::vector<int> v_2 = {3, 4};
    CHECK_EQ(dot(v_1, v_2), 11);
}

TEST_CASE("Test dot (double)") {
    std::vector<double> v_1 = {1.0, 2.0};
    std::vector<double> v_2 = {3.0, 4.0};
    CHECK_EQ(dot(v_1, v_2), 11.0);
}

TEST_CASE("Test dot (rational)") {
    std::vector<fractions::Fraction<int>> v_1
        = {fractions::Fraction<int>(1, 2), fractions::Fraction<int>(1, 4)};
    std::vector<fractions::Fraction<int>> v_2
        = {fractions::Fraction<int>(1, 6), fractions::Fraction<int>(1, 8)};
    CHECK_EQ(dot(v_1, v_2), fractions::Fraction<int>(11, 96));
}

TEST_CASE("Test dot (negative)") {
    std::vector<int> v_1 = {1, 2};
    std::vector<int> v_2 = {-1, -2};
    CHECK_EQ(dot(v_1, v_2), -5);
}

TEST_CASE("Test dot (orthogonal)") {
    std::vector<int> v_1 = {1, 0};
    std::vector<int> v_2 = {0, 1};
    CHECK_EQ(dot(v_1, v_2), 0);
}

TEST_CASE("Test cross (int)") {
    std::vector<int> v_1 = {1, 2};
    std::vector<int> v_2 = {3, 4};
    CHECK_EQ(cross(v_1, v_2), -2);
}

TEST_CASE("Test cross (double)") {
    std::vector<double> v_1 = {1.0, 2.0};
    std::vector<double> v_2 = {3.0, 4.0};
    CHECK_EQ(cross(v_1, v_2), -2.0);
}

TEST_CASE("Test cross (rational)") {
    std::vector<fractions::Fraction<int>> v_1
        = {fractions::Fraction<int>(1, 2), fractions::Fraction<int>(1, 4)};
    std::vector<fractions::Fraction<int>> v_2
        = {fractions::Fraction<int>(1, 6), fractions::Fraction<int>(1, 8)};
    CHECK_EQ(cross(v_1, v_2), fractions::Fraction<int>(1, 48));
}

TEST_CASE("Test cross (parallel)") {
    std::vector<int> v_1 = {1, 2};
    std::vector<int> v_2 = {1, 2};
    CHECK_EQ(cross(v_1, v_2), 0);
}

TEST_CASE("Test cross (unit vectors)") {
    std::vector<int> v_1 = {1, 0};
    std::vector<int> v_2 = {0, 1};
    CHECK_EQ(cross(v_1, v_2), 1);
}

TEST_CASE("Test quad (int)") {
    std::vector<int> v = {3, 4};
    CHECK_EQ(quad(v), 25);
}

TEST_CASE("Test quad (double)") {
    std::vector<double> v = {3.0, 4.0};
    CHECK_EQ(quad(v), 25.0);
}

TEST_CASE("Test quad (rational)") {
    std::vector<fractions::Fraction<int>> v
        = {fractions::Fraction<int>(3, 5), fractions::Fraction<int>(4, 5)};
    CHECK_EQ(quad(v), fractions::Fraction<int>(1, 1));
}

TEST_CASE("Test quad (diagonal)") {
    std::vector<int> v = {1, 1};
    CHECK_EQ(quad(v), 2);
}

TEST_CASE("Test quad (zero)") {
    std::vector<int> v = {0, 0};
    CHECK_EQ(quad(v), 0);
}

TEST_CASE("Test spread (rational)") {
    std::vector<fractions::Fraction<int>> v_1
        = {fractions::Fraction<int>(1), fractions::Fraction<int>(2)};
    std::vector<fractions::Fraction<int>> v_2
        = {fractions::Fraction<int>(3), fractions::Fraction<int>(4)};
    CHECK_EQ(spread(v_1, v_2), fractions::Fraction<int>(4, 125));
}

TEST_CASE("Test spread (double)") {
    std::vector<double> v_1 = {1.0, 2.0};
    std::vector<double> v_2 = {3.0, 4.0};
    CHECK_EQ(spread(v_1, v_2), 0.032);
}

TEST_CASE("Test spread (rational 2)") {
    std::vector<fractions::Fraction<int>> v_1
        = {fractions::Fraction<int>(1, 2), fractions::Fraction<int>(1, 4)};
    std::vector<fractions::Fraction<int>> v_2
        = {fractions::Fraction<int>(1, 6), fractions::Fraction<int>(1, 8)};
    CHECK_EQ(spread(v_1, v_2), fractions::Fraction<int>(4, 125));
}

TEST_CASE("Test spread (parallel)") {
    std::vector<int> v_1 = {1, 2};
    std::vector<int> v_2 = {1, 2};
    CHECK_EQ(spread(v_1, v_2), 0);
}

TEST_CASE("Test spread (orthogonal)") {
    std::vector<int> v_1 = {1, 0};
    std::vector<int> v_2 = {0, 1};
    CHECK_EQ(spread(v_1, v_2), 1);
}

TEST_CASE("Test spread_law (double)") {
    double q_1 = 5.0;
    double q_2 = 25.0;
    double q_3 = 20.0;
    CHECK_EQ(spread_law(q_1, q_2, q_3), 0.8);
}

TEST_CASE("Test spread_law (degenerate)") {
    int q_1 = 1;
    int q_2 = 1;
    int q_3 = 4;
    CHECK_EQ(spread_law(q_1, q_2, q_3), 0);
}

TEST_CASE("Test spread_law (zero)") {
    int q_1 = 1;
    int q_2 = 1;
    int q_3 = 0;
    CHECK_EQ(spread_law(q_1, q_2, q_3), 0);
}

TEST_CASE("Test triple_quad_formula (int)") {
    int q_1 = 5;
    int q_2 = 25;
    int s_3 = 0;  // Fraction(4, 125) would be 0 as int
    CHECK_EQ(triple_quad_formula(q_1, q_2, s_3), 400);
}

TEST_CASE("Test triple_quad_formula (double)") {
    double q_1 = 5.0;
    double q_2 = 25.0;
    double s_3 = 0.032;  // 4/125 = 0.032
    CHECK_EQ(triple_quad_formula(q_1, q_2, s_3), 416.0);
}

TEST_CASE("Test triple_quad_formula (rational)") {
    fractions::Fraction<int> q_1(5);
    fractions::Fraction<int> q_2(25);
    fractions::Fraction<int> s_3(4, 125);
    CHECK_EQ(triple_quad_formula(q_1, q_2, s_3), fractions::Fraction<int>(416));
}

TEST_CASE("Test triple_quad_formula (max spread)") {
    int q_1 = 1;
    int q_2 = 1;
    int s_3 = 1;
    CHECK_EQ(triple_quad_formula(q_1, q_2, s_3), 4);
}

TEST_CASE("Test triple_quad_formula (zero spread)") {
    int q_1 = 1;
    int q_2 = 1;
    int s_3 = 0;
    CHECK_EQ(triple_quad_formula(q_1, q_2, s_3), 0);
}
