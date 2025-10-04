
#include "BibliotecaMagica.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
using namespace std::chrono;

BibliotecaMagica::BibliotecaMagica() : arbolFechas(3), arbolGeneros(2) {}

void BibliotecaMagica::agregarLibro(Libro libro) {
    listaSecuencial.insertar(libro);
    arbolTitulos.insertar(libro);
    arbolFechas.insertar(libro);
    tablaISBN.insertar(libro);
    arbolGeneros.insertar(libro);
}

void BibliotecaMagica::eliminarLibro(string isbn) {
    listaSecuencial.eliminar(isbn);
    tablaISBN.eliminar(isbn);
    // Falta implementar eliminaciones en AVL y B
}

Libro* BibliotecaMagica::buscarPorTitulo(string titulo) {
    return arbolTitulos.buscar(titulo);
}

Libro* BibliotecaMagica::buscarPorISBN(string isbn) {
    return tablaISBN.buscar(isbn);
}

Libro* BibliotecaMagica::buscarPorFecha(int anio) {
    return arbolFechas.buscar(anio);
}

void BibliotecaMagica::mostrarPorTitulo() {
    arbolTitulos.mostrarInOrder();
}

vector<Libro> BibliotecaMagica::buscarPorGenero(string genero) {
    return arbolGeneros.buscar(genero);
}

void BibliotecaMagica::cargarDesdeCSV(const std::string& rutaArchivo) {
    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << rutaArchivo << std::endl;
        return;
    }

    std::string linea;
    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string titulo, isbn, genero, anioStr, autor;

        // Quitar comillas y separar por comas
        if (!getline(ss, titulo, ',')) continue;
        if (!getline(ss, isbn, ',')) continue;
        if (!getline(ss, genero, ',')) continue;
        if (!getline(ss, anioStr, ',')) continue;
        if (!getline(ss, autor, ',')) continue;

        // Eliminar comillas si las hay
        auto clean = [](std::string& s) {
            if (!s.empty() && s.front() == '"') s.erase(0, 1);
            if (!s.empty() && s.back() == '"') s.pop_back();
        };
        clean(titulo);
        clean(isbn);
        clean(genero);
        clean(anioStr);
        clean(autor);

        // Validar año numérico
        int anio;
        try {
            anio = std::stoi(anioStr);
        } catch (...) {
            std::cerr << "Linea ignorada (anio invalido): " << linea << std::endl;
            continue;
        }

        // Validar ISBN único
        if (buscarPorISBN(isbn) != nullptr) {
            std::cerr << "ISBN duplicado, libro ignorado: " << isbn << std::endl;
            continue;
        }

        Libro libro(titulo, isbn, genero, anio, autor);
        agregarLibro(libro);
    }

    archivo.close();
    std::cout << "Carga desde CSV completada." << std::endl;
}

ListaLibros BibliotecaMagica::buscarPorRangoFechas(int inicio, int fin) {
    return arbolFechas.buscarPorRangoFechas(inicio, fin);
}

//Medicion
long long BibliotecaMagica::medirBusquedaTituloSecuencial(const string& titulo) {
    auto start = high_resolution_clock::now();
    listaSecuencial.buscarPorTitulo(titulo);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

long long BibliotecaMagica::medirBusquedaTituloAVL(const string& titulo) {
    auto start = high_resolution_clock::now();
    arbolTitulos.buscar(titulo);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

long long BibliotecaMagica::medirBusquedaISBNHash(const string& isbn) {
    auto start = high_resolution_clock::now();
    tablaISBN.buscar(isbn);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

long long BibliotecaMagica::medirBusquedaISBNSecuencial(const string& isbn) {
    auto start = high_resolution_clock::now();
    listaSecuencial.buscarPorISBN(isbn);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

void BibliotecaMagica::exportarAVL(const string& archivo) {
    arbolTitulos.exportarDOT(archivo);
}

void BibliotecaMagica::exportarB(const string& archivo) {
    arbolFechas.exportarDOT(archivo);
}

void BibliotecaMagica::exportarBPlus(const string& archivo) {
    arbolGeneros.exportarDOT(archivo);
}
