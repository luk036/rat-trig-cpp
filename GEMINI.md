# GEMINI Analysis of rat-trig-cpp

## Project Overview

This is a C++ project that implements a library for Rational Trigonometry. The project is structured using modern CMake practices, with a clear separation between the library code, tests, and a standalone executable. It also includes support for code formatting, documentation generation, and continuous integration.

**Key Technologies:**

*   C++
*   CMake
*   Doxygen
*   GitHub Actions
*   clang-format

**Architecture:**

The project is divided into the following main components:

*   **`include/rattrig`**: The public interface of the `rat-trig-cpp` library.
*   **`source`**: The implementation of the library.
*   **`test`**: The test suite for the library, using the `doctest` framework.
*   **`standalone`**: A simple command-line executable that demonstrates the use of the library.
*   **`documentation`**: The Doxygen configuration for generating API documentation.
*   **`all`**: A top-level CMake project that builds all the sub-projects together.

## Building and Running

### Build everything at once

```bash
cmake -S all -B build
cmake --build build
```

### Build and run the standalone target

```bash
cmake -S standalone -B build/standalone
cmake --build build/standalone
./build/standalone/RatTrig --help
```

### Build and run test suite

```bash
cmake -S test -B build/test
cmake --build build/test
CTEST_OUTPUT_ON_FAILURE=1 cmake --build build/test --target test
```

### Build the documentation

```bash
cmake -S documentation -B build/doc
cmake --build build/doc --target GenerateDocs
```

## Development Conventions

### Coding Style

The project uses `clang-format` to enforce a consistent coding style, based on the Google C++ Style Guide. The configuration is defined in the `.clang-format` file.

To check and fix the code style, run the following commands:

```bash
cmake -S test -B build/test

# view changes
cmake --build build/test --target format

# apply changes
cmake --build build/test --target fix-format
```

### Testing

The project uses the `doctest` framework for unit testing. The tests are located in the `test/source` directory.

### Dependencies

The project uses `CPM.cmake` to manage its dependencies. The dependencies are declared in the `CMakeLists.txt` files.
