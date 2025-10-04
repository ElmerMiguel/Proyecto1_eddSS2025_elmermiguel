#ifndef ARBOLB_H
#define ARBOLB_H

#pragma once
#include "../Objetos/Libro.h"
#include "ListaLibros.h"
#include <iostream>
using namespace std;

class NodoB {
public:
    int* claves;
    Libro* valores;
    NodoB** hijos;
    int n;
    bool hoja;
    int t;
    NodoB(int _t, bool _hoja);
    void recorrer();
    NodoB* buscar(int k);
    int buscarIndice(int k);
    void insertarNoLleno(Libro libro);
    void dividirHijo(int i, NodoB* y);
    void buscarRango(int inicio, int fin, ListaLibros& lista);
    
};

class ArbolB {
private:
    NodoB* raiz;
    int t;
    void exportarDOTRec(NodoB* nodo, ofstream& out, int& id);
    void listarAniosRec(NodoB* nodo);  // AGREGAR ESTA LÍNEA
public:
    ArbolB(int _t);
    void insertar(Libro libro);
    void recorrer();
    Libro* buscar(int k);
    ListaLibros buscarPorRangoFechas(int inicio, int fin);
    void exportarDOT(const string& archivo);
    void listarAnios();               // AGREGAR AQUÍ
};


#endif