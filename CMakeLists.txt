cmake_minimum_required(VERSION 3.27)
project(BuscaMinas)

set(CMAKE_CXX_STANDARD 23)

add_executable(BuscaMinas main.cpp
        cmake-build-debug/Ordenamiendo_burbuja.cpp
        OrdenamientoBurbuja.cpp
)
