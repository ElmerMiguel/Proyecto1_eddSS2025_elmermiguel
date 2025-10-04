
#ifndef LISTALIBROS_H
#define LISTALIBROS_H

#include "../Objetos/Libro.h"
#include <iostream>
using namespace std;

struct NodoLista {
    Libro data;
    NodoLista* siguiente;
    NodoLista(Libro l) : data(l), siguiente(nullptr) {}
};

class ListaLibros {
private:
    NodoLista* cabeza;
public:
    ListaLibros();
    void insertar(Libro libro);
    bool eliminar(string isbn);
    Libro* buscarPorTitulo(string titulo);
    Libro* buscarPorISBN(string isbn);
    void mostrarTodos();
};


#endif