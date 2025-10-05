#ifndef ARBOLBST_H
#define ARBOLBST_H

#pragma once
#include "../Objetos/Libro.h"
#include <iostream>
#include <fstream>
using namespace std;

struct NodoBST {
    Libro data;
    NodoBST* izq;
    NodoBST* der;
    
    NodoBST(Libro libro) : data(libro), izq(nullptr), der(nullptr) {}
};

class ArbolBST {
private:
    NodoBST* raiz;
    
    NodoBST* insertar(NodoBST* nodo, Libro libro);
    NodoBST* buscar(NodoBST* nodo, string isbn);
    NodoBST* eliminar(NodoBST* nodo, string isbn);
    NodoBST* encontrarMin(NodoBST* nodo);
    void inOrder(NodoBST* nodo);
    void exportarDOTRec(NodoBST* nodo, ofstream& out);
    void destruir(NodoBST* nodo);
     void listarISBNsRec(NodoBST* nodo);

public:
    ArbolBST();
    ~ArbolBST();
    
    void insertar(Libro libro);
    Libro* buscar(string isbn);
    bool eliminar(string isbn);
    void mostrarInOrder();
    void exportarDOT(const string& archivo);
    void listarISBNs();              
};

#endif