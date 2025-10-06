#ifndef ARBOLBPLUS_H
#define ARBOLBPLUS_H

#pragma once
#include "../Objetos/Libro.h"
#include <iostream>
#include <vector>
using namespace std;

class NodoBPlus {
public:
    bool hoja;
    vector<string> claves;
    vector<NodoBPlus*> hijos;
    vector<vector<Libro>> valores;
    NodoBPlus* siguiente;

    NodoBPlus(bool esHoja);
};

class ArbolBPlus {
private:
    NodoBPlus* raiz;
    int t; // grado mínimo

    void insertarInterno(NodoBPlus* nodo, const Libro& libro, const string& genero);
    void dividirNodo(NodoBPlus* padre, int i, NodoBPlus* hijo);
    void mostrarRecursivo(NodoBPlus* nodo, int nivel);
    void exportarDOTRec(NodoBPlus* nodo, ofstream& out, int& id);
    void agregarEnlacesHojas(ofstream& out); 
    int contarNodosInternos(NodoBPlus* nodo);
    void recopilarIdsHojas(NodoBPlus* nodo, int& id, vector<int>& idHojas); 
     

public:
    ArbolBPlus(int _t = 2); // por defecto grado 2
    void insertar(const Libro& libro);
    vector<Libro> buscar(const string& genero);
    void mostrarTodos();
    void exportarDOT(const string& archivo);
    void listarGeneros();
    bool eliminar(const string& genero, const string& isbn); 
   
};


#endif