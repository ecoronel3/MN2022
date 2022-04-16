cmake_policy(SET CMP0048 NEW)
PROJECT(tp1 VERSION 1.0.0)
CMAKE_MINIMUM_REQUIRED(VERSION 3.11)

set(CMAKE_CXX_STANDARD 17)

INCLUDE_DIRECTORIES(.)

ADD_EXECUTABLE(tp1 "Main.cpp")

ADD_EXECUTABLE(BenchmarkEGvsLU "BenchmarkEGvsLU.cpp")

include(FetchContent)
FetchContent_Declare(
  googletest
  URL https://github.com/google/googletest/archive/e2239ee6043f73722e7aa812a459f54a28552929.zip
)
# For Windows: Prevent overriding the parent project's compiler/linker settings
set(gtest_force_shared_crt ON CACHE BOOL "" FORCE)
FetchContent_MakeAvailable(googletest)

enable_testing()

ADD_EXECUTABLE(tp1Test 
  "tests/VectorNTest.cpp"
  "tests/MatrixNTest.cpp"
  "tests/GaussianEliminationTest.cpp"
  "tests/BackwardSustitutionTest.cpp"
  "tests/ForwardSubstitutionTest.cpp"
  "tests/LUFactorizationTest.cpp"
  "tests/FindIsothermTest.cpp"
  "tests/AluTests.cpp"
  )

  # Test files
set(TEST_FILES_SOURCE_DIR ${CMAKE_CURRENT_SOURCE_DIR}/tests/tests_alu)

add_custom_command(TARGET tp1Test PRE_BUILD
    COMMAND ${CMAKE_COMMAND} -E copy_directory ${TEST_FILES_SOURCE_DIR} $<TARGET_FILE_DIR:tp1Test>/tests_alu
    DEPENDS ${MY_TARGET}
    COMMENT "Copying test files output directory"
)

TARGET_INCLUDE_DIRECTORIES(tp1Test PUBLIC .)
TARGET_LINK_LIBRARIES(tp1Test gtest_main)

include(GoogleTest)
gtest_discover_tests(tp1Test)

