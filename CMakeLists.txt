cmake_minimum_required(VERSION 3.17)
project(avl_tree)

set(CMAKE_CXX_STANDARD 14)

find_package(SFML 2.5 COMPONENTS graphics REQUIRED)

add_executable(avl_tree main.cpp Tree.cpp Tree.h)

target_link_libraries(avl_tree sfml-graphics)