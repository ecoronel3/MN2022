cmake_policy(SET CMP0048 NEW)

project(tp2 VERSION 1.0.0)
cmake_minimum_required(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

include(FetchContent)

## GoogleTest
FetchContent_Declare(
    googletest
    GIT_REPOSITORY  https://github.com/google/googletest.git
    GIT_TAG         release-1.11.0
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)

## Eigen
FetchContent_Declare(
    eigen
    GIT_REPOSITORY  https://gitlab.com/libeigen/eigen.git
    GIT_TAG         3.4.0
)

enable_testing()

FetchContent_MakeAvailable(googletest eigen)


set(EIGEN3_INCLUDE_DIR ${eigen_SOURCE_DIR})

include_directories(EIGEN3_INCLUDE_DIR)

## OCR Library
add_library(libocr STATIC 
    "libocr/PCA.cpp"
    "libocr/powerIteration.cpp"
    "libocr/randVector.cpp"
    )

target_include_directories(libocr PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(libocr eigen_blas_static)

## Test OCR library
add_executable(tp2Test 
  "tests/PCATests.cpp"
  "tests/powerIterationTests.cpp"
  )

target_include_directories(tp2Test PUBLIC .)

target_include_directories(tp2Test PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(tp2Test gtest_main libocr)

include(GoogleTest)
gtest_discover_tests(tp2Test)

