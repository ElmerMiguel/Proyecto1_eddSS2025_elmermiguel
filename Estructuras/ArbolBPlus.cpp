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
    if (!raiz) {
        raiz = new NodoBPlus(true);
    }

    // si la raiz se llena se divide
    if (raiz->claves.size() == 2 * t - 1) {
        NodoBPlus* nuevaRaiz = new NodoBPlus(false);
        nuevaRaiz->hijos.push_back(raiz);
        dividirNodo(nuevaRaiz, 0, raiz);
        raiz = nuevaRaiz;
    }

    insertarInterno(raiz, libro, libro.genero);
}

void ArbolBPlus::insertarInterno(NodoBPlus* nodo, const Libro& libro, const string& genero) {
    if (nodo->hoja) {
        // si el genero ya existe se agrega el libro
        for (size_t i = 0; i < nodo->claves.size(); i++) {
            if (nodo->claves[i] == genero) {
                nodo->valores[i].push_back(libro);
                return;
            }
        }

        // insertar nuevo genero y mantener orden
        nodo->claves.push_back(genero);
        nodo->valores.push_back({libro});
        for (size_t i = nodo->claves.size() - 1; i > 0; i--) {
            if (nodo->claves[i] < nodo->claves[i - 1]) {
                swap(nodo->claves[i], nodo->claves[i - 1]);
                swap(nodo->valores[i], nodo->valores[i - 1]);
            }
        }
    } else {
        int i = 0;
        while (i < (int)nodo->claves.size() && genero > nodo->claves[i]) i++;
        insertarInterno(nodo->hijos[i], libro, genero);

        // si el hijo se llena se divide
        if ((int)nodo->hijos[i]->claves.size() >= 2 * t) {
            dividirNodo(nodo, i, nodo->hijos[i]);
        }
    }
}

void ArbolBPlus::dividirNodo(NodoBPlus* padre, int i, NodoBPlus* hijo) {
    NodoBPlus* nuevo = new NodoBPlus(hijo->hoja);
    int mitad = t;

    if (hijo->hoja) {
        // dividir hoja
        nuevo->claves.assign(hijo->claves.begin() + mitad, hijo->claves.end());
        nuevo->valores.assign(hijo->valores.begin() + mitad, hijo->valores.end());
        hijo->claves.erase(hijo->claves.begin() + mitad, hijo->claves.end());
        hijo->valores.erase(hijo->valores.begin() + mitad, hijo->valores.end());

        nuevo->siguiente = hijo->siguiente;
        hijo->siguiente = nuevo;

        padre->claves.insert(padre->claves.begin() + i, nuevo->claves[0]);
        padre->hijos.insert(padre->hijos.begin() + i + 1, nuevo);
    } else {
        // dividir nodo interno
        nuevo->claves.assign(hijo->claves.begin() + mitad + 1, hijo->claves.end());
        nuevo->hijos.assign(hijo->hijos.begin() + mitad + 1, hijo->hijos.end());
        string clavePromocion = hijo->claves[mitad];

        hijo->claves.erase(hijo->claves.begin() + mitad, hijo->claves.end());
        hijo->hijos.erase(hijo->hijos.begin() + mitad + 1, hijo->hijos.end());

        padre->claves.insert(padre->claves.begin() + i, clavePromocion);
        padre->hijos.insert(padre->hijos.begin() + i + 1, nuevo);
    }
}

vector<Libro> ArbolBPlus::buscar(const string& genero) {
    vector<Libro> resultado;
    if (!raiz) return resultado;

    // ir a la hoja mas a la izquierda
    NodoBPlus* actual = raiz;
    while (!actual->hoja) {
        actual = actual->hijos[0];
    }

    // recorrer hojas enlazadas
    while (actual) {
        for (size_t i = 0; i < actual->claves.size(); i++) {
            if (actual->claves[i] == genero) {
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
    while (!actual->hoja) actual = actual->hijos[0];

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
        cerr << "Error al crear archivo " << archivo << endl;
        return;
    }

    out << "digraph BPlusTree {\n";
    out << "node [shape=record, style=filled, fillcolor=lightblue];\n";
    out << "rankdir=TB;\n";

    if (!raiz) {
        out << "vacio [label=\"Arbol vacio\"];\n";
    } else {
        int id = 0;
        exportarDOTRec(raiz, out, id);
        agregarEnlacesHojas(out);
    }

    out << "}\n";
    out.close();
    cout << "Archivo DOT generado: " << archivo << endl;
}

void ArbolBPlus::exportarDOTRec(NodoBPlus* nodo, ofstream& out, int& id) {
    if (!nodo) return;
    int nodoId = id++;

    out << "n" << nodoId << " [label=\"";
    if (nodo->hoja) {
        for (size_t i = 0; i < nodo->claves.size(); i++) {
            out << "<f" << i << "> " << nodo->claves[i]
                << "(" << nodo->valores[i].size() << ")";
            if (i != nodo->claves.size() - 1) out << "|";
        }
    } else {
        for (size_t i = 0; i < nodo->claves.size(); i++) {
            out << "<f" << i << "> |" << nodo->claves[i] << "| ";
        }
        out << "<f" << nodo->claves.size() << ">";
    }
    out << "\", fillcolor=" << (nodo->hoja ? "lightgreen" : "lightblue") << "];\n";

    if (!nodo->hoja) {
        for (size_t i = 0; i < nodo->hijos.size(); i++) {
            int childId = id;
            exportarDOTRec(nodo->hijos[i], out, id);
            out << "\"n" << nodoId << "\":f" << i << " -> \"n" << childId << "\";\n";
        }
    }
}

void ArbolBPlus::agregarEnlacesHojas(ofstream& out) {
    if (!raiz) return;

    vector<int> idHojas;
    int id = 0;
    recopilarIdsHojas(raiz, id, idHojas);

    for (size_t i = 0; i < idHojas.size() - 1; i++) {
        out << "n" << idHojas[i] << " -> n" << idHojas[i + 1]
            << " [style=dashed, color=red, constraint=false];\n";
    }
}

int ArbolBPlus::contarNodosInternos(NodoBPlus* nodo) {
    if (!nodo || nodo->hoja) return 0;

    int count = 1;
    for (NodoBPlus* hijo : nodo->hijos) count += contarNodosInternos(hijo);
    return count;
}

void ArbolBPlus::recopilarIdsHojas(NodoBPlus* nodo, int& id, vector<int>& idHojas) {
    if (!nodo) return;

    int nodoId = id++;
    if (nodo->hoja) {
        idHojas.push_back(nodoId);
    } else {
        for (NodoBPlus* hijo : nodo->hijos) {
            recopilarIdsHojas(hijo, id, idHojas);
        }
    }
}
