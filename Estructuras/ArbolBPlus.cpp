
#include "ArbolBPlus.h"
#include <fstream>

NodoBPlus::NodoBPlus(bool esHoja) {
    hoja = esHoja;
    siguiente = nullptr;
}

ArbolBPlus::ArbolBPlus(int _t) {
    t = (_t < 2) ? 2 : _t;
    raiz = new NodoBPlus(true);
}

void ArbolBPlus::insertar(const Libro& libro) {
    insertarInterno(raiz, libro, libro.genero);

    // Si la raíz se desborda, dividir
    if ((int)raiz->claves.size() >= 2 * t) {
        NodoBPlus* nuevaRaiz = new NodoBPlus(false);
        nuevaRaiz->hijos.push_back(raiz);
        dividirNodo(nuevaRaiz, 0, raiz);
        raiz = nuevaRaiz;
    }
}

void ArbolBPlus::insertarInterno(NodoBPlus* nodo, const Libro& libro, const string& genero) {
    if (nodo->hoja) {
        // Buscar si ya existe ese género
        for (size_t i = 0; i < nodo->claves.size(); i++) {
            if (nodo->claves[i] == genero) {
                nodo->valores[i].push_back(libro);
                return;
            }
        }
        // Insertar nuevo género
        nodo->claves.push_back(genero);
        nodo->valores.push_back({libro});

        // Ordenar claves (géneros en orden alfabético)
        for (size_t i = nodo->claves.size() - 1; i > 0; i--) {
            if (nodo->claves[i] < nodo->claves[i - 1]) {
                swap(nodo->claves[i], nodo->claves[i - 1]);
                swap(nodo->valores[i], nodo->valores[i - 1]);
            }
        }
    } else {
        // Nodo interno: buscar hijo correcto
        int i = 0;
        while (i < (int)nodo->claves.size() && genero > nodo->claves[i]) i++;
        insertarInterno(nodo->hijos[i], libro, genero);

        // Si hijo se desborda, dividir
        if ((int)nodo->hijos[i]->claves.size() >= 2 * t) {
            dividirNodo(nodo, i, nodo->hijos[i]);
        }
    }
}

void ArbolBPlus::dividirNodo(NodoBPlus* padre, int i, NodoBPlus* hijo) {
    NodoBPlus* nuevo = new NodoBPlus(hijo->hoja);
    int mitad = t;

    // Copiar claves a nuevo nodo
    nuevo->claves.assign(hijo->claves.begin() + mitad, hijo->claves.end());
    hijo->claves.erase(hijo->claves.begin() + mitad, hijo->claves.end());

    if (hijo->hoja) {
        nuevo->valores.assign(hijo->valores.begin() + mitad, hijo->valores.end());
        hijo->valores.erase(hijo->valores.begin() + mitad, hijo->valores.end());

        nuevo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevo;

        padre->claves.insert(padre->claves.begin() + i, nuevo->claves[0]);
        padre->hijos.insert(padre->hijos.begin() + i + 1, nuevo);
    } else {
        nuevo->hijos.assign(hijo->hijos.begin() + mitad + 1, hijo->hijos.end());
        hijo->hijos.erase(hijo->hijos.begin() + mitad + 1, hijo->hijos.end());

        padre->claves.insert(padre->claves.begin() + i, hijo->claves[mitad]);
        hijo->claves.erase(hijo->claves.begin() + mitad);

        padre->hijos.insert(padre->hijos.begin() + i + 1, nuevo);
    }
}

vector<Libro> ArbolBPlus::buscar(const string& genero) {
    vector<Libro> resultado;
    
    if (!raiz) return resultado;
    
    // Ir a la PRIMERA hoja (mas a la izquierda)
    NodoBPlus* actual = raiz;
    while (!actual->hoja) {
        actual = actual->hijos[0];  // Siempre ir al hijo mas a la izquierda
    }
    
    // Recorrer TODAS las hojas enlazadas secuencialmente
    while (actual) {
        for (size_t i = 0; i < actual->claves.size(); i++) {
            if (actual->claves[i] == genero) {
                // Agregar todos los libros de este genero
                for (const Libro& libro : actual->valores[i]) {
                    resultado.push_back(libro);
                }
            }
        }
        actual = actual->siguiente;
    }
    
    return resultado;
}


void ArbolBPlus::mostrarTodos() {
    NodoBPlus* actual = raiz;
    while (!actual->hoja) {
        actual = actual->hijos[0]; // ir al mas a la izquierda
    }
    while (actual) {
        for (size_t i = 0; i < actual->claves.size(); i++) {
            cout << "Genero: " << actual->claves[i] << endl;
            for (auto& l : actual->valores[i]) {
                cout << "   - " << l.titulo << " (" << l.autor << ")" << endl;
            }
        }
        actual = actual->siguiente;
    }
}

void ArbolBPlus::exportarDOT(const string& archivo) {
    ofstream out(archivo);
    if (!out.is_open()) {
        cerr << "No se pudo abrir el archivo DOT." << endl;
        return;
    }

    out << "digraph BPlusTree {\n";
    out << "node [shape=record, style=filled, fillcolor=lightgreen];\n";

    int id = 0;
    exportarDOTRec(raiz, out, id);

    out << "}\n";
    out.close();
}

void ArbolBPlus::exportarDOTRec(NodoBPlus* nodo, ofstream& out, int& id) {
    if (!nodo) return;
    int nodoId = id++;

    out << "n" << nodoId << " [label=\"";
    for (size_t i = 0; i < nodo->claves.size(); i++) {
        out << nodo->claves[i];
        if (i != nodo->claves.size() - 1) out << "|";
    }
    out << "\"];\n";

    if (!nodo->hoja) {
        for (size_t i = 0; i < nodo->hijos.size(); i++) {
            int childId = id;
            exportarDOTRec(nodo->hijos[i], out, id);
            out << "n" << nodoId << " -> n" << childId << ";\n";
        }
    }
}

