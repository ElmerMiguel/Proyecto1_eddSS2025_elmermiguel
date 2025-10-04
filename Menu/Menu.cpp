#include "Menu.h"
#include <iostream>
#include <limits>
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

    cout << "Ingrese titulo: ";
    getline(cin, titulo);
    cout << "Ingrese ISBN: ";
    getline(cin, isbn);
    cout << "Ingrese genero: ";
    getline(cin, genero);
    cout << "Ingrese anio: ";
    cin >> anio;
    cin.ignore();
    cout << "Ingrese autor: ";
    getline(cin, autor);

    bm.agregarLibro(Libro(titulo, isbn, genero, anio, autor));
    
}

void Menu::opcionEliminar() {
    mostrarSeparador();
    cout << "         ELIMINAR LIBRO" << endl;
    mostrarSeparador();

    string isbn;
    cout << "Ingrese ISBN del libro a eliminar: ";
    getline(cin, isbn);
    bm.eliminarLibro(isbn);
    
}

void Menu::opcionBuscarTitulo() {
    mostrarSeparador();
    cout << "         BUSCAR POR TITULO" << endl;
    mostrarSeparador();

    string titulo;
    cout << "Ingrese titulo a buscar: ";
    getline(cin, titulo);
    Libro* l = bm.buscarPorTitulo(titulo);
    if (l) {
        cout << "\nLibro encontrado:" << endl;
        cout << "Titulo: " << l->titulo << endl;
        cout << "Autor: " << l->autor << endl;
        cout << "ISBN: " << l->isbn << endl;
        cout << "Genero: " << l->genero << endl;
        cout << "Anio: " << l->anio << endl;
    } else {
        cout << "\nNo se encontro el libro." << endl;
    }
}

void Menu::opcionBuscarISBN() {
    mostrarSeparador();
    cout << "         BUSCAR POR ISBN" << endl;
    mostrarSeparador();

    string isbn;
    cout << "Ingrese ISBN a buscar: ";
    getline(cin, isbn);
    Libro* l = bm.buscarPorISBN(isbn);
    if (l) {
        cout << "\nLibro encontrado:" << endl;
        cout << "Titulo: " << l->titulo << endl;
        cout << "Autor: " << l->autor << endl;
        cout << "ISBN: " << l->isbn << endl;
        cout << "Genero: " << l->genero << endl;
        cout << "Anio: " << l->anio << endl;
    } else {
        cout << "\nNo se encontro el libro." << endl;
    }
}

void Menu::opcionBuscarFecha() {
    mostrarSeparador();
    cout << "         BUSCAR POR ANIO" << endl;
    mostrarSeparador();

    int anio;
    cout << "Ingrese anio a buscar: ";
    cin >> anio;
    cin.ignore();
    Libro* l = bm.buscarPorFecha(anio);
    if (l) {
        cout << "\nLibro encontrado:" << endl;
        cout << "Titulo: " << l->titulo << endl;
        cout << "Autor: " << l->autor << endl;
        cout << "ISBN: " << l->isbn << endl;
        cout << "Genero: " << l->genero << endl;
        cout << "Anio: " << l->anio << endl;
    } else {
        cout << "\nNo se encontro ningun libro de ese anio." << endl;
    }
}

void Menu::opcionMostrarPorTitulo() {
    mostrarSeparador();
    cout << "      LIBROS ORDENADOS POR TITULO" << endl;
    mostrarSeparador();
    bm.mostrarPorTitulo();
}

void Menu::opcionBuscarGenero() {
    mostrarSeparador();
    cout << "         BUSCAR POR GENERO" << endl;
    mostrarSeparador();

    string genero;
    cout << "Ingrese genero a buscar: ";
    getline(cin, genero);

    vector<Libro> libros = bm.buscarPorGenero(genero);
    if (libros.empty()) {
        cout << "\nNo se encontraron libros del genero " << genero << "." << endl;
    } else {
        cout << "\nLibros encontrados en el genero " << genero << ":" << endl;
        mostrarSeparador();
        for (const auto& l : libros) {
            cout << "Titulo: " << l.titulo << endl;
            cout << "Autor: " << l.autor << endl;
            cout << "Anio: " << l.anio << endl;
            cout << "ISBN: " << l.isbn << endl;
            cout << "---" << endl;
        }
    }
}

void Menu::opcionCargarCSV() {
    mostrarSeparador();
    cout << "       CARGAR DESDE ARCHIVO CSV" << endl;
    mostrarSeparador();

    string ruta;
    cout << "Ingrese ruta del archivo CSV: ";
    getline(cin, ruta);

    bm.cargarDesdeCSV(ruta);
}

void Menu::opcionBuscarRangoFechas() {
    mostrarSeparador();
    cout << "       BUSCAR POR RANGO DE FECHAS" << endl;
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

    string titulo, isbn;
    cout << "Ingrese titulo a medir: ";
    getline(cin, titulo);
    cout << "Ingrese ISBN a medir: ";
    getline(cin, isbn);

    cout << "\nMidiendo rendimiento..." << endl;

    long long tSec = bm.medirBusquedaTituloSecuencial(titulo);
    long long tAVL = bm.medirBusquedaTituloAVL(titulo);
    long long iSec = bm.medirBusquedaISBNSecuencial(isbn);
    long long iBST = bm.medirBusquedaISBNBST(isbn);

    mostrarSeparador();
    cout << "       RESULTADOS DE RENDIMIENTO" << endl;
    mostrarSeparador();
    cout << "Busqueda por titulo:" << endl;
    cout << "  Secuencial:  " << tSec << " microsegundos" << endl;
    cout << "  AVL:         " << tAVL << " microsegundos" << endl;
    cout << "\nBusqueda por ISBN:" << endl;
    cout << "  Secuencial:  " << iSec << " microsegundos" << endl;
    cout << "  BST:         " << iBST << " microsegundos" << endl;
}

void Menu::opcionExportarArboles() {
    mostrarSeparador();
    cout << "       EXPORTAR GRAFICOS DE ARBOLES" << endl;
    mostrarSeparador();

    cout << "Exportando arboles a archivos DOT..." << endl;
    bm.exportarAVL("avl.dot");
    bm.exportarB("b.dot");
    bm.exportarBPlus("bplus.dot");
    bm.exportarBST("bst.dot");
    cout << "\nArchivos generados:" << endl;
    cout << "- avl.dot (Arbol AVL de titulos)" << endl;
    cout << "- b.dot (Arbol B de fechas)" << endl;
    cout << "- bplus.dot (Arbol B+ de generos)" << endl;
    cout << "- bst.dot (Arbol BST de ISBN)" << endl;
    cout << "\nPara generar imagenes, use:" << endl;
    cout << "dot -Tpng archivo.dot -o salida.png" << endl;
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