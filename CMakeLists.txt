cmake_minimum_required(VERSION 3.9)
project(freshman_proj_c C)

set(CMAKE_C_STANDARD 99)

set(CMAKE_MODULE_PATH "${CMAKE_SOURCE_DIR}/externals/CMake-codecov/cmake" ${CMAKE_MODULE_PATH})
find_package(codecov)

add_subdirectory(externals)

aux_source_directory(core module_core)
aux_source_directory(util module_util)
aux_source_directory(data module_data)

set(modules
        ${module_core}
        ${module_util}
        ${module_data})

add_executable(freshman_proj_c main.c ${libs} ${modules})
add_coverage(freshman_proj_c)

enable_testing()

# Main test
add_test (MainRuns freshman_proj_c)

# Unit Test
option(BUILD_TEST "Build the unit tests" ON)
if(BUILD_TEST)
    add_subdirectory(test)
endif()

# evaluate coverage
coverage_evaluate()