#include <doctest/doctest.h>

#include <cstdint>
#include <fractions/fractions.hpp>
#include <rattrig/geometry.hpp>
#include <rattrig/validation.hpp>

using namespace rattrig;
using fractions::Fraction;

// ===========================================================================
// Geometry: Point2D
// ===========================================================================

TEST_CASE("Point2D") {
    auto p = Point2D<int>::new_(3, 5);
    CHECK(p.x == 3);
    CHECK(p.y == 5);
}

TEST_CASE("Point2D from_pair") {
    auto p = Point2D<int>::from_pair({1, 2});
    CHECK(p.x == 1);
    CHECK(p.y == 2);
}

// ===========================================================================
// Geometry: Vector2D
// ===========================================================================

TEST_CASE("Vector2D add") {
    auto v1 = Vector2D<int>::new_(1, 2);
    auto v2 = Vector2D<int>::new_(3, 4);
    auto result = v1 + v2;
    CHECK(result.x == 4);
    CHECK(result.y == 6);
}

TEST_CASE("Vector2D sub") {
    auto v1 = Vector2D<int>::new_(3, 4);
    auto v2 = Vector2D<int>::new_(1, 2);
    auto result = v1 - v2;
    CHECK(result.x == 2);
    CHECK(result.y == 2);
}

// ===========================================================================
// Geometry: Triangle2D
// ===========================================================================

TEST_CASE("Triangle2D quadrances") {
    auto p1 = Point2D<int>::new_(0, 0);
    auto p2 = Point2D<int>::new_(1, 0);
    auto p3 = Point2D<int>::new_(0, 1);
    auto t = Triangle2D<int>(p1, p2, p3);
    auto q = t.quadrances();
    CHECK(std::get<0>(q) == 2);
    CHECK(std::get<1>(q) == 1);
    CHECK(std::get<2>(q) == 1);
}

TEST_CASE("Triangle2D area") {
    auto p1 = Point2D<int>::new_(0, 0);
    auto p2 = Point2D<int>::new_(1, 0);
    auto p3 = Point2D<int>::new_(0, 1);
    auto t = Triangle2D<int>(p1, p2, p3);
    CHECK(t.area() == 4);
}

TEST_CASE("Triangle2D twist") {
    auto p1 = Point2D<int>::new_(0, 0);
    auto p2 = Point2D<int>::new_(1, 0);
    auto p3 = Point2D<int>::new_(0, 1);
    auto t = Triangle2D<int>(p1, p2, p3);
    CHECK(t.twist() == 1);
}

TEST_CASE("Triangle2D is_degenerate") {
    auto p1 = Point2D<int>::new_(0, 0);
    auto p2 = Point2D<int>::new_(1, 1);
    auto p3 = Point2D<int>::new_(2, 2);
    auto t = Triangle2D<int>(p1, p2, p3);
    CHECK(t.is_degenerate());
}

// ===========================================================================
// Validation
// ===========================================================================

TEST_CASE("are_collinear") {
    auto p1 = std::make_pair(0, 0);
    auto p2 = std::make_pair(1, 1);
    auto p3 = std::make_pair(2, 2);
    CHECK(are_collinear(p1, p2, p3));
}

TEST_CASE("not collinear") {
    auto p1 = std::make_pair(0, 0);
    auto p2 = std::make_pair(1, 0);
    auto p3 = std::make_pair(0, 1);
    CHECK(!are_collinear(p1, p2, p3));
}

TEST_CASE("is_valid_triangle") {
    auto p1 = std::make_pair(0, 0);
    auto p2 = std::make_pair(1, 0);
    auto p3 = std::make_pair(0, 1);
    CHECK(is_valid_triangle(p1, p2, p3));
}

TEST_CASE("is_right_triangle") {
    CHECK(is_right_triangle(1, 0, 0));
    CHECK(!is_right_triangle(0, 0, 0));
}

TEST_CASE("are_lines_parallel") {
    auto l1 = std::make_tuple(1, 1, 0);
    auto l2 = std::make_tuple(2, 2, 1);
    CHECK(are_lines_parallel(l1, l2));
}

TEST_CASE("are_lines_perpendicular") {
    auto l1 = std::make_tuple(1, 0, 0);
    auto l2 = std::make_tuple(0, 1, 0);
    CHECK(are_lines_perpendicular(l1, l2));
}

TEST_CASE("point_on_line") {
    auto point = std::make_pair(1, 1);
    auto line = std::make_tuple(1, -1, 0);
    CHECK(point_on_line(point, line));
}

TEST_CASE("point_in_triangle") {
    using F = Fraction<int>;
    auto point = std::make_pair(F(1, 2), F(1, 4));
    auto p1 = std::make_pair(F(0, 1), F(0, 1));
    auto p2 = std::make_pair(F(1, 1), F(0, 1));
    auto p3 = std::make_pair(F(0, 1), F(1, 1));
    CHECK(point_in_triangle(point, p1, p2, p3));
}

TEST_CASE("is_valid_quadrance") {
    CHECK(is_valid_quadrance(4));
    CHECK(is_valid_quadrance(0));
    CHECK(!is_valid_quadrance(-1));
}

TEST_CASE("is_valid_spread") {
    using F = Fraction<int>;
    CHECK(is_valid_spread(F(0, 1)));
    CHECK(is_valid_spread(F(1, 2)));
    CHECK(is_valid_spread(F(1, 1)));
    CHECK(!is_valid_spread(F(-1, 10)));
    CHECK(!is_valid_spread(F(11, 10)));
}

TEST_CASE("is_acute_triangle") {
    using F = Fraction<int>;
    CHECK(is_acute_triangle(F(3, 10), F(3, 10), F(3, 10)));
    CHECK(!is_acute_triangle(F(1, 1), F(3, 10), F(3, 10)));
}

TEST_CASE("is_obtuse_triangle") {
    using F = Fraction<int>;
    CHECK(is_obtuse_triangle(F(3, 5), F(3, 10), F(3, 10)));
    CHECK(!is_obtuse_triangle(F(2, 5), F(2, 5), F(2, 5)));
}

// ===========================================================================
// Fraction type support
// ===========================================================================

using Frac = Fraction<int>;

TEST_CASE("Triangle2D with Fraction<int>") {
    auto p1 = Point2D<Frac>::new_(Frac(0, 1), Frac(0, 1));
    auto p2 = Point2D<Frac>::new_(Frac(3, 1), Frac(0, 1));
    auto p3 = Point2D<Frac>::new_(Frac(0, 1), Frac(4, 1));
    auto t = Triangle2D<Frac>(p1, p2, p3);
    auto q = t.quadrances();
    // 3-4-5 triangle: q1=25 (3²+4²), q2=16 (4²), q3=9 (3²)
    CHECK(std::get<0>(q).numer() == 25);
    CHECK(std::get<1>(q).numer() == 16);
    CHECK(std::get<2>(q).numer() == 9);
    // area = 4 * 9 * 16 - (9+16-25)² = 576 - 0 = 576
    CHECK(t.area().numer() == 576);
    CHECK(!t.is_degenerate());
}

TEST_CASE("are_collinear with Fraction<int>") {
    auto p1 = std::make_pair(Frac(0, 1), Frac(0, 1));
    auto p2 = std::make_pair(Frac(1, 1), Frac(1, 1));
    auto p3 = std::make_pair(Frac(2, 1), Frac(2, 1));
    CHECK(are_collinear(p1, p2, p3));

    auto p4 = std::make_pair(Frac(0, 1), Frac(1, 1));
    CHECK(!are_collinear(p1, p2, p4));
}