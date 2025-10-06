#include "ArbolAVL.h"
#include <fstream>
#include <iomanip>    
#include <algorithm>  


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
        return nodo; 

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





NodoAVL* ArbolAVL::encontrarMin(NodoAVL* nodo) {
    while (nodo && nodo->izq) {
        nodo = nodo->izq;
    }
    return nodo;
}

NodoAVL* ArbolAVL::eliminar(NodoAVL* nodo, string titulo) {
    if (!nodo) return nodo;

    if (titulo < nodo->data.titulo) {
        nodo->izq = eliminar(nodo->izq, titulo);
    } else if (titulo > nodo->data.titulo) {
        nodo->der = eliminar(nodo->der, titulo);
    } else {
        // Nodo encontrado - eliminar
        if (!nodo->izq || !nodo->der) {
            NodoAVL* temp = nodo->izq ? nodo->izq : nodo->der;
            if (!temp) {
                temp = nodo;
                nodo = nullptr;
            } else {
                *nodo = *temp;
            }
            delete temp;
        } else {
            // Nodo con dos hijos - encontrar sucesor inorder
            NodoAVL* temp = encontrarMin(nodo->der);
            nodo->data = temp->data;
            nodo->der = eliminar(nodo->der, temp->data.titulo);
        }
    }

    if (!nodo) return nodo;

    // Actualizar altura
    nodo->altura = 1 + max(altura(nodo->izq), altura(nodo->der));

    // Verificar balance y rotar si es necesario
    int balanceFactor = balance(nodo);

    // Rotacion izquierda-izquierda
    if (balanceFactor > 1 && balance(nodo->izq) >= 0)
        return rotacionDerecha(nodo);

    // Rotacion derecha-derecha
    if (balanceFactor < -1 && balance(nodo->der) <= 0)
        return rotacionIzquierda(nodo);

    // Rotacion izquierda-derecha
    if (balanceFactor > 1 && balance(nodo->izq) < 0) {
        nodo->izq = rotacionIzquierda(nodo->izq);
        return rotacionDerecha(nodo);
    }

    // Rotacion derecha-izquierda
    if (balanceFactor < -1 && balance(nodo->der) > 0) {
        nodo->der = rotacionDerecha(nodo->der);
        return rotacionIzquierda(nodo);
    }

    return nodo;
}

bool ArbolAVL::eliminar(string titulo) {
    NodoAVL* original = raiz;
    raiz = eliminar(raiz, titulo);
    return raiz != original || buscar(titulo) == nullptr;
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
    out << "rankdir=TB;\n";  
    out << "ordering=out;\n"; 

    if (!raiz) {
        out << "empty [label=\"Arbol Vacio\"];\n";
    } else {
        exportarDOTRec(raiz, out);
    }

    out << "}\n";
    out.close();
    cout << "Archivo DOT generado: " << archivo << endl;
}



void ArbolAVL::exportarDOTRec(NodoAVL* nodo, ofstream& out) {
    if (!nodo) return;

    if (nodo->izq) {
        out << "\"" << nodo->data.titulo << "\" -> \"" << nodo->izq->data.titulo << "\" [label=\"L\"];\n";
        exportarDOTRec(nodo->izq, out);
    }
    if (nodo->der) {
        out << "\"" << nodo->data.titulo << "\" -> \"" << nodo->der->data.titulo << "\" [label=\"R\"];\n";
        exportarDOTRec(nodo->der, out);
    }
}




void ArbolAVL::listarTitulos() {
    cout << "Titulos disponibles:" << endl;
    cout << "===================" << endl;
    
    vector<Libro> todosLosLibros;
    recopilarLibros(raiz, todosLosLibros);
    
    if (todosLosLibros.empty()) {
        cout << "No hay titulos disponibles." << endl;
        return;
    }
    
    int maxTitulo = 6; 
    int maxAutor = 5;  
    int maxAnio = 3;   
    int maxISBN = 4;   
    
    for (const auto& libro : todosLosLibros) {
        maxTitulo = max(maxTitulo, (int)libro.titulo.length());
        maxAutor = max(maxAutor, (int)libro.autor.length());
        maxAnio = max(maxAnio, (int)to_string(libro.anio).length());
        maxISBN = max(maxISBN, (int)libro.isbn.length());
    }
    
    cout << "\nTotal de titulos: " << todosLosLibros.size() << endl;
    cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;
    
    cout << left << setw(maxTitulo + 2) << "TITULO"
         << left << setw(maxAutor + 2) << "AUTOR"
         << left << setw(maxAnio + 4) << "AÑO"
         << left << setw(maxISBN + 2) << "ISBN" << endl;
    
    cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;
    
    for (const auto& libro : todosLosLibros) {
        cout << left << setw(maxTitulo + 2) << libro.titulo
             << left << setw(maxAutor + 2) << libro.autor
             << left << setw(maxAnio + 4) << libro.anio
             << left << setw(maxISBN + 2) << libro.isbn
             << endl;
    }
    
    cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;
}

void ArbolAVL::recopilarLibros(NodoAVL* nodo, vector<Libro>& libros) {
    if (!nodo) return;
    recopilarLibros(nodo->izq, libros);
    libros.push_back(nodo->data);
    recopilarLibros(nodo->der, libros);
}

