enable_testing()

add_executable(baxtertest
  BaxterTest.cpp
)
target_link_libraries(baxtertest
  baxter
  tictactoe
  GTest::gtest
)

include(GoogleTest)
gtest_discover_tests(baxtertest)