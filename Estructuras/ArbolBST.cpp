#include "ArbolBST.h"

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
    // Si ISBN es igual, no insertar duplicado
    
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
    
    // Usar solo parte del ISBN para el nodo visual
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