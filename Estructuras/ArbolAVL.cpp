#include "ArbolAVL.h"
#include <fstream>

ArbolAVL::ArbolAVL() { raiz = nullptr; }

int ArbolAVL::altura(NodoAVL* nodo) {
    return nodo ? nodo->altura : 0;
}

int ArbolAVL::balance(NodoAVL* nodo) {
    return nodo ? altura(nodo->izq) - altura(nodo->der) : 0;
}

NodoAVL* ArbolAVL::rotacionDerecha(NodoAVL* y) {
    NodoAVL* x = y->izq;
    NodoAVL* T2 = x->der;
    x->der = y;
    y->izq = T2;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    return x;
}

NodoAVL* ArbolAVL::rotacionIzquierda(NodoAVL* x) {
    NodoAVL* y = x->der;
    NodoAVL* T2 = y->izq;
    y->izq = x;
    x->der = T2;
    x->altura = max(altura(x->izq), altura(x->der)) + 1;
    y->altura = max(altura(y->izq), altura(y->der)) + 1;
    return y;
}

NodoAVL* ArbolAVL::insertar(NodoAVL* nodo, Libro libro) {
    if (!nodo) return new NodoAVL(libro);

    if (libro.titulo < nodo->data.titulo)
        nodo->izq = insertar(nodo->izq, libro);
    else if (libro.titulo > nodo->data.titulo)
        nodo->der = insertar(nodo->der, libro);
    else
        return nodo; // duplicado

    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));
    int balanceFactor = balance(nodo);

    if (balanceFactor > 1 && libro.titulo < nodo->izq->data.titulo)
        return rotacionDerecha(nodo);
    if (balanceFactor < -1 && libro.titulo > nodo->der->data.titulo)
        return rotacionIzquierda(nodo);
    if (balanceFactor > 1 && libro.titulo > nodo->izq->data.titulo) {
        nodo->izq = rotacionIzquierda(nodo->izq);
        return rotacionDerecha(nodo);
    }
    if (balanceFactor < -1 && libro.titulo < nodo->der->data.titulo) {
        nodo->der = rotacionDerecha(nodo->der);
        return rotacionIzquierda(nodo);
    }
    return nodo;
}

NodoAVL* ArbolAVL::buscar(NodoAVL* nodo, string titulo) {
    if (!nodo) return nullptr;
    if (titulo == nodo->data.titulo) return nodo;
    if (titulo < nodo->data.titulo) return buscar(nodo->izq, titulo);
    return buscar(nodo->der, titulo);
}

void ArbolAVL::inOrder(NodoAVL* nodo) {
    if (!nodo) return;
    inOrder(nodo->izq);
    cout << nodo->data.titulo << endl;
    inOrder(nodo->der);
}

void ArbolAVL::insertar(Libro libro) {
    raiz = insertar(raiz, libro);
}

Libro* ArbolAVL::buscar(string titulo) {
    NodoAVL* nodo = buscar(raiz, titulo);
    return nodo ? &nodo->data : nullptr;
}

void ArbolAVL::mostrarInOrder() {
    inOrder(raiz);
}

void ArbolAVL::exportarDOT(const string& archivo) {
    ofstream out(archivo);
    if (!out.is_open()) {
        cerr << "No se pudo abrir el archivo DOT." << endl;
        return;
    }

    out << "digraph AVL {\n";
    out << "node [shape=circle, style=filled, fillcolor=lightblue];\n";

    exportarDOTRec(raiz, out);

    out << "}\n";
    out.close();
}

void ArbolAVL::exportarDOTRec(NodoAVL* nodo, ofstream& out) {
    if (!nodo) return;

    out << "\"" << nodo->data.titulo << "\";\n";

    if (nodo->izq) {
        out << "\"" << nodo->data.titulo << "\" -> \"" << nodo->izq->data.titulo << "\";\n";
        exportarDOTRec(nodo->izq, out);
    }
    if (nodo->der) {
        out << "\"" << nodo->data.titulo << "\" -> \"" << nodo->der->data.titulo << "\";\n";
        exportarDOTRec(nodo->der, out);
    }
}
