cmake_minimum_required(VERSION 3.0.0)
project(kstring VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

add_compile_options(-Wall -Wextra -Werror)


option(ENABLE_TEST "if test is enabled" ON)

if(ENABLE_TEST)
    include(CTest)
    add_compile_options(-fsanitize=address -g --coverage)
    add_link_options(-fsanitize=address --coverage)
    add_subdirectory(test)
endif()


add_library(kstring INTERFACE)
target_include_directories(kstring INTERFACE include)

install(DIRECTORY include/ DESTINATION include)
