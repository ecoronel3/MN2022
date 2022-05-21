cmake_policy(SET CMP0048 NEW)


# if(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)
#     set(CMAKE_INSTALL_PREFIX
#         ${CMAKE_CURRENT_SOURCE_DIR} CACHE PATH "install prefix" FORCE
#     )
# endif(CMAKE_INSTALL_PREFIX_INITIALIZED_TO_DEFAULT)

set(CMAKE_INSTALL_PREFIX
    ${CMAKE_CURRENT_SOURCE_DIR}/install CACHE PATH "install prefix" FORCE
)

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

## pybind11
FetchContent_Declare(
    pybind11
    GIT_REPOSITORY  https://github.com/pybind/pybind11.git
    GIT_TAG         v2.9.2
)

enable_testing()

FetchContent_MakeAvailable(googletest eigen pybind11)

set(EIGEN3_INCLUDE_DIR ${eigen_SOURCE_DIR})
set(PYBIND11_INCLUDE_DIR ${pybind11_SOURCE_DIR}/include)

# Python
find_package(PythonLibs REQUIRED)

## MN Library
set(LIBMN_SOURCES 
    "mn/PCA.cpp"
    "mn/powerIteration.cpp"
    "mn/kNNClassifier.cpp"
    "mn/randVector.cpp"
)
add_library(libmn STATIC ${LIBMN_SOURCES})
set_target_properties(libmn PROPERTIES POSITION_INDEPENDENT_CODE ON)
target_include_directories(libmn PRIVATE ${EIGEN3_INCLUDE_DIR})
target_link_libraries(libmn eigen_blas_static)

## Test MN library
set(TP2TEST_SOURCES
    "tests/PCATests.cpp"
    "tests/powerIterationTests.cpp"
    "tests/kNNClassifierTests.cpp"
)
add_executable(tp2Test ${TP2TEST_SOURCES})
target_include_directories(tp2Test PRIVATE . ${EIGEN3_INCLUDE_DIR})
target_link_libraries(tp2Test gtest_main libmn)

## Python bindings for MN Library
set(MNPY_SOURCES
    "mnpy/bindings.cpp"
)

add_library(mnpy MODULE ${MNPY_SOURCES})
target_include_directories(mnpy PRIVATE . ${EIGEN3_INCLUDE_DIR} ${PYTHON_INCLUDE_DIRS} ${PYBIND11_INCLUDE_DIR})
target_link_libraries(mnpy PRIVATE pybind11::module pybind11::lto pybind11::windows_extras libmn)

pybind11_extension(mnpy)
pybind11_strip(mnpy)

set_target_properties(mnpy PROPERTIES CXX_VISIBILITY_PRESET "hidden"
                                         CUDA_VISIBILITY_PRESET "hidden")

# set(MNPY_INSTALL_PATH ${CMAKE_INSTALL_PREFIX}/scripts)
install(TARGETS mnpy LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR} )

# pybind11_add_module(mnpy ${MNPY_SOURCES})

include(GoogleTest)
gtest_discover_tests(tp2Test)

