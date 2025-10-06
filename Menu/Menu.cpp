#include "Menu.h"
#include <iostream>
#include <limits>
#include <iomanip> 
#include <algorithm>
#include <map>
using namespace std;

Menu::Menu() : bm() {}

void Menu::ejecutar() {
    int opcion;
    do {
        mostrarMenuPrincipal();
        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                submenuGestionLibros();
                break;
            case 2:
                submenuBusquedas();
                break;
            case 3:
                submenuComparaciones();
                break;
            case 4:
                submenuArchivos();
                break;
            case 0:
                cout << "\nCerrando sistema de biblioteca..." << endl;
                break;
            default:
                cout << "Opcion no valida. Intente nuevamente." << endl;
        }
    } while (opcion != 0);
}

void Menu::mostrarMenuPrincipal() {
    mostrarSeparador();
    cout << "               BIBLIOTECA MAGICA" << endl;
    mostrarSeparador();
    cout << "1. Gestion de Libros" << endl;
    cout << "2. Busquedas Especializadas" << endl;
    cout << "3. Analisis de Rendimiento" << endl;
    cout << "4. Gestion de Archivos" << endl;
    cout << "0. Salir del Sistema" << endl;
    mostrarSeparador();
}

void Menu::submenuGestionLibros() {
    int opcion;
    do {
        mostrarSeparador();
        cout << "           GESTION DE LIBROS" << endl;
        mostrarSeparador();
        cout << "1. Agregar nuevo libro" << endl;
        cout << "2. Eliminar libro por ISBN" << endl;
        cout << "3. Mostrar libros ordenados por titulo" << endl;
        cout << "0. Volver al menu principal" << endl;
        mostrarSeparador();

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                opcionAgregar();
                break;
            case 2:
                opcionEliminar();
                break;
            case 3:
                opcionMostrarPorTitulo();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
        }

        if (opcion != 0) pausar();
    } while (opcion != 0);
}

void Menu::submenuBusquedas() {
    int opcion;
    do {
        mostrarSeparador();
        cout << "         BUSQUEDAS ESPECIALIZADAS" << endl;
        mostrarSeparador();
        cout << "1. Buscar por titulo (Arbol AVL)" << endl;
        cout << "2. Buscar por ISBN (Arbol BST)" << endl;
        cout << "3. Buscar por anio especifico (Arbol B)" << endl;
        cout << "4. Buscar por genero (Arbol B+)" << endl;
        cout << "5. Buscar por rango de fechas (Arbol B)" << endl;
        cout << "0. Volver al menu principal" << endl;
        mostrarSeparador();

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                opcionBuscarTitulo();
                break;
            case 2:
                opcionBuscarISBN();
                break;
            case 3:
                opcionBuscarFecha();
                break;
            case 4:
                opcionBuscarGenero();
                break;
            case 5:
                opcionBuscarRangoFechas();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
        }

        if (opcion != 0) pausar();
    } while (opcion != 0);
}

void Menu::submenuComparaciones() {
    int opcion;
    do {
        mostrarSeparador();
        cout << "        ANALISIS DE RENDIMIENTO" << endl;
        mostrarSeparador();
        cout << "1. Medir rendimiento de busquedas" << endl;
        cout << "2. Exportar graficos de arboles (DOT)" << endl;
        cout << "0. Volver al menu principal" << endl;
        mostrarSeparador();

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                opcionMedirRendimiento();
                break;
            case 2:
                opcionExportarArboles();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
        }

        if (opcion != 0) pausar();
    } while (opcion != 0);
}

void Menu::submenuArchivos() {
    int opcion;
    do {
        mostrarSeparador();
        cout << "          GESTION DE ARCHIVOS" << endl;
        mostrarSeparador();
        cout << "1. Cargar libros desde archivo CSV" << endl;
        cout << "0. Volver al menu principal" << endl;
        mostrarSeparador();

        opcion = leerEntero("Seleccione una opcion: ");

        switch (opcion) {
            case 1:
                opcionCargarCSV();
                break;
            case 0:
                break;
            default:
                cout << "Opcion no valida." << endl;
        }

        if (opcion != 0) pausar();
    } while (opcion != 0);
}

void Menu::opcionAgregar() {
    mostrarSeparador();
    cout << "         AGREGAR NUEVO LIBRO" << endl;
    mostrarSeparador();

    string titulo, isbn, genero, autor;
    int anio;

    cout << "Complete la informacion del nuevo libro:" << endl;
    cout << string(50, '-') << endl;
    cout << "Titulo: ";
    getline(cin, titulo);
    
    cout << "ISBN (formato: 978-XX-XXXX-XXX-X): ";
    getline(cin, isbn);
    
    cout << "Genero: ";
    getline(cin, genero);
    
    cout << "Año de publicacion (1000-2025): ";
    while (!(cin >> anio) || anio < 1000 || anio > 2025) {
        cout << "Error: Ingrese un año valido entre 1000 y 2025: ";
        cin.clear();
        cin.ignore(numeric_limits<streamsize>::max(), '\n');
    }
    cin.ignore();
    
    cout << "Autor: ";
    getline(cin, autor);

    cout << "\nProcesando nuevo libro..." << endl;
    bm.agregarLibro(Libro(titulo, isbn, genero, anio, autor));
}

void Menu::opcionEliminar() {
    mostrarSeparador();
    cout << "         ELIMINAR LIBRO" << endl;
    mostrarSeparador();

    cout << "Resumen de libros disponibles:" << endl;
    bm.mostrarResumenLibros();
    mostrarSeparador();

    string isbn;
    cout << "Ingrese ISBN del libro a eliminar: ";
    getline(cin, isbn);
    
    cout << "\nConfirmando eliminacion..." << endl;
    bm.eliminarLibro(isbn);
}
void Menu::opcionBuscarTitulo() {
    mostrarSeparador();
    cout << "         BUSCAR POR TITULO" << endl;
    mostrarSeparador();

    bm.mostrarTitulosDisponibles();
    mostrarSeparador();

    string titulo;
    cout << "Ingrese titulo a buscar: ";
    getline(cin, titulo);
    Libro* l = bm.buscarPorTitulo(titulo);
    if (l) {
        cout << "\nLibro encontrado:" << endl;
        cout << string(80, '=') << endl;
        cout << left << setw(12) << "TITULO:"    << l->titulo << endl;
        cout << left << setw(12) << "AUTOR:"     << l->autor << endl;
        cout << left << setw(12) << "GENERO:"    << l->genero << endl;
        cout << left << setw(12) << "AÑO:"       << l->anio << endl;
        cout << left << setw(12) << "ISBN:"      << l->isbn << endl;
        cout << string(80, '=') << endl;
    } else {
        cout << "\nNo se encontro el libro con titulo: '" << titulo << "'." << endl;
    }
}

void Menu::opcionBuscarISBN() {
    mostrarSeparador();
    cout << "         BUSCAR POR ISBN" << endl;
    mostrarSeparador();

    bm.mostrarISBNsDisponibles();
    mostrarSeparador();

    string isbn;
    cout << "Ingrese ISBN a buscar: ";
    getline(cin, isbn);
    Libro* l = bm.buscarPorISBN(isbn);
    if (l) {
        cout << "\nLibro encontrado:" << endl;
        cout << string(80, '=') << endl;
        cout << left << setw(12) << "TITULO:"    << l->titulo << endl;
        cout << left << setw(12) << "AUTOR:"     << l->autor << endl;
        cout << left << setw(12) << "GENERO:"    << l->genero << endl;
        cout << left << setw(12) << "AÑO:"       << l->anio << endl;
        cout << left << setw(12) << "ISBN:"      << l->isbn << endl;
        cout << string(80, '=') << endl;
    } else {
        cout << "\nNo se encontro el libro con ISBN: '" << isbn << "'." << endl;
    }
}
void Menu::opcionBuscarFecha() {
    mostrarSeparador();
    cout << "         BUSCAR POR ANIO" << endl;
    mostrarSeparador();

    bm.mostrarAniosDisponibles();
    mostrarSeparador();

    int anio;
    cout << "Ingrese anio a buscar: ";
    cin >> anio;
    cin.ignore();
    
    vector<Libro> libros = bm.buscarPorFecha(anio);
    
    if (libros.empty()) {
        cout << "\nNo se encontro ningun libro de " << anio << "." << endl;
    } else {
        int maxTitulo = 6; 
        int maxAutor = 5;  
        int maxGenero = 6; 
        int maxISBN = 4;   

        for (const auto& libro : libros) {
            maxTitulo = max(maxTitulo, (int)libro.titulo.length());
            maxAutor = max(maxAutor, (int)libro.autor.length());
            maxGenero = max(maxGenero, (int)libro.genero.length());
            maxISBN = max(maxISBN, (int)libro.isbn.length());
        }

        cout << "\nTotal de libros encontrados en " << anio << ": " << libros.size() << endl;
        cout << string(maxTitulo + maxAutor + maxGenero + maxISBN + 12, '=') << endl;

        cout << left << setw(maxTitulo + 2) << "TITULO"
             << left << setw(maxAutor + 2) << "AUTOR"
             << left << setw(maxGenero + 2) << "GENERO"
             << left << setw(maxISBN + 2) << "ISBN" << endl;

        cout << string(maxTitulo + maxAutor + maxGenero + maxISBN + 12, '=') << endl;

        for (const auto& l : libros) {
            cout << left << setw(maxTitulo + 2) << l.titulo
                 << left << setw(maxAutor + 2) << l.autor
                 << left << setw(maxGenero + 2) << l.genero
                 << left << setw(maxISBN + 2) << l.isbn
                 << endl;
        }

        cout << string(maxTitulo + maxAutor + maxGenero + maxISBN + 12, '=') << endl;
    }
}

void Menu::opcionMostrarPorTitulo() {
    mostrarSeparador();
    cout << "       MOSTRAR LIBROS ORDENADOS POR TITULO" << endl;
    mostrarSeparador();
    
    cout << "Libros ordenados alfabeticamente:" << endl;
    mostrarSeparador();
    bm.mostrarPorTitulo();
}

void Menu::opcionBuscarGenero() {
    mostrarSeparador();
    cout << "         BUSCAR POR GENERO" << endl;
    mostrarSeparador();

    bm.mostrarGenerosDisponibles();
    mostrarSeparador();

    string genero;
    cout << "Ingrese genero a buscar: ";
    getline(cin, genero);

    vector<Libro> libros = bm.buscarPorGenero(genero);
    if (libros.empty()) {
        cout << "\nNo se encontraron libros del genero " << genero << "." << endl;
    } else {
        int maxTitulo = 6; 
        int maxAutor = 5;  
        int maxAnio = 3;   
        int maxISBN = 4;   

        for (const auto& libro : libros) {
            maxTitulo = max(maxTitulo, (int)libro.titulo.length());
            maxAutor = max(maxAutor, (int)libro.autor.length());
            maxAnio = max(maxAnio, (int)to_string(libro.anio).length());
            maxISBN = max(maxISBN, (int)libro.isbn.length());
        }

        cout << "\nTotal de libros encontrados en '" << genero << "': " << libros.size() << endl;
        cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;

        cout << left << setw(maxTitulo + 2) << "TITULO"
             << left << setw(maxAutor + 2) << "AUTOR"
             << left << setw(maxAnio + 4) << "AÑO"
             << left << setw(maxISBN + 2) << "ISBN" << endl;

        cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;

        for (const auto& l : libros) {
            cout << left << setw(maxTitulo + 2) << l.titulo
                 << left << setw(maxAutor + 2) << l.autor
                 << left << setw(maxAnio + 4) << l.anio
                 << left << setw(maxISBN + 2) << l.isbn
                 << endl;
        }

        cout << string(maxTitulo + maxAutor + maxAnio + maxISBN + 12, '=') << endl;
    }
}

void Menu::opcionCargarCSV() {
    mostrarSeparador();
    cout << "       CARGAR DESDE ARCHIVO CSV" << endl;
    mostrarSeparador();

    bm.cargarDesdeCSV(""); 
}

void Menu::opcionBuscarRangoFechas() {
    mostrarSeparador();
    cout << "       BUSCAR POR RANGO DE FECHAS" << endl;
    mostrarSeparador();

    bm.mostrarAniosDisponibles();
    mostrarSeparador();

    int inicio, fin;
    cout << "Ingrese anio inicial: ";
    cin >> inicio;
    cout << "Ingrese anio final: ";
    cin >> fin;
    cin.ignore();

    ListaLibros resultado = bm.buscarPorRangoFechas(inicio, fin);
    cout << "\nLibros publicados entre " << inicio << " y " << fin << ":" << endl;
    mostrarSeparador();
    resultado.mostrarTodos();
}

void Menu::opcionMedirRendimiento() {
    mostrarSeparador();
    cout << "       MEDICION DE RENDIMIENTO" << endl;
    mostrarSeparador();

    cout << "Datos disponibles para pruebas:" << endl;
    cout << "===============================" << endl;
    bm.mostrarTitulosDisponibles();
    mostrarSeparador();
    bm.mostrarISBNsDisponibles();
    mostrarSeparador();

    string titulo, isbn;
    cout << "Ingrese titulo a medir: ";
    getline(cin, titulo);
    cout << "Ingrese ISBN a medir: ";
    getline(cin, isbn);

    Libro* libroTitulo = bm.buscarPorTitulo(titulo);
    Libro* libroISBN = bm.buscarPorISBN(isbn);
    
    if (!libroTitulo) {
        cout << "\nError: El titulo '" << titulo << "' no existe en el sistema." << endl;
        cout << "Por favor seleccione un titulo de la lista mostrada arriba." << endl;
        return; 
    }
    if (!libroISBN) {
        cout << "\nError: El ISBN '" << isbn << "' no existe en el sistema." << endl;
        cout << "Por favor seleccione un ISBN de la lista mostrada arriba." << endl;
        return;  
    }

    if (libroTitulo->isbn != isbn || libroISBN->titulo != titulo) {
        cout << "\nError: El titulo e ISBN no pertenecen al mismo libro." << endl;
        cout << "Titulo encontrado: " << libroTitulo->titulo << " (" << libroTitulo->isbn << ")" << endl;
        cout << "ISBN encontrado: " << libroISBN->titulo << " (" << libroISBN->isbn << ")" << endl;
        cout << "Por favor ingrese titulo e ISBN del MISMO libro." << endl;
        return; 
    }

    cout << "\nDatos validados correctamente:" << endl;
    cout << "Titulo: " << libroTitulo->titulo << " (" << libroTitulo->autor << ")" << endl;
    cout << "ISBN: " << libroISBN->isbn << " (" << libroISBN->titulo << ")" << endl;
    
    cout << "\nMidiendo rendimiento..." << endl;

    long long tSec = bm.medirBusquedaTituloSecuencial(titulo);
    long long tAVL = bm.medirBusquedaTituloAVL(titulo);
    long long iSec = bm.medirBusquedaISBNSecuencial(isbn);
    long long iBST = bm.medirBusquedaISBNBST(isbn);

    mostrarSeparador();
    cout << "       RESULTADOS DE RENDIMIENTO" << endl;
    mostrarSeparador();
    
    cout << "Tiempos de busqueda:" << endl;
    cout << "Busqueda por titulo '" << titulo << "':" << endl;
    cout << "  Secuencial:  " << tSec << " microsegundos" << endl;
    cout << "  AVL:         " << tAVL << " microsegundos" << endl;
    cout << "\nBusqueda por ISBN '" << isbn << "':" << endl;
    cout << "  Secuencial:  " << iSec << " microsegundos" << endl;
    cout << "  BST:         " << iBST << " microsegundos" << endl;
    
    cout << "\nAnalisis de eficiencia:" << endl;
    cout << "=======================" << endl;
    
    cout << "Busqueda por titulo:" << endl;
    if (tAVL < tSec) {
        cout << "  GANADOR: AVL (" << tAVL << " vs " << tSec << " microsegundos)" << endl;
        cout << "  Mejora: " << (tSec - tAVL) << " microsegundos mas rapido" << endl;
    } else if (tSec < tAVL) {
        cout << "  GANADOR: Secuencial (" << tSec << " vs " << tAVL << " microsegundos)" << endl;
        cout << "  Diferencia: " << (tAVL - tSec) << " microsegundos" << endl;
    } else {
        cout << "  EMPATE: Ambos metodos tardaron " << tSec << " microsegundos" << endl;
    }
    
    cout << "\nBusqueda por ISBN:" << endl;
    if (iBST < iSec) {
        cout << "  GANADOR: BST (" << iBST << " vs " << iSec << " microsegundos)" << endl; 
        cout << "  Mejora: " << (iSec - iBST) << " microsegundos mas rapido" << endl;
    } else if (iSec < iBST) {
        cout << "  GANADOR: Secuencial (" << iSec << " vs " << iBST << " microsegundos)" << endl;
        cout << "  Diferencia: " << (iBST - iSec) << " microsegundos" << endl;
    } else {
        cout << "  EMPATE: Ambos metodos tardaron " << iSec << " microsegundos" << endl;
    }

}
void Menu::opcionExportarArboles() {
    mostrarSeparador();
    cout << "       EXPORTAR GRAFICOS DE ARBOLES" << endl;
    mostrarSeparador();
    
    bm.exportarTodosLosDOTs();
    
    mostrarSeparador();
    cout << "√ Revisa la carpeta 'graficos_arboles/' para ver las imagenes PNG" << endl;
}

// Utilidades
int Menu::leerEntero(const string& mensaje) {
    int valor;
    while (true) {
        cout << mensaje;
        if (cin >> valor) {
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
            return valor;
        } else {
            cout << "Error: Ingrese un numero valido." << endl;
            cin.clear();
            cin.ignore(numeric_limits<streamsize>::max(), '\n');
        }
    }
}

void Menu::mostrarSeparador() {
    cout << string(50, '=') << endl;
}

void Menu::pausar() {
    cout << "\nPresione Enter para continuar...";
    cin.get();
}