#include "ArbolBST.h"
#include <iomanip>   
#include <algorithm>  
#include <vector>    
#include <string>     

ArbolBST::ArbolBST() : raiz(nullptr) {}

ArbolBST::~ArbolBST() {
    destruir(raiz);
}

void ArbolBST::destruir(NodoBST* nodo) {
    if (nodo) {
        destruir(nodo->izq);
        destruir(nodo->der);
        delete nodo;
    }
}

NodoBST* ArbolBST::insertar(NodoBST* nodo, Libro libro) {
    if (!nodo) {
        return new NodoBST(libro);
    }
    
    if (libro.isbn < nodo->data.isbn) {
        nodo->izq = insertar(nodo->izq, libro);
    } else if (libro.isbn > nodo->data.isbn) {
        nodo->der = insertar(nodo->der, libro);
    }
    
    return nodo;
}

void ArbolBST::insertar(Libro libro) {
    raiz = insertar(raiz, libro);
}

NodoBST* ArbolBST::buscar(NodoBST* nodo, string isbn) {
    if (!nodo || nodo->data.isbn == isbn) {
        return nodo;
    }
    
    if (isbn < nodo->data.isbn) {
        return buscar(nodo->izq, isbn);
    }
    return buscar(nodo->der, isbn);
}

Libro* ArbolBST::buscar(string isbn) {
    NodoBST* nodo = buscar(raiz, isbn);
    return nodo ? &nodo->data : nullptr;
}

NodoBST* ArbolBST::encontrarMin(NodoBST* nodo) {
    while (nodo && nodo->izq) {
        nodo = nodo->izq;
    }
    return nodo;
}

NodoBST* ArbolBST::eliminar(NodoBST* nodo, string isbn) {
    if (!nodo) return nodo;
    
    if (isbn < nodo->data.isbn) {
        nodo->izq = eliminar(nodo->izq, isbn);
    } else if (isbn > nodo->data.isbn) {
        nodo->der = eliminar(nodo->der, isbn);
    } else {
        // Nodo encontrado - eliminar
        if (!nodo->izq) {
            NodoBST* temp = nodo->der;
            delete nodo;
            return temp;
        } else if (!nodo->der) {
            NodoBST* temp = nodo->izq;
            delete nodo;
            return temp;
        }
        
        // Nodo con dos hijos - encontrar sucesor inorder
        NodoBST* temp = encontrarMin(nodo->der);
        nodo->data = temp->data;
        nodo->der = eliminar(nodo->der, temp->data.isbn);
    }
    return nodo;
}

bool ArbolBST::eliminar(string isbn) {
    NodoBST* original = raiz;
    raiz = eliminar(raiz, isbn);
    return raiz != original || buscar(isbn) == nullptr;
}

void ArbolBST::inOrder(NodoBST* nodo) {
    if (nodo) {
        inOrder(nodo->izq);
        cout << "ISBN: " << nodo->data.isbn << " - " << nodo->data.titulo << endl;
        inOrder(nodo->der);
    }
}

void ArbolBST::mostrarInOrder() {
    cout << "Libros ordenados por ISBN:" << endl;
    inOrder(raiz);
}

void ArbolBST::exportarDOT(const string& archivo) {
    ofstream out(archivo);
    if (!out.is_open()) return;
    
    out << "digraph BST {" << endl;
    out << "    node [shape=box, style=\"filled\", fillcolor=\"lightblue\"];" << endl;
    
    if (raiz) {
        exportarDOTRec(raiz, out);
    }
    
    out << "}" << endl;
    out.close();
}

void ArbolBST::exportarDOTRec(NodoBST* nodo, ofstream& out) {
    if (!nodo) return;
    
    string isbnCorto = nodo->data.isbn.length() > 10 ? 
                      nodo->data.isbn.substr(nodo->data.isbn.length()-4) : 
                      nodo->data.isbn;
    
    out << "    \"" << nodo->data.isbn << "\" [label=\"" << isbnCorto << "\"];" << endl;
    
    if (nodo->izq) {
        out << "    \"" << nodo->data.isbn << "\" -> \"" << nodo->izq->data.isbn << "\";" << endl;
        exportarDOTRec(nodo->izq, out);
    }
    
    if (nodo->der) {
        out << "    \"" << nodo->data.isbn << "\" -> \"" << nodo->der->data.isbn << "\";" << endl;
        exportarDOTRec(nodo->der, out);
    }
}


void ArbolBST::listarISBNs() {
    cout << "ISBNs disponibles:" << endl;
    cout << "=================" << endl;
    
    // Recopilar todos los libros
    vector<Libro> todosLosLibros;
    recopilarLibros(raiz, todosLosLibros);
    
    if (todosLosLibros.empty()) {
        cout << "No hay ISBNs disponibles." << endl;
        return;
    }
    
    // Calcular anchos máximos
    int maxISBN = 4;   // "ISBN"
    int maxTitulo = 6; // "TITULO"
    int maxAutor = 5;  // "AUTOR"
    int maxAnio = 3;   // "AÑO"
    
    for (const auto& libro : todosLosLibros) {
        maxISBN = max(maxISBN, (int)libro.isbn.length());
        maxTitulo = max(maxTitulo, (int)libro.titulo.length());
        maxAutor = max(maxAutor, (int)libro.autor.length());
        maxAnio = max(maxAnio, (int)to_string(libro.anio).length());
    }
    
    cout << "\nTotal de ISBNs: " << todosLosLibros.size() << endl;
    cout << string(maxISBN + maxTitulo + maxAutor + maxAnio + 12, '=') << endl;
    
    cout << left << setw(maxISBN + 2) << "ISBN"
         << left << setw(maxTitulo + 2) << "TITULO"
         << left << setw(maxAutor + 2) << "AUTOR"
         << left << setw(maxAnio + 4) << "AÑO" << endl;
    
    cout << string(maxISBN + maxTitulo + maxAutor + maxAnio + 12, '=') << endl;
    
    for (const auto& libro : todosLosLibros) {
        cout << left << setw(maxISBN + 2) << libro.isbn
             << left << setw(maxTitulo + 2) << libro.titulo
             << left << setw(maxAutor + 2) << libro.autor
             << left << setw(maxAnio + 4) << libro.anio
             << endl;
    }
    
    cout << string(maxISBN + maxTitulo + maxAutor + maxAnio + 12, '=') << endl;
}

void ArbolBST::recopilarLibros(NodoBST* nodo, vector<Libro>& libros) {
    if (!nodo) return;
    recopilarLibros(nodo->izq, libros);
    libros.push_back(nodo->data);
    recopilarLibros(nodo->der, libros);
}

