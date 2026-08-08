[![Actions Status](https://github.com/luk036/rat-trig-cpp/workflows/MacOS/badge.svg)](https://github.com/luk036/rat-trig-cpp/actions)
[![Actions Status](https://github.com/luk036/rat-trig-cpp/workflows/Windows/badge.svg)](https://github.com/luk036/rat-trig-cpp/actions)
[![Actions Status](https://github.com/luk036/rat-trig-cpp/workflows/Ubuntu/badge.svg)](https://github.com/luk036/rat-trig-cpp/actions)
[![Actions Status](https://github.com/luk036/rat-trig-cpp/workflows/Style/badge.svg)](https://github.com/luk036/rat-trig-cpp/actions)
[![Actions Status](https://github.com/luk036/rat-trig-cpp/workflows/Install/badge.svg)](https://github.com/luk036/rat-trig-cpp/actions)
[![codecov](https://codecov.io/gh/luk036/rat-trig-cpp/graph/badge.svg?token=po0JdQFWtl)](https://codecov.io/gh/luk036/rat-trig-cpp)

<p align="center">
  <img src="https://repository-images.githubusercontent.com/254842585/4dfa7580-7ffb-11ea-99d0-46b8fe2f4170" height="175" width="auto" />
</p>

# 📐 rat-trig-cpp

A Modern C++ implementation of the Rational Trigonometry library.

## ✨ Features

Rational trigonometry, developed by Norman Wildberger, replaces traditional concepts of angles and distances with **quadrance** (squared distance) and **spread** (squared sine of angle), providing a more algebraic approach to geometry.

This library provides:

- **Modern C++17 implementation** with constexpr support
- **Template-based functions** working with any numeric type (int, fractions)
- **std::array and std::vector support** for 2D vector operations
- **Comprehensive test suite** with property-based testing
- **Performance benchmarks** for optimization
- **Multiple build systems**: CMake (primary) and xmake
- **Cross-platform CI/CD** via GitHub Actions (macOS, Windows, Ubuntu)
- **Code coverage** via codecov
- **Automated formatting** via clang-format and cmake-format
- **pkg-config support** for easy integration

## 📖 Mathematical Concepts

### Key Functions

- **Archimedes' Formula**: Calculates quadrea (16 × area²) of a triangle
- **Quadrance**: Squared length of a vector (replaces distance)
- **Spread**: Squared sine of angle between vectors (replaces angle)
- **Triple Quad Formula**: Calculates third quadrance given two quadrances and spread
- **Spread Law**: Calculates spread from three quadrances
- **Quadaverage**: Average quadrance between two vectors
- **QuadAngle**: Dilated directed angle structure

### Why Rational Trigonometry?

Traditional trigonometry uses transcendental functions and irrational numbers. Rational trigonometry works entirely with rational numbers and algebraic operations, making it:
- More precise for computational applications
- Better suited for computer graphics and robotics
- Easier to understand algebraically
- Free from transcendental function approximations

## 💻 Usage Examples

### Basic Usage

```cpp
#include <rattrig/trigonom.hpp>
#include <array>
#include <iostream>

using namespace rattrig;

int main() {
    // Calculate quadrance (squared length) of vector (3, 4)
    std::array<int, 2> vec = {3, 4};
    int q = quad(vec);
    std::cout << "Quadrance: " << q << '\n';  // Output: 25

    // Calculate spread (squared sine) between orthogonal vectors
    std::array<int, 2> x_axis = {1, 0};
    std::array<int, 2> y_axis = {0, 1};
    int s = spread(x_axis, y_axis);
    std::cout << "Spread (orthogonal): " << s << '\n';  // Output: 1

    // Use Archimedes' formula to calculate quadrea
    int q1 = 25, q2 = 16, q3 = 9;
    int quadrea = archimedes(q1, q2, q3);
    std::cout << "Quadrea: " << quadrea << '\n';

    return 0;
}
```

### Working with Different Types

```cpp
#include <rattrig/trigonom.hpp>
#include <fractions/fractions.hpp>
#include <array>

using namespace rattrig;

// Works with integers
std::array<int, 2> v_int = {3, 4};
int q_int = quad(v_int);  // 25

// Works with fractions for exact rational arithmetic
std::array<fractions::Fraction<int>, 2> v_frac = {
    fractions::Fraction<int>(3, 5),
    fractions::Fraction<int>(4, 5)
};
auto q_frac = quad(v_frac);  // Exactly 1
```

### Advanced Features

```cpp
// Create a dilated directed angle (QuadAngle)
std::array<int, 2> v1 = {1, 2};
std::array<int, 2> v2 = {3, 4};

auto qa = make_quadangle(v1, v2);
std::cout << "Spread: " << qa.spread << '\n';
std::cout << "Quad: " << qa.quad << '\n';
std::cout << "Sign: " << (qa.sign ? "positive" : "negative") << '\n';

// Check if four quadrances form a cyclic quad
int Q1 = 2, Q2 = 4, Q3 = 6;
int Q4 = archimedes(Q1, Q2, Q3);
bool is_cyclic = is_cyclic_quad(Q1, Q2, Q3, Q4);
```

### Compile-time Evaluation

All functions are constexpr, enabling compile-time computation:

```cpp
constexpr std::array<int, 2> v1 = {3, 4};
constexpr std::array<int, 2> v2 = {5, 6};

constexpr int q = quad(v1);           // Computed at compile time
constexpr int d = dot(v1, v2);        // Computed at compile time
constexpr int c = cross(v1, v2);      // Computed at compile time

static_assert(q == 25, "Quadrance should be 25");
static_assert(d == 27, "Dot product should be 27");
```

## 🔧 Building and Running

### Build and run the standalone target

Use the following command to build and run the executable target.

```bash
cmake -S . -B build
cmake --build build
./build/RatTrig --help
```

### Build and run test suite

Use the following commands from the project's root directory to run the test suite.

```bash
cmake -S . -B build
cmake --build build
ctest --test-dir build --output-on-failure

# or simply call the executable:
./build/RatTrigTests
```

To collect code coverage information, run CMake with the `-DRATTRIG_ENABLE_COVERAGE=ON` option (GCC/Clang only) and build the `coverage` target.

### Run clang-format

Use the following commands from the project's root directory to check and fix C++ and CMake source style.
This requires _clang-format_, _cmake-format_ and _pyyaml_ to be installed on the current system.

```bash
cmake -S . -B build

# view changes
cmake --build build --target format

# apply changes
cmake --build build --target fix-format
```

See [Format.cmake](https://github.com/TheLartians/Format.cmake) for details.
These dependencies can be easily installed using pip.

```bash
pip install clang-format==18.1.2 cmake_format==0.6.13 pyyaml
```

### Build the documentation

The documentation is automatically built and [published](https://thelartians.github.io/ModernCppStarter) whenever a [GitHub Release](https://help.github.com/en/github/administering-a-repository/managing-releases-in-a-repository) is created.
To manually build documentation, call the following command.

```bash
cmake -S . -B build -DRATTRIG_BUILD_DOCS=ON
cmake --build build --target GenerateDocs
# view the docs
open build/doxygen/html/index.html
```

To build the documentation locally, you will need Doxygen, jinja2 and Pygments installed on your system.

### Build everything at once

The single root `CMakeLists.txt` defines the library, standalone executable and tests, so a single configure step builds everything.

```bash
cmake -S . -B build
cmake --build build

# run tests
./build/RatTrigTests
# format code
cmake --build build --target fix-format
# run standalone
./build/RatTrig --help
# build docs (requires -DRATTRIG_BUILD_DOCS=ON at configure time)
cmake --build build --target GenerateDocs
```

### Additional tools

#### Static analysis

clang-tidy can be enabled by configuring CMake with `-DRATTRIG_ENABLE_CLANG_TIDY=ON`; this provides a `clang-tidy` target that analyzes the public headers.

#### Code coverage

Code coverage (GCC/Clang, via gcovr) can be enabled by configuring CMake with `-DRATTRIG_ENABLE_COVERAGE=ON`; this provides a `coverage` target that runs the tests and writes an HTML report to `build/coverage/index.html`.

## ❓ FAQ

> Can I use this for header-only libraries?

Yes, however you will need to change the library type to an `INTERFACE` library as documented in the [CMakeLists.txt](CMakeLists.txt).
See [here](https://github.com/TheLartians/StaticTypeInfo) for an example header-only library based on the template.

> I don't need a standalone target / documentation. How can I get rid of it?

Simply remove the standalone / documentation directory and according github workflow file.

> Can I build the standalone and tests at the same time? / How can I tell my IDE about all subprojects?

All targets (library, standalone, tests, docs) are defined in the single root `CMakeLists.txt`, so a single `cmake -S . -B build` configuration exposes everything to your IDE at once.

> I see you are using `GLOB` to add source files in CMakeLists.txt. Isn't that evil?

Glob is considered bad because any changes to the source file structure [might not be automatically caught](https://cmake.org/cmake/help/latest/command/file.html#filesystem) by CMake's builders and you will need to manually invoke CMake on changes.
I personally prefer the `GLOB` solution for its simplicity, but feel free to change it to explicitly listing sources.

> I want create additional targets that depend on my library. Should I modify the main CMakeLists to include them?

Avoid including derived projects from the libraries CMakeLists (even though it is a common sight in the C++ world), as this effectively inverts the dependency tree and makes the build system hard to reason about.
Instead, create a new directory or project with a CMakeLists that adds the library as a dependency (e.g. like the [test_installed](test_installed/CMakeLists.txt) directory).
Depending type it might make sense move these components into a separate repositories and reference a specific commit or version of the library.
This has the advantage that individual libraries and components can be improved and updated independently.

> You recommend to add external dependencies using CPM.cmake. Will this force users of my library to use CPM.cmake as well?

[CPM.cmake](https://github.com/TheLartians/CPM.cmake) should be invisible to library users as it's a self-contained CMake Script.
If problems do arise, users can always opt-out by defining the CMake or env variable [`CPM_USE_LOCAL_PACKAGES`](https://github.com/cpm-cmake/CPM.cmake#options), which will override all calls to `CPMAddPackage` with the according `find_package` call.
This should also enable users to use the project with their favorite external C++ dependency manager, such as vcpkg or Conan.

> Can I configure and build my project offline?

No internet connection is required for building the project, however when using CPM missing dependencies are downloaded at configure time.
To avoid redundant downloads, it's highly recommended to set a CPM.cmake cache directory, e.g.: `export CPM_SOURCE_CACHE=$HOME/.cache/CPM`.
This will enable shallow clones and allow offline configurations dependencies are already available in the cache.

> Can I use CPack to create a package installer for my project?

As there are a lot of possible options and configurations, this is not (yet) in the scope of this template. See the [CPack documentation](https://cmake.org/cmake/help/latest/module/CPack.html) for more information on setting up CPack installers.

> This is too much, I just want to play with C++ code and test some libraries.

Perhaps the [MiniCppStarter](https://github.com/TheLartians/MiniCppStarter) is something for you!

## Related projects and alternatives

- [**rat-trig-simple**](https://github.com/luk036/rat-trig-simple): Simplified header-only variant (xmake/CMake, lighter CI)
- [**ModernCppStarter & PVS-Studio Static Code Analyzer**](https://github.com/viva64/pvs-studio-cmake-examples/tree/master/modern-cpp-starter): Official instructions on how to use the ModernCppStarter with the PVS-Studio Static Code Analyzer.
- [**cpp-best-practices/gui_starter_template**](https://github.com/cpp-best-practices/gui_starter_template/): A popular C++ starter project, created in 2017.
- [**filipdutescu/modern-cpp-template**](https://github.com/filipdutescu/modern-cpp-template): A recent starter using a more traditional approach for CMake structure and dependency management.
- [**vector-of-bool/pitchfork**](https://github.com/vector-of-bool/pitchfork/): Pitchfork is a Set of C++ Project Conventions.

## Star History

[![Star History Chart](https://api.star-history.com/svg?repos=luk036/rat-trig-cpp,cpp-best-practices/gui_starter_template,filipdutescu/modern-cpp-template&type=Date)](https://star-history.com/#luk036/rat-trig-cpp&cpp-best-practices/gui_starter_template&filipdutescu/modern-cpp-template&Date)
