cmake_minimum_required(VERSION 3.27)
project(pruefung)

set(CMAKE_CXX_STANDARD 20)

add_executable(pruefung main.cpp
        Implementation/IOManager.cpp
        Implementation/Menu.cpp
        Implementation/Mitarbeiter.cpp
        Implementation/Utilities.cpp
        Implementation/Mitarbeiterdatenbank.cpp)
