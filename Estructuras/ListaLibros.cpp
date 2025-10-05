
#include "ListaLibros.h"

ListaLibros::ListaLibros() {
    cabeza = nullptr;
}

void ListaLibros::insertar(Libro libro) {
    NodoLista* nuevo = new NodoLista(libro);
    nuevo->siguiente = cabeza;
    cabeza = nuevo;
}

bool ListaLibros::eliminar(string isbn) {
    NodoLista* actual = cabeza;
    NodoLista* anterior = nullptr;

    while (actual != nullptr){
        if(actual->data.isbn == isbn) {
            if(anterior) anterior->siguiente = actual->siguiente;
            else cabeza = actual->siguiente;
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}

Libro* ListaLibros::buscarPorTitulo(string titulo) {
    NodoLista* actual = cabeza;
    while (actual != nullptr){
        if(actual->data.titulo == titulo) return &actual->data;
        actual = actual->siguiente;
    }
    return nullptr;
}

Libro* ListaLibros::buscarPorISBN(string isbn){
    NodoLista* actual = cabeza;
    while (actual != nullptr){
        if(actual->data.isbn == isbn) return &actual->data;
        actual = actual->siguiente;
    }
    return nullptr;
}


void ListaLibros::mostrarTodos() {
    NodoLista* actual = cabeza;
    while (actual != nullptr){
        cout << actual->data.titulo << " (" << actual->data.isbn << ") " << endl;
        actual = actual->siguiente;
    }
}