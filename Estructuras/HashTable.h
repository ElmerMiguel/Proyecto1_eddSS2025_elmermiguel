#ifndef HASHTABLE_H
#define HASHTABLE_H

#pragma  once
#include "../Objetos/Libro.h"
#include <iostream>
using namespace std;

class HashTable {
private:
    static const int TAM = 101;
    struct Nodo{
        Libro data;
        Nodo* siguiente;
        Nodo(Libro l) : data(l), siguiente(nullptr) {}
    };
    Nodo* tabla[TAM];

    int hashFunc (string isbn);

public:
    HashTable();
    void insertar(Libro libro);
    Libro* buscar(string isbn);
    bool eliminar(string isbn);
};


#endif