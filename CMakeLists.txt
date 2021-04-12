cmake_minimum_required(VERSION 3.15)
project(Recherche)

set(CMAKE_CXX_STANDARD 14)

include_directories(.)

add_executable(Recherche
        page.cpp
        page.hpp
        resultat.cpp
        resultat.hpp
        tests.cpp)
