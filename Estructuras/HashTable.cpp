
#include "HashTable.h"

int HashTable::hashFunc(string isbn) {
    int hash = 0;
    for (char c : isbn) hash = (hash * 31 + c) % TAM;
    return hash;
}

HashTable::HashTable() {
    for (int i = 0; i < TAM; i++) tabla[i] = nullptr;
}

void HashTable::insertar(Libro libro) {
    int idx = hashFunc(libro.isbn);
    Nodo* nuevo = new Nodo(libro);
    nuevo->siguiente = tabla[idx];
    tabla[idx] = nuevo;
}

Libro* HashTable::buscar(string isbn) {
    int idx = hashFunc(isbn);
    Nodo* actual = tabla[idx];
    while (actual) {
        if (actual->data.isbn == isbn) return &actual->data;
        actual = actual->siguiente;
    }
    return nullptr;
}

bool HashTable::eliminar(string isbn) {
    int idx = hashFunc(isbn);
    Nodo* actual = tabla[idx];
    Nodo* anterior = nullptr;
    while (actual) {
        if (actual->data.isbn == isbn) {
            if (anterior) anterior->siguiente = actual->siguiente;
            else tabla[idx] = actual->siguiente;
            delete actual;
            return true;
        }
        anterior = actual;
        actual = actual->siguiente;
    }
    return false;
}
