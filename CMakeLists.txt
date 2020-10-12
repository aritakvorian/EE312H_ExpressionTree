cmake_minimum_required(VERSION 3.13)
project(Project8)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Project8
        Input.cpp
        Input.o
        Makefile
        Parse.h
        test1.blip
        test2.blip
        test3.blip
        test4.blip
        test5.blip
        ExpressionTree.cpp
        ExpressionTree.hpp
        SymbolTable.cpp
        SymbolTable.hpp
        Project8.cpp
       )