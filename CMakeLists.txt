cmake_minimum_required(VERSION 3.19)
project(binarytree)

set(CMAKE_CXX_STANDARD 11)
add_compile_options(-std=c++2a -Werror -Wsign-conversion)
add_executable(demo Demo.cpp sources/BinaryTree.cpp sources/BinaryTree.hpp)
add_executable(test Test.cpp sources/BinaryTree.cpp sources/BinaryTree.hpp)
add_executable(test1 StudentTest1.cpp sources/BinaryTree.cpp sources/BinaryTree.hpp)
add_executable(test2 StudentTest2.cpp sources/BinaryTree.cpp sources/BinaryTree.hpp)