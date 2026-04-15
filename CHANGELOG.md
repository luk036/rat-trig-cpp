# Changelog

All notable changes to this project will be documented in this file.

The format is based on [Keep a Changelog](https://keepachangelog.com/en/1.0.0/),
and this project adheres to [Semantic Versioning](https://semver.org/spec/v2.0.0.html).

## [Unreleased]

### Added
- **std::array support**: Added std::array<T, 2> overloads for all vector functions (cross, dot, quad, spread)
  - Better performance than std::vector for 2D vectors
  - Enables true constexpr evaluation at compile-time
  - Backward compatibility maintained with std::vector versions (marked as deprecated)
- **Division by zero protection**: spread() function now throws std::invalid_argument when given zero vectors
- **New mathematical functions**:
  - `quadaverage()`: Calculates the average quadrance between two vectors
  - `QuadAngle<T>`: Struct representing dilated directed angles with quadrance, spread, and sign
  - `make_quadangle()`: Helper function to create QuadAngle instances
  - `is_cyclic_quad()`: Checks if four quadrances form a cyclic quadrilateral
- **Comprehensive test suite**:
  - Extended edge case tests for all functions
  - Property-based tests using rapidcheck
  - Tests with multiple numeric types (int, double, float, long double, long long, fractions)
  - Division by zero exception tests
  - Constexpr evaluation tests
- **Performance benchmarks**: Benchmark tests comparing different functions and data types
  - std::array vs std::vector performance comparison
  - Performance metrics for all core functions
- **pkg-config support**: Added rattrig.pc.in for easier integration with build systems
- **Improved xmake build**: Fixed hardcoded dependency paths in xmake.lua
  - Now checks environment variable FRACTIONS_CPP_DIR
  - Falls back to multiple common relative locations
  - More flexible for different development setups

### Changed
- Updated namespace documentation to clarify rational trigonometry concepts
- Improved error messages for invalid arguments
- Enhanced test coverage from basic to comprehensive

### Deprecated
- std::vector overloads for vector operations (cross, dot, quad, spread)
  - Use std::array<T, 2> versions instead for better performance
  - Will be removed in a future major version

### Security
- Added validation to prevent division by zero in spread calculations

## [1.0] - Initial Release

### Added
- Core rational trigonometry functions:
  - `archimedes()`: Quadrea calculation using Archimedes' formula
  - `cross()`: 2D vector cross product
  - `dot()`: 2D vector dot product
  - `quad()`: Quadrance (squared length) calculation
  - `spread()`: Spread between two vectors
  - `triple_quad_formula()`: Third quadrance calculation
  - `spread_law()`: Spread calculation from three quadrances
- Modern CMake build system with CPM.cmake dependency management
- xmake build system support
- Comprehensive CI/CD pipeline via GitHub Actions
- Code coverage integration via codecov
- Automated code formatting with clang-format and cmake-format
- Doxygen documentation generation
- Test suite using doctest framework
- Property-based testing support with rapidcheck
- Standalone executable target
- Installable package with version header generation

[Unreleased]: https://github.com/luk036/rat-trig-cpp/compare/v1.0...HEAD
[1.0]: https://github.com/luk036/rat-trig-cpp/releases/tag/v1.0
