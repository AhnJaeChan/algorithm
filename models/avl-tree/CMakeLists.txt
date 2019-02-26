cmake_minimum_required(VERSION 3.11)
project(AVLTree C)

set(CMAKE_C_STANDARD 99)

add_executable(AVLTree main.c avltree.c avltree.h util.c util.h)