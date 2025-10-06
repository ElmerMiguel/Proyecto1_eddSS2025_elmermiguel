#include "ListaLibros.h"
#include <iomanip>
#include <algorithm>
#include <string>
using namespace std;

using namespace std;

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
    if (cabeza == nullptr) {
        cout << "No hay libros en el rango especificado." << endl;
        return;
    }

    // Calcular anchos máximos dinámicamente
    int maxTitulo = 6; // "TITULO"
    int maxAutor = 5;  // "AUTOR"
    int maxAnio = 3;   // "AÑO"
    int maxISBN = 4;   // "ISBN"

    NodoLista* actual = cabeza;
    int contador = 0;
    while (actual != nullptr) {
        maxTitulo = max(maxTitulo, (int)actual->data.titulo.length());
        maxAutor = max(maxAutor, (int)actual->data.autor.length());
        maxAnio = max(maxAnio, (int)to_string(actual->data.anio).length());
        maxISBN = max(maxISBN, (int)actual->data.isbn.length());
        actual = actual->siguiente;
        contador++;
    }

    cout << "\nTotal de libros encontrados: " << contador << endl;
    cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;

    cout << left << setw(maxTitulo + 2) << "TITULO"
         << left << setw(maxAutor + 2) << "AUTOR"
         << left << setw(maxAnio + 4) << "AÑO"
         << left << setw(maxISBN + 2) << "ISBN" << endl;

    cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;

    actual = cabeza;
    while (actual != nullptr) {
        cout << left << setw(maxTitulo + 2) << actual->data.titulo
             << left << setw(maxAutor + 2) << actual->data.autor
             << left << setw(maxAnio + 4) << actual->data.anio
             << left << setw(maxISBN + 2) << actual->data.isbn
             << endl;
        actual = actual->siguiente;
    }

    cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;
}
