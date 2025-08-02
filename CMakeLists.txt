cmake_minimum_required(VERSION 3.15)
set(CMAKE_CXX_STANDARD 17)

project(rayban VERSION 1.0
    DESCRIPTION "C++ implementation of the Ray Tracer Challenge"
    LANGUAGES C CXX)


add_executable(${PROJECT_NAME}
    src/main.cpp
)

include_directories(include)

enable_testing()

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_MULTITHREADED ON)
set(Boost_USE_STATIC_RUNTIME OFF)
find_package(Boost 1.55 REQUIRED COMPONENTS unit_test_framework)

add_subdirectory(tests)
