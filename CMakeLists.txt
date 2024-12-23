cmake_minimum_required(VERSION 3.29)
project(trabalho_grafos)

set(CMAKE_CXX_STANDARD 20)

add_executable(trabalho_grafos main.cpp)
add_executable(lista-encadeada
        src/lista-encadeada/Vertice.cpp
        src/lista-encadeada/Vertice.h
        src/lista-encadeada/Aresta.cpp
        src/lista-encadeada/Aresta.h
        src/lista-encadeada/GrafoLista.cpp
        src/lista-encadeada/GrafoLista.h
        src/lista-encadeada/main.cpp
)
