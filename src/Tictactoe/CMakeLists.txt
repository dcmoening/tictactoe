add_library(tictactoe INTERFACE
    Tictactoe.hpp)

target_include_directories(tictactoe INTERFACE ${CMAKE_CURRENT_SOURCE_DIR})