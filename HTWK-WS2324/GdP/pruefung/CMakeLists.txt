cmake_minimum_required(VERSION 3.27)
project(pruefung)

set(CMAKE_CXX_STANDARD 20)

add_executable(pruefung main.cpp
        IOManager.cpp
        Menu.cpp
        Mitarbeiter.cpp
        Utilities.cpp
        Mitarbeiterdatenbank.cpp
        MenuBuilder.cpp)

target_compile_options(pruefung PRIVATE -Weverything -Wno-c++98-compat -Wall)