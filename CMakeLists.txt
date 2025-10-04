cmake_minimum_required(VERSION 3.30)
project(Proyecto1_eddSS2025)

set(CMAKE_CXX_STANDARD 20)

add_executable(Proyecto1_eddSS2025 main.cpp
        Estructuras/ArbolAVL.cpp
        Estructuras/ArbolAVL.h
        Estructuras/ArbolB.cpp
        Estructuras/ArbolB.h
        Estructuras/ArbolBPlus.cpp
        Estructuras/ArbolBPlus.h
        Estructuras/hola.cpp
        Estructuras/hola.h
        Estructuras/HashTable.cpp
        Estructuras/HashTable.h
        Estructuras/ListaLibros.cpp
        Estructuras/ListaLibros.h
        Menu/Menu.cpp
        Menu/Menu.h
        Objetos/BibliotecaMagica.cpp
        Objetos/BibliotecaMagica.h
        Objetos/Libro.cpp
        Objetos/Libro.h)
