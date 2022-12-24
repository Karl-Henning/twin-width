cmake_minimum_required(VERSION 3.23)
project(twin_width)

set(CMAKE_CXX_STANDARD 20)

# Now simply link against gtest or gtest_main as needed. Eg
add_executable(twin_width main.cpp graph.cpp graph.h)