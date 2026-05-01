#include <fmt/format.h>

#include <cxxopts.hpp>
#include <iostream>
#include <rattrig/trigonom.hpp>
#include <string>
#include <vector>

using namespace rattrig;

void print_usage(const cxxopts::Options& options) { std::cout << options.help() << '\n'; }

void print_vector(const std::string& name, const std::vector<double>& vec) {
    std::cout << fmt::format("  {}: [{:.2f}, {:.2f}]", name, vec[0], vec[1]) << '\n';
}

int main(int argc, char** argv) {
    cxxopts::Options options(*argv, "Rational Trigonometry Calculator");

    bool demo = false;
    bool help = false;
    bool version = false;
    std::string operation;

    // clang-format off
    options.add_options()
        ("h,help", "Show help", cxxopts::value(help))
        ("v,version", "Print version information", cxxopts::value(version))
        ("d,demo", "Run demonstration mode", cxxopts::value(demo))
        ("o,operation", "Operation to perform", cxxopts::value(operation)->default_value("demo"));
    // clang-format on

    try {
        auto result = options.parse(argc, argv);

        if (help) {
            print_usage(options);
            return 0;
        }

        if (version) {
            std::cout << "RatTrig, version 1.0.0\n";
            std::cout << "Rational Trigonometry Library\n";
            return 0;
        }

        // Demo mode
        std::cout << "=== Rational Trigonometry Demo ===\n" << '\n';

        // Example 1: Basic vector operations
        std::cout << "Example 1: Basic Vector Operations\n";
        std::vector<double> v1 = {3.0, 4.0};
        std::vector<double> v2 = {1.0, 2.0};

        print_vector("Vector v1", v1);
        print_vector("Vector v2", v2);

        std::cout << fmt::format("  Quadrance v1: {:.2f}", quad(v1)) << '\n';
        std::cout << fmt::format("  Quadrance v2: {:.2f}", quad(v2)) << '\n';
        std::cout << fmt::format("  Dot product: {:.2f}", dot(v1, v2)) << '\n';
        std::cout << fmt::format("  Cross product: {:.2f}", cross(v1, v2)) << '\n';
        std::cout << fmt::format("  Spread: {:.4f}", spread(v1, v2)) << '\n';
        std::cout << '\n';

        // Example 2: Triangle analysis
        std::cout << "Example 2: Triangle Analysis\n";
        std::vector<double> a = {0.0, 0.0};
        std::vector<double> b = {4.0, 0.0};
        std::vector<double> c = {2.0, 3.0};

        print_vector("Point A", a);
        print_vector("Point B", b);
        print_vector("Point C", c);

        std::vector<double> ab = {b[0] - a[0], b[1] - a[1]};
        std::vector<double> bc = {c[0] - b[0], c[1] - b[1]};
        std::vector<double> ca = {a[0] - c[0], a[1] - c[1]};

        double q_ab = quad(ab);
        double q_bc = quad(bc);
        double q_ca = quad(ca);

        std::cout << fmt::format("  Side AB quadrance: {:.2f}", q_ab) << '\n';
        std::cout << fmt::format("  Side BC quadrance: {:.2f}", q_bc) << '\n';
        std::cout << fmt::format("  Side CA quadrance: {:.2f}", q_ca) << '\n';
        std::cout << fmt::format("  Quadrea (Archimedes): {:.2f}", archimedes(q_ab, q_bc, q_ca))
                  << '\n';
        std::cout << fmt::format("  Spread at A: {:.4f}", spread_law(q_ca, q_ab, q_bc)) << '\n';
        std::cout << fmt::format("  Spread at B: {:.4f}", spread_law(q_ab, q_bc, q_ca)) << '\n';
        std::cout << fmt::format("  Spread at C: {:.4f}", spread_law(q_bc, q_ca, q_ab)) << '\n';
        std::cout << '\n';

        // Example 3: Special cases
        std::cout << "Example 3: Special Cases\n";
        std::vector<double> parallel1 = {1.0, 2.0};
        std::vector<double> parallel2 = {2.0, 4.0};
        std::vector<double> orthogonal1 = {1.0, 0.0};
        std::vector<double> orthogonal2 = {0.0, 1.0};

        std::cout << "  Parallel vectors: spread = " << spread(parallel1, parallel2) << '\n';
        std::cout << "  Orthogonal vectors: spread = " << spread(orthogonal1, orthogonal2) << '\n';
        std::cout << "  Parallel vectors: cross = " << cross(parallel1, parallel2) << '\n';
        std::cout << "  Orthogonal vectors: cross = " << cross(orthogonal1, orthogonal2) << '\n';
        std::cout << '\n';

        // Example 4: Triple Quad Formula
        std::cout << "Example 4: Triple Quad Formula\n";
        double q1 = 5.0;
        double q2 = 25.0;
        double spr = 0.032;
        double q3 = triple_quad_formula(q1, q2, spr);

        std::cout << fmt::format("  Given Q1 = {:.2f}, Q2 = {:.2f}, Spread = {:.3f}", q1, q2, spr)
                  << '\n';
        std::cout << fmt::format("  Calculated Q3 = {:.2f}", q3) << '\n';
        std::cout << fmt::format("  Verification: Spread Law = {:.4f}", spread_law(q1, q2, q3))
                  << '\n';
        std::cout << '\n';

        std::cout << "=== Demo Complete ===\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}