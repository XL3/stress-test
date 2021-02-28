cmake_minimum_required(VERSION 3.0.0)
project(stress-test VERSION 0.1.0)

add_executable(stress-test main.cpp)
set_property(TARGET stress-test PROPERTY CXX_STANDARD 17)