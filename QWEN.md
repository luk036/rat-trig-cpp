# rat-trig-cpp Project Context

## Project Overview

**rat-trig-cpp** is a modern C++ implementation of **Rational Trigonometry**, an alternative approach to classical trigonometry developed by Norman Wildberger. Instead of using traditional concepts like angles, sine, and cosine (which involve irrational numbers and limits), this library uses rational numbers and geometric concepts like **quadrance** (squared length) and **spread** (squared sine of an angle).

### Key Features

- Modern C++17 implementation with constexpr support
- Single-header library design suitable for projects of any scale
- Clean separation between library code, tests, and standalone executable
- Template-based functions working with any numeric type
- Modern CMake practices with proper installable targets
- Dependency management via CPM.cmake
- Full CI/CD pipeline via GitHub Actions (macOS, Windows, Ubuntu)
- Code coverage via codecov
- Code formatting enforced by clang-format and cmake-format

### Core Mathematical Concepts

The library implements several key functions from rational trigonometry:

- **Archimedes' formula**: Calculates the quadrea (16 × area²) of a triangle
- **Quadrance**: Squared length of a vector (replaces distance)
- **Spread**: Square of cross product divided by product of quadrances (replaces angle)
- **Triple quad formula**: Calculates third quadrance given two quadrances and spread
- **Spread law**: Calculates spread given three quadrances of a triangle
- **Vector operations**: Cross product and dot product for 2D vectors

## Project Structure

```
rat-trig-cpp/
├── include/
│   └── rattrig/
│       └── trigonom.hpp          # Main library header (header-only capable)
├── source/
│   └── greeter.cpp               # Library source files
├── test/
│   ├── CMakeLists.txt            # Test build configuration
│   └── source/
│       ├── main.cpp              # Test runner entry point
│       └── test_trigonom.cpp     # Test implementations
├── standalone/
│   ├── CMakeLists.txt            # Standalone executable config
│   └── source/                   # Standalone CLI application source
├── all/                          # Builds all targets at once
├── cmake/                        # CMake utility scripts
│   ├── CPM.cmake                 # Dependency management
│   ├── specific.cmake            # Project-specific dependencies
│   └── tools.cmake               # Tool configuration (sanitizers, etc.)
├── documentation/                # Doxygen configuration
├── CMakeLists.txt                # Main CMake configuration
└── xmake.lua                     # Alternative build system (xmake)
```

## Dependencies

- **fmt** (v10.2.1): Format library for string formatting
- **Fractions** (luk036/fractions-cpp): Fraction number support
- **rapidcheck**: Property-based testing (via CMake)
- **doctest**: Unit testing framework
- **cxxopts**: Command-line option parsing (standalone only)

## Building and Running

### Build Everything (Recommended)

```bash
cmake -S all -B build
cmake --build build

# Run tests
./build/test/RatTrigTests

# Run standalone
./build/standalone/RatTrig --help

# Fix code format
cmake --build build --target fix-format
```

### Build Standalone Executable Only

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/RatTrig --help
```

### Build and Run Tests

```bash
cmake -S test -B build/test
cmake --build build/test

# Run tests via CTest
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test

# Or directly
./build/test/RatTrigTests
```

### Build Documentation

```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
# Open in browser
open build/doc/doxygen/html/index.html
```

### Alternative: Xmake Build System

```bash
# Build
xmake

# Run tests
xmake run test_rattrig

# Debug
xmake run -d test_rattrig
```

## Development Conventions

### Code Style

- **C++ Standard**: C++17
- **Formatting**: Enforced by clang-format (Google style)
- **CMake formatting**: Enforced by cmake-format
- **Compiler warnings**: Strict warnings, MSVC uses `/permissive-`

### Code Format Commands

```bash
# Install dependencies
pip install clang-format==18.1.2 cmake_format==0.6.13 pyyaml

# View formatting changes
cmake -S test -B build/test
cmake --build build/test --target format

# Apply formatting fixes
cmake --build build/test --target fix-format
```

### Testing Practices

- Uses **doctest** framework for unit tests
- Tests located in `test/source/`
- Property-based testing support via **rapidcheck**
- Code coverage enabled with `-DENABLE_TEST_COVERAGE=1`

### Build Configuration Options

**Sanitizers:**
```bash
cmake -S all -B build -DUSE_SANITIZER=Address
# Options: Address, Memory, MemoryWithOrigins, Undefined, Thread, Leak, 'Address;Undefined'
```

**Static Analyzers:**
```bash
cmake -S all -B build -DUSE_STATIC_ANALYZER=clang-tidy
# Options: clang-tidy, iwyu, cppcheck
```

**Ccache:**
```bash
cmake -S all -B build -DUSE_CCACHE=ON
```

**Code Coverage:**
```bash
cmake -S test -B build/test -DENABLE_TEST_COVERAGE=1
```

## Usage Examples

### Include the Library

```cpp
#include <rattrig/trigonom.hpp>

using namespace rattrig;

// Calculate quadrance (squared length) of a vector
std::vector<double> vec = {3.0, 4.0};
double q = quad(vec);  // Returns 25.0

// Calculate spread between two vectors
std::vector<double> v1 = {1.0, 0.0};
std::vector<double> v2 = {0.0, 1.0};
double s = spread(v1, v2);  // Returns 1.0 (perpendicular vectors)

// Use Archimedes' formula
double q1 = 25.0, q2 = 16.0, q3 = 9.0;
double quadrea = archimedes(q1, q2, q3);
```

### Template Support

All functions are templated and work with any numeric type:

```cpp
// Works with integers
int qi = archimedes(25, 16, 9);

// Works with doubles
double qd = archimedes(25.0, 16.0, 9.0);

// Works with custom types (e.g., fractions)
```

## Key Notes

- **Header-only option**: Can be converted to header-only by changing `add_library(${PROJECT_NAME} ...)` to `add_library(${PROJECT_NAME} INTERFACE)` and replacing `PUBLIC` with `INTERFACE`
- **In-source builds disabled**: Always use out-of-source builds (e.g., `cmake -S . -B build`)
- **File globbing used**: Source files are automatically detected via `GLOB_RECURSE`, but you may need to re-run CMake when adding new files
- **Version header**: Automatically generated via PackageProject.cmake at `rattrig/version.h`

## CI/CD

The project uses GitHub Actions for:
- ✅ Building on macOS, Windows, and Ubuntu
- ✅ Running tests
- ✅ Code coverage reporting (codecov)
- ✅ Code formatting checks
- ✅ Installation target verification
- ✅ Automatic documentation deployment on releases

## License

Check the `LICENSE` file for project licensing information.

## Related Projects

- **fractions-cpp**: C++ fractions library (dependency)
- **ModernCppStarter**: Template this project is based on
- **MiniCppStarter**: Simpler alternative starter template
