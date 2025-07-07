
add_subdirectory(Tictactoe)
add_subdirectory(Baxter)
add_subdirectory(Ultron)

add_executable(main
    main.cpp)

target_link_libraries(main
    tictactoe
    ultron
    baxter
)
