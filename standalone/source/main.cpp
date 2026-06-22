#include <fmt/format.h>

#include <cxxopts.hpp>
#include <iostream>
#include <rattrig/trigonom.hpp>
#include <string>
#include <vector>

using namespace rattrig;

void print_usage(const cxxopts::Options& options) { std::cout << options.help() << '\n'; }

void print_vector(const std::string& name, const std::vector<int>& vec) {
    std::cout << fmt::format("  {}: [{}, {}]", name, vec[0], vec[1]) << '\n';
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
        std::vector<int> v1 = {3, 4};
        std::vector<int> v2 = {1, 2};

        print_vector("Vector v1", v1);
        print_vector("Vector v2", v2);

        std::cout << fmt::format("  Quadrance v1: {}", quad(v1)) << '\n';
        std::cout << fmt::format("  Quadrance v2: {}", quad(v2)) << '\n';
        std::cout << fmt::format("  Dot product: {}", dot(v1, v2)) << '\n';
        std::cout << fmt::format("  Cross product: {}", cross(v1, v2)) << '\n';
        std::cout << fmt::format("  Spread: {}", spread(v1, v2)) << '\n';
        std::cout << '\n';

        // Example 2: Triangle analysis
        std::cout << "Example 2: Triangle Analysis\n";
        std::vector<int> a = {0, 0};
        std::vector<int> b = {4, 0};
        std::vector<int> c = {2, 3};

        print_vector("Point A", a);
        print_vector("Point B", b);
        print_vector("Point C", c);

        std::vector<int> ab = {b[0] - a[0], b[1] - a[1]};
        std::vector<int> bc = {c[0] - b[0], c[1] - b[1]};
        std::vector<int> ca = {a[0] - c[0], a[1] - c[1]};

        int q_ab = quad(ab);
        int q_bc = quad(bc);
        int q_ca = quad(ca);

        std::cout << fmt::format("  Side AB quadrance: {}", q_ab) << '\n';
        std::cout << fmt::format("  Side BC quadrance: {}", q_bc) << '\n';
        std::cout << fmt::format("  Side CA quadrance: {}", q_ca) << '\n';
        std::cout << fmt::format("  Quadrea (Archimedes): {}", archimedes(q_ab, q_bc, q_ca))
                  << '\n';
        std::cout << '\n';

        // Example 3: Special cases
        std::cout << "Example 3: Special Cases\n";
        std::vector<int> parallel1 = {1, 2};
        std::vector<int> parallel2 = {2, 4};
        std::vector<int> orthogonal1 = {1, 0};
        std::vector<int> orthogonal2 = {0, 1};

        std::cout << "  Parallel vectors: spread = " << spread(parallel1, parallel2) << '\n';
        std::cout << "  Orthogonal vectors: spread = " << spread(orthogonal1, orthogonal2) << '\n';
        std::cout << "  Parallel vectors: cross = " << cross(parallel1, parallel2) << '\n';
        std::cout << "  Orthogonal vectors: cross = " << cross(orthogonal1, orthogonal2) << '\n';
        std::cout << '\n';

        // Example 4: Triple Quad Formula
        std::cout << "Example 4: Triple Quad Formula\n";
        int q1 = 5;
        int q2 = 25;
        int spr = 0;  // 4/125 truncates to 0 as int
        int q3 = triple_quad_formula(q1, q2, spr);

        std::cout << fmt::format("  Given Q1 = {}, Q2 = {}, Spread = {}", q1, q2, spr) << '\n';
        std::cout << fmt::format("  Calculated Q3 = {}", q3) << '\n';
        std::cout << '\n';

        std::cout << "=== Demo Complete ===\n";

        return 0;

    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << '\n';
        return 1;
    }
}
