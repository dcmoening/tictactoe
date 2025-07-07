add_library(ultron
    Ultron.hpp
    Ultron.cpp)

target_link_libraries(ultron
    tictactoe
)

target_include_directories(ultron PUBLIC ${CMAKE_CURRENT_SOURCE_DIR})