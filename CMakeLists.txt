cmake_minimum_required(VERSION 3.9)
project(freshman_proj_c C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})
find_package(codecov)

add_executable(freshman_proj_c main.c core/Database.h core/TableTest.h core/Database.c)
add_coverage(freshman_proj_c)

enable_testing()

# Main test
add_test (MainRuns freshman_proj_c)

# Unit Test
option(BUILD_TEST "Build the unit tests" ON)
if(BUILD_TEST)
    add_subdirectory(externals)
    add_subdirectory(test)
endif()

# evaluate coverage
coverage_evaluate()