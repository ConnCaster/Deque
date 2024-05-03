# CATCH2
find_package(Catch2 3 REQUIRED PATHS "/home/user/dir/programming/C++/Alexey_CPP/deps/catch2")

add_executable(test test.cpp)
target_include_directories(test PUBLIC "/home/user/dir/programming/C++/Alexey_CPP/deps/catch2/include" ../)
target_link_libraries(test PUBLIC Catch2::Catch2WithMain)


# GTEST
enable_testing()
find_package(GTest REQUIRED PATHS "/home/user/dir/programming/C++/Alexey_CPP/deps/gtest")

add_executable(
        test_gtest
        test_gtest.cpp
)
target_link_libraries(
        test_gtest
        GTest::gtest_main
)

target_include_directories(test_gtest PUBLIC "/home/user/dir/programming/C++/Alexey_CPP/deps/gtest/include" ../)
