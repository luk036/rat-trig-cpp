#define ANKERL_NANOBENCH_IMPLEMENT
#include <nanobench.h>

#include <fractions/fractions.hpp>
#include <rattrig/geometry.hpp>
#include <rattrig/validation.hpp>

using namespace rattrig;
using fractions::Fraction;

// ===========================================================================
// Geometry: Triangle2D
// ===========================================================================

static void bench_triangle2d(ankerl::nanobench::Bench& b) {
    auto p1 = Point2D<int>::new_(0, 0);
    auto p2 = Point2D<int>::new_(3, 0);
    auto p3 = Point2D<int>::new_(0, 4);
    auto t = Triangle2D<int>(p1, p2, p3);

    b.run("Triangle2D<int> quadrances", [&] {
        auto result = t.quadrances();
        ankerl::nanobench::doNotOptimizeAway(result);
    });

    b.run("Triangle2D<int> area", [&] {
        auto result = t.area();
        ankerl::nanobench::doNotOptimizeAway(result);
    });

    b.run("Triangle2D<int> twist", [&] {
        auto result = t.twist();
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

// ===========================================================================
// Validation
// ===========================================================================

static void bench_validation(ankerl::nanobench::Bench& b) {
    auto p1 = std::make_pair(0, 0);
    auto p2 = std::make_pair(1, 1);
    auto p3 = std::make_pair(2, 2);

    b.run("are_collinear(int) collinear", [&] {
        auto result = are_collinear(p1, p2, p3);
        ankerl::nanobench::doNotOptimizeAway(result);
    });

    auto p4 = std::make_pair(0, 1);
    b.run("are_collinear(int) not collinear", [&] {
        auto result = are_collinear(p1, p2, p4);
        ankerl::nanobench::doNotOptimizeAway(result);
    });

    using F = Fraction<int>;
    auto l1 = std::make_tuple(F::one(), F::one(), F::zero());
    auto l2 = std::make_tuple(F::from(2, 1), F::from(2, 1), F::one());
    b.run("are_lines_parallel(Fraction<int>)", [&] {
        auto result = are_lines_parallel(l1, l2);
        ankerl::nanobench::doNotOptimizeAway(result);
    });
}

// ===========================================================================
// Main
// ===========================================================================

int main() {
    ankerl::nanobench::Bench bench;
    bench.title("rat-trig-cpp benchmarks").unit("iteration").warmup(100).minEpochIterations(5000);

    bench_triangle2d(bench);
    bench_validation(bench);
}