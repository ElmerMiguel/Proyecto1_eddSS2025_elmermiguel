#ifndef ARBOLAVL_H
#define ARBOLAVL_H

#pragma once
#include "../Objetos/Libro.h"
#include <iostream>
using namespace std;

struct NodoAVL {
    Libro data;
    NodoAVL* izq;
    NodoAVL* der;
    int altura;
    NodoAVL(Libro l) : data(l), izq(nullptr), der(nullptr), altura(1) {}
};

class ArbolAVL {
private:
    NodoAVL* raiz;

    int altura(NodoAVL* nodo);
    int balance(NodoAVL* nodo);
    NodoAVL* rotacionDerecha(NodoAVL* y);
    NodoAVL* rotacionIzquierda(NodoAVL* x);
    NodoAVL* insertar(NodoAVL* nodo, Libro libro);
    NodoAVL* buscar(NodoAVL* nodo, string titulo);
    NodoAVL* eliminar(NodoAVL* nodo, string titulo);
    NodoAVL* encontrarMin(NodoAVL* nodo);

    void inOrder(NodoAVL* nodo);
    void exportarDOTRec(NodoAVL* nodo, ofstream& out);
public:
    ArbolAVL();
    void insertar(Libro libro);
    Libro* buscar(string titulo);
    void mostrarInOrder();
    void exportarDOT(const string& archivo);
    bool eliminar(string titulo);
};


#endif