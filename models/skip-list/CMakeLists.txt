cmake_minimum_required(VERSION 3.11)
project(SkipList C)

set(CMAKE_C_STANDARD 99)

add_executable(SkipList main.c skiplist.h skiplist.c util.h util.c)