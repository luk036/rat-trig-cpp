# AGENTS.md - Developer Guide for rat-trig-cpp

This file provides context and guidelines for agentic coding agents operating in this repository.

---

## Project Overview

**rat-trig-cpp** is a Modern C++17 implementation of Rational Trigonometry, developed by Norman Wildberger. It replaces traditional trigonometry concepts (angles, distances) with **quadrance** (squared distance) and **spread** (squared sine of angle), providing a more algebraic approach to geometry.

- **Language**: C++17 (with constexpr support)
- **Build System**: CMake
- **Testing Framework**: doctest (with optional RapidCheck for property-based testing)

---

## Build Commands

### Build Everything

```bash
# Build all targets at once (recommended for development)
cmake -S all -B build
cmake --build build
```

### Build and Run Tests

```bash
# Configure and build test suite
cmake -S test -B build/test
cmake --build build/test

# Run tests via ctest
cd build/test
ctest --build-config Debug

# Or run executable directly
./build/test/RatTrigTests
```

### Run a Single Test

```bash
# Using doctest's test case filter (by name)
./build/test/RatTrigTests --test-case="Test archimedes (int)"

# Or bysubstring filter
./build/test/RatTrigTests --test-case-prefix="archimedes"
```

### Build Standalone Executable

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/RatTrig --help
```

### Code Formatting

```bash
# Requires: clang-format, cmake-format, pyyaml
# pip install clang-format==18.1.2 cmake_format==0.6.13 pyyaml

# View formatting changes (dry-run)
cmake --build build/test --target format

# Apply formatting fixes
cmake --build build/test --target fix-format
```

### Sanitizers

Configure CMake with `-DUSE_SANITIZER=<Address | Memory | Undefined | Thread | Leak | 'Address;Undefined'>` to enable sanitizers.

### Static Analyzers

Configure CMake with `-DUSE_STATIC_ANALYZER=<clang-tidy | iwyu | cppcheck>` to enable static analysis.

### Code Coverage (Ubuntu/Linux)

```bash
cmake -S test -B build -DENABLE_TEST_COVERAGE=1 -DCMAKE_BUILD_TYPE=Debug
cmake --build build
cd build
ctest --build-config Debug
```

---

## Code Style Guidelines

### Formatting Configuration

The project uses `.clang-format` (Google-based with modifications):

```
BasedOnStyle: Google
IndentWidth: 4
ColumnLimit: 100
NamespaceIndentation: All
BreakBeforeBraces: Attach
BreakBeforeBinaryOperators: All
BreakBeforeTernaryOperators: true
AccessModifierOffset: -2
```

### Key Style Rules

1. **Indentation**: 4 spaces (no tabs)
2. **Column Limit**: 100 characters
3. **Braces**: Attach to line (K&R style)
4. **Namespaces**: Indent contents (all levels)
5. **Binary Operators**: Break before operators

### Naming Conventions

| Element | Convention | Example |
|---------|------------|---------|
| Classes/Structs | PascalCase | `TrigonomError`, `Triangle<T>` |
| Functions | camelCase | `archimedes()`, `quad()` |
| Member Variables | snake_case | `q_ab`, `spread_a` |
| Constants | camelCase or SCREAMING_SNAKE | `maxIterations` |
| Templates | T or descriptive | `<typename T>`, `<typename Tracer>` |
| Files | kebab-case | `trigonom.hpp` |

### Import/Include Order (clang-format Regroup)

```cpp
// 1. Main library header
#include <rattrig/trigonom.hpp>

// 2. Related headers (local)
// (none in this project)

// 3. External dependencies
#include <fractions/fractions.hpp>

// 4. Standard library
#include <array>
#include <cmath>
#include <iostream>
#include <limits>
#include <vector>
```

### Type Guidelines

- Use **template functions** for generic numeric types (`int`, `double`, `float`, `Fraction`)
- Prefer `std::vector<T>` for dynamic arrays; `std::array<T, N>` for fixed-size
- Use `std::size_t` for container sizes
- Use `constexpr` whenever possible for compile-time evaluation

### Error Handling

1. **Custom Exception**: `TrigonomError` (extends `std::runtime_error`)
2. **Validation Functions**: All input validation functions throw descriptive errors:

```cpp
template <typename T>
constexpr void validate_vector_size(const std::vector<T>& vec, size_t expected_size) {
    if (vec.size() != expected_size) {
        throw TrigonomError("Vector must have exactly " + std::to_string(expected_size) +
                          " elements, got " + std::to_string(vec.size()));
    }
}
```

3. **Validate Early**: Check preconditions at function entry
4. **Descriptive Messages**: Include parameter name and expected value

### Exception Usage

```cpp
// Throw with descriptive message
throw TrigonomError("Parameter '" + param_name + "' cannot be zero");

// Catch and handle
try {
    auto result = func();
} catch (const TrigonomError& e) {
    std::cerr << "Error: " << e.what() << '\n';
}
```

---

## Architecture Patterns

### Namespace

All library code lives in `rattrig` namespace:

```cpp
namespace rattrig {
    // functions, classes, templates
}  // namespace rattrig
```

### Template Functions

Template functions support any numeric type:

```cpp
template <typename T>
constexpr T quad(const std::vector<T>& vec) {
    // Works with int, double, Fraction<T>, etc.
}
```

### Structs for Compound Data

```cpp
template <typename T>
struct Triangle {
    std::vector<T> a;    // First vertex
    std::vector<T> b;    // Second vertex
    std::vector<T> c;    // Third vertex
    T q_ab;              // Quadrance of side AB
    T q_bc;
    T q_ca;
    T quadrea;           // Quadrea (16 × area²)
    T spread_a;
    T spread_b;
    T spread_c;
};
```

### Validation Functions Pattern

Each mathematical function:
1. Validates input sizes (vector dimensions)
2. Validates non-zero requirements
3. Validates non-negative requirements
4. Validates no overflow before operations
5. Then executes the computation

---

## Test Patterns

### Using doctest

```cpp
#define DOCTEST_CONFIG_IMPLEMENT_WITH_MAIN
#include <doctest/doctest.h>

TEST_CASE("Test description") {
    // Arrange
    int q_1 = 2;
    int q_2 = 4;
    int q_3 = 6;
    
    // Act
    auto result = archimedes(q_1, q_2, q_3);
    
    // Assert
    CHECK_EQ(result, 32);
}
```

### Property-Based Tests (RapidCheck)

```cpp
#ifdef RAPIDCHECK_H
#include <rapidcheck.h>

TEST_CASE("Property: dot product is commutative") {
    rc::check("dot(v1, v2) == dot(v2, v1)", []() {
        auto v1 = *rc::gen::container<std::vector<int>>(...);
        auto v2 = *rc::gen::container<std::vector<int>>(...);
        RC_PRE(v1.size() == 2 && v2.size() == 2);
        RC_ASSERT(dot(v1, v2) == dot(v2, v1));
    });
}
#endif
```

### Testing Multiple Types

```cpp
// Test with int
CHECK_EQ(archimedes(2, 4, 6), 32);

// Test with double
CHECK_EQ(archimedes(2.0, 4.0, 6.0), 32.0);

// Test with Fraction
fractions::Fraction<int> q_1(1, 2);
fractions::Fraction<int> q_2(1, 4);
fractions::Fraction<int> q_3(1, 6);
CHECK_EQ(archimedes(q_1, q_2, q_3), fractions::Fraction<int>(23, 144));
```

### Testing Error Handling

```cpp
TEST_CASE("Error handling - invalid vector size") {
    std::vector<int> v1 = {1};  // Wrong size!
    std::vector<int> v2 = {1, 2};
    
    CHECK_THROWS_AS(quad(v1), TrigonomError);
    CHECK_THROWS_AS(dot(v1, v2), TrigonomError);
}
```

---

## Key Files Reference

| File | Purpose |
|------|---------|
| `include/rattrig/trigonom.hpp` | Main library header (all functions) |
| `test/source/test_trigonom.cpp` | Test suite |
| `standalone/source/main.cpp` | Example standalone program |
| `CMakeLists.txt` | Main build configuration |
| `test/CMakeLists.txt` | Test build configuration |
| `.clang-format` | Code formatting rules |

---

## Common Development Workflows

### Adding a New Function

1. Add implementation to `include/rattrig/trigonom.hpp`
2. Use template for generic numeric type support
3. Add input validation functions
4. Add tests to `test/source/test_trigonom.cpp`
5. Test with int, double, and Fraction types

### Running Tests During Development

```bash
# Quick edit-build-test cycle
cmake -S test -B build/test && cmake --build build/test && ./build/test/RatTrigTests
```

### Building with All Subprojects

```bash
# See all targets in IDE
cmake -S all -B build
cmake --build build

# Run specific target
./build/test/RatTrigTests
./build/standalone/RatTrig --help
```

---

## Dependencies (via CPM.cmake)

- `fmt` (10.2.1) - Formatting library
- `doctest` (2.4.11) - Testing framework
- `PackageProject.cmake` (1.8.0) - Installable target support
- `Format.cmake` (1.7.3) - Code formatting

---

## Notes

- No Cursor/Copilot rules exist in this repository
- Uses Qwen settings: only allows specific bash commands (`sed`, test executable)
- Cross-platform: builds on Windows, macOS, Ubuntu via GitHub Actions
- No in-source builds allowed (must use out-of-source build directory)