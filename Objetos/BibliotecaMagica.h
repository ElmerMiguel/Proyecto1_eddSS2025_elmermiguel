
#ifndef BIBLIOTECAMAGICA_H
#define BIBLIOTECAMAGICA_H

#pragma once
#include "../Estructuras/ListaLibros.h"
#include "../Estructuras/ArbolAVL.h"
#include "../Estructuras/ArbolB.h"
#include "../Estructuras/HashTable.h"
#include "../Estructuras/ArbolBPlus.h"
#include <vector>
#include <string>
#include <chrono>

class BibliotecaMagica {
private:
    ListaLibros listaSecuencial;
    ArbolAVL arbolTitulos;
    ArbolB arbolFechas;
    HashTable tablaISBN;
    ArbolBPlus arbolGeneros;

public:
    BibliotecaMagica();
    void agregarLibro(Libro libro);
    void eliminarLibro(string isbn);

    Libro* buscarPorTitulo(string titulo);
    Libro* buscarPorISBN(string isbn);
    Libro* buscarPorFecha(int anio);
    vector<Libro> buscarPorGenero(string genero);

    void mostrarPorTitulo();

    void cargarDesdeCSV(const std::string& rutaArchivo);

    ListaLibros buscarPorRangoFechas(int inicio, int fin);

    long long medirBusquedaTituloSecuencial(const string& titulo);
    long long medirBusquedaTituloAVL(const string& titulo);
    long long medirBusquedaISBNHash(const string& isbn);
    long long medirBusquedaISBNSecuencial(const string& isbn);

    void exportarAVL(const string& archivo);
    void exportarB(const string& archivo);
    void exportarBPlus(const string& archivo);


};


#endif 
