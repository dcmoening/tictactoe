add_library(baxter
    Baxter.hpp
    Baxter.cpp)

target_link_libraries(baxter
    GTest::gtest
    tictactoe
)

target_include_directories(baxter PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})