cmake_minimum_required(VERSION 3.10)
set(CMAKE_CXX_STANDARD 17)

project(TicTacToe)

# Using GTest for unit testing
include(FetchContent)
FetchContent_Declare(
      googletest
      GIT_REPOSITORY https://github.com/google/googletest.git
      GIT_TAG        v1.17.0 # Or use a specific commit hash for a precise version
    )

FetchContent_MakeAvailable(googletest)
include(CTest)
add_subdirectory(src)
add_subdirectory(tests)
