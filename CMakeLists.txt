cmake_minimum_required(VERSION 3.21)

project(fastmath VERSION 0.1.0 LANGUAGES CXX)

include(FetchContent)
include(CTest)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

option(FASTMATH_ENABLE_TESTS "Build tests" ON)
option(FASTMATH_ENABLE_BENCHMARKS "Build benchmarks" ON)
option(FASTMATH_ENABLE_FAST_MATH "Enable -ffast-math" OFF)

if(FASTMATH_ENABLE_FAST_MATH)
  add_compile_options(-ffast-math -fno-finite-math-only)
endif()

set(FASTMATH_SOURCES
    src/f_acos.cpp
    src/f_asin.cpp
    src/f_atan.cpp
    src/f_cos.cpp
    src/f_cosh.cpp
    src/f_exp.cpp
    src/f_log.cpp
    src/f_pow.cpp
    src/f_sin.cpp
    src/f_sinh.cpp
    src/f_sqrt.cpp
    src/f_tan.cpp
    src/f_tanh.cpp)

add_library(fastmath SHARED ${FASTMATH_SOURCES})
target_include_directories(fastmath PUBLIC include PRIVATE src)
target_compile_features(fastmath PUBLIC cxx_std_20)

if(FASTMATH_ENABLE_TESTS)
  FetchContent_Declare(
      catch2
      GIT_REPOSITORY https://github.com/catchorg/Catch2.git
      GIT_TAG v3.6.0)
  FetchContent_MakeAvailable(catch2)

  add_executable(fastmath_tests test/fastmath_tests.cpp)
  target_link_libraries(fastmath_tests PRIVATE fastmath Catch2::Catch2WithMain)

  include(Catch)
  catch_discover_tests(fastmath_tests)
endif()

if(FASTMATH_ENABLE_BENCHMARKS)
  set(BENCHMARK_ENABLE_TESTING OFF CACHE BOOL "" FORCE)
  FetchContent_Declare(
      benchmark
      GIT_REPOSITORY https://github.com/google/benchmark.git
      GIT_TAG v1.9.0)
  FetchContent_MakeAvailable(benchmark)

  add_executable(fastmath_bench bench/fastmath_bench.cpp)
  target_link_libraries(fastmath_bench PRIVATE fastmath benchmark::benchmark_main)

  add_custom_target(
      run_benchmarks
      COMMAND $<TARGET_FILE:fastmath_bench>
      DEPENDS fastmath_bench
      WORKING_DIRECTORY ${CMAKE_SOURCE_DIR}
      USES_TERMINAL
      COMMENT "Running fastmath benchmarks")
endif()
