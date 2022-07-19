cmake_minimum_required(VERSION 3.0.0)
project(kstring VERSION 0.1.0)

set(CMAKE_CXX_STANDARD 20)

include(CTest)

add_compile_options(-Wall -Wextra -Werror)

add_library(kstring INTERFACE)
target_include_directories(kstring INTERFACE include)

install(DIRECTORY include/ DESTINATION include)
