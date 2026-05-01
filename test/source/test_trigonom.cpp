#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>  // for ResultBuilder, TestCase, CHECK, TEST_CASE

#include <fractions/fractions.hpp>  // for Fraction
#include <limits>                   // for numeric_limits
#include <ostream>                  // for Fraction, don't remove
#include <rattrig/trigonom.hpp>     // for archimedes
#include <stdexcept>                // for runtime_error

using namespace rattrig;

// Traditional unit tests
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
    std::vector<int> vec = {3, 4};
    CHECK_EQ(quad(vec), 25);
}

TEST_CASE("Test quad (double)") {
    std::vector<double> vec = {3.0, 4.0};
    CHECK_EQ(quad(vec), 25.0);
}

TEST_CASE("Test quad (rational)") {
    std::vector<fractions::Fraction<int>> vec
        = {fractions::Fraction<int>(3, 5), fractions::Fraction<int>(4, 5)};
    CHECK_EQ(quad(vec), fractions::Fraction<int>(1, 1));
}

TEST_CASE("Test quad (diagonal)") {
    std::vector<int> vec = {1, 1};
    CHECK_EQ(quad(vec), 2);
}

TEST_CASE("Test quad (zero)") {
    std::vector<int> vec = {0, 0};
    CHECK_EQ(quad(vec), 0);
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
    int spr_val = 0;  // Fraction(4, 125) would be 0 as int
    CHECK_EQ(triple_quad_formula(q_1, q_2, spr_val), 400);
}

TEST_CASE("Test triple_quad_formula (double)") {
    double q_1 = 5.0;
    double q_2 = 25.0;
    double spr_val = 0.032;  // 4/125 = 0.032
    CHECK_EQ(triple_quad_formula(q_1, q_2, spr_val), 416.0);
}

TEST_CASE("Test triple_quad_formula (rational)") {
    fractions::Fraction<int> q_1(5);
    fractions::Fraction<int> q_2(25);
    fractions::Fraction<int> spr_val(4, 125);
    CHECK_EQ(triple_quad_formula(q_1, q_2, spr_val), fractions::Fraction<int>(416));
}

TEST_CASE("Test triple_quad_formula (max spread)") {
    int q_1 = 1;
    int q_2 = 1;
    int spr_val = 1;
    CHECK_EQ(triple_quad_formula(q_1, q_2, spr_val), 4);
}

TEST_CASE("Test triple_quad_formula (zero spread)") {
    int q_1 = 1;
    int q_2 = 1;
    int spr_val = 0;
    CHECK_EQ(triple_quad_formula(q_1, q_2, spr_val), 0);
}

// Error handling tests
TEST_CASE("Test error handling - invalid vector size") {
    std::vector<int> v1 = {1};  // Wrong size
    std::vector<int> v2 = {1, 2};

    CHECK_THROWS_AS(quad(v1), TrigonomError);
    CHECK_THROWS_AS(dot(v1, v2), TrigonomError);
    CHECK_THROWS_AS(cross(v1, v2), TrigonomError);
}

TEST_CASE("Test error handling - zero quadrance in spread") {
    std::vector<int> zero = {0, 0};
    std::vector<int> v = {1, 2};

    CHECK_THROWS_AS(spread(zero, v), TrigonomError);
    CHECK_THROWS_AS(spread(v, zero), TrigonomError);
}

TEST_CASE("Test error handling - zero quadrance in spread_law") {
    CHECK_THROWS_AS(spread_law(0, 1, 1), TrigonomError);
    CHECK_THROWS_AS(spread_law(1, 0, 1), TrigonomError);
}

// 3D operations tests
TEST_CASE("Test dot3d (double)") {
    std::vector<double> v1 = {1.0, 2.0, 3.0};
    std::vector<double> v2 = {4.0, 5.0, 6.0};
    CHECK_EQ(dot3d(v1, v2), 32.0);
}

TEST_CASE("Test cross3d (double)") {
    std::vector<double> v1 = {1.0, 2.0, 3.0};
    std::vector<double> v2 = {4.0, 5.0, 6.0};
    auto result = cross3d(v1, v2);
    CHECK_EQ(result[0], -3.0);
    CHECK_EQ(result[1], 6.0);
    CHECK_EQ(result[2], -3.0);
}

TEST_CASE("Test quad3d (double)") {
    std::vector<double> v = {1.0, 2.0, 3.0};
    CHECK_EQ(quad3d(v), 14.0);
}

TEST_CASE("Test spread3d (parallel)") {
    std::vector<double> v1 = {1.0, 2.0, 3.0};
    std::vector<double> v2 = {2.0, 4.0, 6.0};
    CHECK_EQ(spread3d(v1, v2), 0.0);
}

TEST_CASE("Test spread3d (orthogonal)") {
    std::vector<double> v1 = {1.0, 0.0, 0.0};
    std::vector<double> v2 = {0.0, 1.0, 0.0};
    CHECK_EQ(spread3d(v1, v2), 1.0);
}

TEST_CASE("Test triple_product (double)") {
    std::vector<double> v1 = {1.0, 0.0, 0.0};
    std::vector<double> v2 = {0.0, 1.0, 0.0};
    std::vector<double> v3 = {0.0, 0.0, 1.0};
    CHECK_EQ(triple_product(v1, v2, v3), 1.0);
}

// Triangle solving tests
TEST_CASE("Test create_triangle") {
    std::vector<double> a = {0.0, 0.0};
    std::vector<double> b = {4.0, 0.0};
    std::vector<double> c = {2.0, 3.0};

    auto tri = create_triangle(a, b, c);
    CHECK_EQ(tri.q_ab, 16.0);
    CHECK(tri.quadrea > 0.0);
    CHECK_GE(tri.spread_a, 0.0);
    CHECK(tri.spread_a <= 1.0);
}

TEST_CASE("Test solve_triangle_sss") {
    auto tri = solve_triangle_sss(5.0, 25.0, 20.0);
    CHECK_EQ(tri.q_ab, 5.0);
    CHECK_EQ(tri.q_bc, 25.0);
    CHECK_EQ(tri.q_ca, 20.0);
    CHECK(tri.quadrea > 0.0);
}

TEST_CASE("Test solve_triangle_sas") {
    // Test with known valid triangle: 3-4-5 triangle
    // For a 3-4-5 triangle, the spread between sides 3 and 4 is 1 - 0^2/(3^2 * 4^2) = 1 (right
    // angle)
    auto tri = solve_triangle_sas(9.0, 16.0, 1.0);
    CHECK_EQ(tri.q_ab, 9.0);
    CHECK_EQ(tri.q_bc, 16.0);
    CHECK(tri.quadrea > 0.0);
    CHECK_EQ(tri.spread_c, 1.0);  // Right angle at C
}

// Transformation tests
TEST_CASE("Test translate_2d") {
    std::vector<double> v = {1.0, 2.0};
    std::vector<double> trans = {3.0, 4.0};
    auto result = translate_2d(v, trans);
    CHECK_EQ(result[0], 4.0);
    CHECK_EQ(result[1], 6.0);
}

TEST_CASE("Test scale_2d") {
    std::vector<double> v = {1.0, 2.0};
    auto result = scale_2d(v, 2.0);
    CHECK_EQ(result[0], 2.0);
    CHECK_EQ(result[1], 4.0);
}

TEST_CASE("Test rotate_2d") {
    std::vector<double> v = {1.0, 0.0};
    auto result = rotate_2d(v, 1.0);           // 90 degree rotation
    CHECK(std::abs(result[0]) < 1e-10);        // Should be near 0
    CHECK(std::abs(result[1] - 1.0) < 1e-10);  // Should be near 1
}

#ifdef RAPIDCHECK_H
#    include <rapidcheck.h>

// Improved property-based tests with better generation
TEST_CASE("Property-based test: dot product commutativity") {
    rc::check("dot(v1, v2) == dot(v2, v1)", []() {
        std::vector<int> v1 = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        std::vector<int> v2 = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        RC_PRE(v1.size() == static_cast<size_t>(2) && v2.size() == static_cast<size_t>(2));
        RC_ASSERT(dot(v1, v2) == dot(v2, v1));
    });
}

TEST_CASE("Property-based test: dot product with zero vector") {
    rc::check("dot(v, {0, 0}) == 0", []() {
        std::vector<int> v = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        RC_PRE(v.size() == static_cast<size_t>(2));
        std::vector<int> zero = {0, 0};
        RC_ASSERT(dot(v, zero) == 0);
    });
}

TEST_CASE("Property-based test: cross product anti-commutativity") {
    rc::check("cross(v1, v2) == -cross(v2, v1)", []() {
        std::vector<int> v1 = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        std::vector<int> v2 = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        RC_PRE(v1.size() == static_cast<size_t>(2) && v2.size() == static_cast<size_t>(2));
        RC_ASSERT(cross(v1, v2) == -cross(v2, v1));
    });
}

TEST_CASE("Property-based test: cross product with parallel vectors") {
    rc::check("cross(v, v) == 0", []() {
        std::vector<int> v = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        RC_PRE(v.size() == static_cast<size_t>(2));
        RC_ASSERT(cross(v, v) == 0);
    });
}

TEST_CASE("Property-based test: quad is always non-negative") {
    rc::check("quad(v) >= 0", []() {
        std::vector<int> v = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        RC_PRE(v.size() == static_cast<size_t>(2));
        // Note: For int types, quad can overflow for large values
        // Use smaller range to avoid overflow
        RC_PRE(std::abs(v[0]) < 1000 && std::abs(v[1]) < 1000);
        RC_ASSERT(quad(v) >= 0);
    });
}

TEST_CASE("Property-based test: quad of zero vector is zero") {
    rc::check("quad({0, 0}) == 0", []() {
        std::vector<int> zero = {0, 0};
        RC_ASSERT(quad(zero) == 0);
    });
}

TEST_CASE("Property-based test: spread is always between 0 and 1") {
    rc::check("0 <= spread(v1, v2) <= 1", []() {
        std::vector<double> v1
            = *rc::gen::container<std::vector<double>>(rc::gen::arbitrary<double>());
        std::vector<double> v2
            = *rc::gen::container<std::vector<double>>(rc::gen::arbitrary<double>());
        RC_PRE(v1.size() == static_cast<size_t>(2) && v2.size() == static_cast<size_t>(2));
        RC_PRE(v1[0] != 0.0 || v1[1] != 0.0);
        RC_PRE(v2[0] != 0.0 || v2[1] != 0.0);
        // Use smaller values to avoid numerical issues
        RC_PRE(std::abs(v1[0]) < 1000.0 && std::abs(v1[1]) < 1000.0);
        RC_PRE(std::abs(v2[0]) < 1000.0 && std::abs(v2[1]) < 1000.0);
        double spr = spread(v1, v2);
        RC_ASSERT(spr >= 0.0 && spr <= 1.0);
    });
}

TEST_CASE("Property-based test: spread of parallel vectors is zero") {
    rc::check("spread(v, v) == 0", []() {
        std::vector<int> v = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        RC_PRE(v.size() == static_cast<size_t>(2));
        RC_PRE(v[0] != 0 || v[1] != 0);
        RC_ASSERT(spread(v, v) == 0);
    });
}

TEST_CASE("Property-based test: spread of orthogonal vectors is one") {
    rc::check("spread(v1, v2) == 1 when orthogonal", []() {
        std::vector<int> v1 = *rc::gen::container<std::vector<int>>(rc::gen::arbitrary<int>());
        RC_PRE(v1.size() == static_cast<size_t>(2));
        RC_PRE(v1[0] != 0 || v1[1] != 0);
        std::vector<int> v2 = {-v1[1], v1[0]};
        RC_ASSERT(spread(v1, v2) == 1);
    });
}
#endif