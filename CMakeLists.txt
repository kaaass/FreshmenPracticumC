cmake_minimum_required(VERSION 3.9)
project(freshman_proj_c C)

set(CMAKE_C_STANDARD 99)

add_executable(freshman_proj_c main.c core/Database.h core/TableTest.h core/Database.c)