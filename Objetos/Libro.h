
#ifndef LIBRO_H
#define LIBRO_H

#pragma once
#include <string>
using namespace std;

class Libro {
public:
    string titulo;
    string isbn;
    string genero;
    int anio;
    string autor;

    Libro();
    Libro(string t, string i, string g, int a, string au);
};


#endif