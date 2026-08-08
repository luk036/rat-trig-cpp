cmake_minimum_required(VERSION 3.14)

project(RatTrigInstalledTest LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# Find dependencies first - RatTrigConfig.cmake references fmt and Fractions (installed alongside
# the library by `cmake --install`).
find_package(fmt REQUIRED)
find_package(Fractions REQUIRED)
find_package(RatTrig REQUIRED)

add_executable(ratrig_installed_test main.cpp)
target_link_libraries(ratrig_installed_test PRIVATE RatTrig::RatTrig)

enable_testing()
add_test(NAME ratrig_installed_test COMMAND ratrig_installed_test)
