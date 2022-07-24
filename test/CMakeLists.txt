find_package(GTest REQUIRED)

add_executable(string_test string_test.cpp)
target_include_directories(string_test PRIVATE ../include)
target_link_libraries(string_test PRIVATE gtest::gtest)


add_test(string_test string_test)