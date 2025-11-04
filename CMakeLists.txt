cmake_minimum_required(VERSION 3.16)
project(paoo_lab LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(paoo_lab
    src/main.cpp
)

target_include_directories(paoo_lab PRIVATE include)
