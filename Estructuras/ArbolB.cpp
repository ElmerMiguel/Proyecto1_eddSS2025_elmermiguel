
#include "ArbolB.h"
#include <fstream>

NodoB::NodoB(int _t, bool _hoja) {
    if (_t < 2) throw invalid_argument("El grado minimo del Arbol B debe ser >= 2");
    t = _t;
    hoja = _hoja;
    claves = new int[2*t-1];
    valores = new Libro[2*t-1];
    hijos = new NodoB*[2*t];
    n = 0;
}

void NodoB::recorrer() {
    int i;
    for (i = 0; i < n; i++) {
        if(!hoja) hijos[i]->recorrer();
        cout << valores[i].titulo << " (" << claves[i] << ") " << endl;
    }
    if (!hoja) hijos[i]->recorrer();
}

NodoB* NodoB::buscar(int k) {
    int i = 0;
    while (i < n && k > claves[i]) i++;
    if (i < n && claves[i] == k) return this;
    if (hoja) return nullptr;
    return hijos[i]->buscar(k);
}

int NodoB::buscarIndice(int k) {
    int i = 0;
    while (i < n && k > claves[i]) i++;
    if (i < n && claves[i] == k) return i;
    return -1; 
}

ArbolB::ArbolB(int _t) {
    raiz = nullptr;
    t = _t;
}

void ArbolB::insertar(Libro libro) {
    if (raiz == nullptr) {
        raiz = new NodoB(t, true);
        raiz->claves[0] = libro.anio;
        raiz->valores[0] = libro;
        raiz->n = 1;
    } else {
        if (raiz->n == 2*t-1) {
            NodoB* s = new NodoB(t, false);
            s->hijos[0] = raiz;
            s->dividirHijo(0, raiz);
            int i = 0;
            if (s->claves[0] < libro.anio) i++;
            s->hijos[i]->insertarNoLleno(libro);
            raiz = s;
        } else {
            raiz->insertarNoLleno(libro);
        }
    }
}

void ArbolB::recorrer() {
    if(raiz != nullptr) raiz->recorrer();
}


Libro* ArbolB::buscar(int k) {
    if (raiz == nullptr) return nullptr;
    NodoB* nodo = raiz->buscar(k);
    if (!nodo) return nullptr;
    
    int indice = nodo->buscarIndice(k);
    return (indice >= 0) ? &nodo->valores[indice] : nullptr;
}

void NodoB::insertarNoLleno(Libro libro) {
    int i = n - 1;

    if (hoja) {
        // Mover claves mayores hacia adelante
        while (i >= 0 && claves[i] > libro.anio) {
            claves[i + 1] = claves[i];
            valores[i + 1] = valores[i];
            i--;
        }
        // Insertar nueva clave
        claves[i + 1] = libro.anio;
        valores[i + 1] = libro;
        n++;
    } else {
        // Encontrar el hijo adecuado
        while (i >= 0 && claves[i] > libro.anio) i--;

        if (hijos[i + 1]->n == 2 * t - 1) {
            dividirHijo(i + 1, hijos[i + 1]);

            if (claves[i + 1] < libro.anio) i++;
        }
        hijos[i + 1]->insertarNoLleno(libro);
    }
}

void NodoB::dividirHijo(int i, NodoB* y) {
    NodoB* z = new NodoB(y->t, y->hoja);
    z->n = t - 1;

    // Copiar últimas (t-1) claves de y en z
    for (int j = 0; j < t - 1; j++) {
        z->claves[j] = y->claves[j + t];
        z->valores[j] = y->valores[j + t];
    }

    // Copiar hijos si no es hoja
    if (!y->hoja) {
        for (int j = 0; j < t; j++) {
            z->hijos[j] = y->hijos[j + t];
        }
    }

    y->n = t - 1;

    // Mover hijos del nodo actual
    for (int j = n; j >= i + 1; j--) {
        hijos[j + 1] = hijos[j];
    }
    hijos[i + 1] = z;

    // Mover claves del nodo actual
    for (int j = n - 1; j >= i; j--) {
        claves[j + 1] = claves[j];
        valores[j + 1] = valores[j];
    }

    claves[i] = y->claves[t - 1];
    valores[i] = y->valores[t - 1];
    n++;
}

void NodoB::buscarRango(int inicio, int fin, ListaLibros& lista) {
    int i = 0;
    while (i < n && claves[i] < inicio) {
        if (!hoja && hijos[i]) hijos[i]->buscarRango(inicio, fin, lista);
        i++;
    }

    while (i < n && claves[i] <= fin) {
        if (!hoja && hijos[i]) hijos[i]->buscarRango(inicio, fin, lista);

        if (claves[i] >= inicio && claves[i] <= fin) {
            lista.insertar(valores[i]);
        }
        i++;
    }

    if (!hoja && i < 2*t && hijos[i]) hijos[i]->buscarRango(inicio, fin, lista);
}

ListaLibros ArbolB::buscarPorRangoFechas(int inicio, int fin) {
    ListaLibros lista;
    if (raiz != nullptr) {
        raiz->buscarRango(inicio, fin, lista);
    }
    return lista;
}

void ArbolB::exportarDOT(const string& archivo) {
    ofstream out(archivo);
    if (!out.is_open()) {
        cerr << "No se pudo abrir el archivo DOT." << endl;
        return;
    }

    out << "digraph BTree {\n";
    out << "node [shape=record, style=filled, fillcolor=lightyellow];\n";

    int id = 0;
    exportarDOTRec(raiz, out, id);

    out << "}\n";
    out.close();
}


void ArbolB::exportarDOTRec(NodoB* nodo, ofstream& out, int& id) {
    if (!nodo) return;
    int nodoId = id++;

    out << "n" << nodoId << " [label=\"";
    for (int i = 0; i < nodo->n; i++) {
        out << "<f" << i << "> |" << nodo->claves[i] << "| ";
    }
    out << "<f" << nodo->n << ">\"];\n";

    if (!nodo->hoja) {
        for (int i = 0; i <= nodo->n; i++) {
            if (nodo->hijos[i]) {
                int childId = id;
                exportarDOTRec(nodo->hijos[i], out, id);
                out << "\"n" << nodoId << "\":f" << i << " -> \"n" << childId << "\";\n";
            }
        }
    }
}



void ArbolB::listarAnios() {
    cout << "Años disponibles:" << endl;
    cout << "================" << endl;
    if (raiz) listarAniosRec(raiz);
    cout << endl;
}
void ArbolB::listarAniosRec(NodoB* nodo) {
    if (!nodo) return;
    
    for (int i = 0; i < nodo->n; i++) {
        if (!nodo->hoja) listarAniosRec(nodo->hijos[i]);  // CORREGIDO: llamar método de ArbolB
        cout << "- " << nodo->claves[i] << " (" << nodo->valores[i].titulo << ")" << endl;
    }
    if (!nodo->hoja) listarAniosRec(nodo->hijos[nodo->n]);  // CORREGIDO: llamar método de ArbolB
}