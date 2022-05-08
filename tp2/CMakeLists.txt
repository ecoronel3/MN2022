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

set(LIBMN_SOURCES 
    "mn/PCA.cpp"
    "mn/powerIteration.cpp"
    "mn/kNNClassifier.cpp"
    "mn/randVector.cpp"
)
add_library(libmn STATIC ${LIBMN_SOURCES})
target_include_directories(libmn PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(libmn eigen_blas_static)

## Test OCR library
set(TP2TEST_SOURCES
    "tests/PCATests.cpp"
    "tests/powerIterationTests.cpp"
    "tests/kNNClassifierTests.cpp"
)
add_executable(tp2Test ${TP2TEST_SOURCES})
target_include_directories(tp2Test PUBLIC .)
target_include_directories(tp2Test PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(tp2Test gtest_main libmn)

include(GoogleTest)
gtest_discover_tests(tp2Test)

