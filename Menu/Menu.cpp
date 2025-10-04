
#include "Menu.h"
#include <iostream>
using namespace std;

Menu::Menu() : bm() {}

void Menu::mostrarMenu() {
    cout << "\n=====  Biblioteca Magica =====" << endl;
    cout << "1. Agregar libro" << endl;
    cout << "2. Eliminar libro" << endl;
    cout << "3. Buscar por titulo" << endl;
    cout << "4. Buscar por ISBN" << endl;
    cout << "5. Buscar por anio" << endl;
    cout << "6. Mostrar libros ordenados por titulo" << endl;
    cout << "7. Buscar por genero" << endl;
    cout << "8. Cargar libros desde CSV" << endl;
    cout << "9. Buscar por Rango de Fechas" << endl;
    cout << "10. Medir rendimiento de busquedas" << endl;
    cout << "11. Exportar arboles a DOT (Graphviz)" << endl;
    cout << "0. Salir" << endl;
    cout << "Seleccione una opcion: ";
}

void Menu::opcionAgregar() {
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
    cout << "Libro agregado con exito.\n";
}

void Menu::opcionEliminar() {
    string isbn;
    cout << "Ingrese ISBN del libro a eliminar: ";
    getline(cin, isbn);
    bm.eliminarLibro(isbn);
    cout << "Libro eliminado (si existía).\n";
}

void Menu::opcionBuscarTitulo() {
    string titulo;
    cout << "Ingrese titulo a buscar: ";
    getline(cin, titulo);
    Libro* l = bm.buscarPorTitulo(titulo);
    if (l) cout << "Encontrado: " << l->titulo << " de " << l->autor << endl;
    else cout << "No se encontro el libro.\n";
}

void Menu::opcionBuscarISBN() {
    string isbn;
    cout << "Ingrese ISBN a buscar: ";
    getline(cin, isbn);
    Libro* l = bm.buscarPorISBN(isbn);
    if (l) cout << "Encontrado: " << l->titulo << " de " << l->autor << endl;
    else cout << "No se encontro el libro.\n";
}

void Menu::opcionBuscarFecha() {
    int anio;
    cout << "Ingrese anio a buscar: ";
    cin >> anio;
    cin.ignore();
    Libro* l = bm.buscarPorFecha(anio);
    if (l) cout << "Encontrado: " << l->titulo << " de " << l->autor << endl;
    else cout << "No se encontro el libro.\n";
}

void Menu::opcionMostrarPorTitulo() {
    cout << "\n Libros ordenados por titulo:\n";
    bm.mostrarPorTitulo();
}

void Menu::ejecutar() {
    int opcion;
    do {
        mostrarMenu();
        cin >> opcion;
        cin.ignore();

        switch (opcion) {
            case 1: opcionAgregar(); break;
            case 2: opcionEliminar(); break;
            case 3: opcionBuscarTitulo(); break;
            case 4: opcionBuscarISBN(); break;
            case 5: opcionBuscarFecha(); break;
            case 6: opcionMostrarPorTitulo(); break;
            case 7: opcionBuscarGenero(); break;
            case 8: opcionCargarCSV(); break;
            case 9: opcionBuscarRangoFechas(); break;
            case 10: opcionMedirRendimiento(); break;
            case 11: opcionExportarArboles(); break;
            case 0: cout << " Saliendo del sistema...\n"; break;
            default: cout << " Opcion inválida.\n";
        }
    } while (opcion != 0);
}

void Menu::opcionBuscarGenero() {
    string genero;
    cout << "Ingrese genero a buscar: ";
    getline(cin, genero);

    vector<Libro> libros = bm.buscarPorGenero(genero);
    if (libros.empty()) {
        cout << "No se encontraron libros del genero " << genero << ".\n";
    } else {
        cout << "Libros encontrados en el genero " << genero << ":\n";
        for (auto& l : libros) {
            cout << " - " << l.titulo << " de " << l.autor
                 << " (" << l.anio << ", ISBN: " << l.isbn << ")\n";
        }
    }
}

void Menu::opcionCargarCSV() {
    string ruta;
    cout << "Ingrese ruta del archivo CSV: ";
    getline(cin, ruta);

    bm.cargarDesdeCSV(ruta);
}

void Menu::opcionBuscarRangoFechas() {
    int inicio, fin;
    cout << "Ingrese anio inicial: ";
    cin >> inicio;
    cout << "Ingrese anio final: ";
    cin >> fin;
    cin.ignore();

    ListaLibros resultado = bm.buscarPorRangoFechas(inicio, fin);
    cout << "Libros publicados entre " << inicio << " y " << fin << ":\n";
    resultado.mostrarTodos();
}

void Menu::opcionMedirRendimiento() {
    string titulo, isbn;
    cout << "Ingrese titulo a medir: ";
    getline(cin, titulo);
    cout << "Ingrese ISBN a medir: ";
    getline(cin, isbn);

    long long tSec = bm.medirBusquedaTituloSecuencial(titulo);
    long long tAVL = bm.medirBusquedaTituloAVL(titulo);
    long long iSec = bm.medirBusquedaISBNSecuencial(isbn);
    long long iHash = bm.medirBusquedaISBNHash(isbn);

    cout << "\n=== Resultados de rendimiento ===\n";
    cout << "Busqueda por titulo (Secuencial): " << tSec << " us\n";
    cout << "Busqueda por titulo (AVL):        " << tAVL << " us\n";
    cout << "Busqueda por ISBN (Secuencial):   " << iSec << " us\n";
    cout << "Busqueda por ISBN (Hash):         " << iHash << " us\n";
}

void Menu::opcionExportarArboles() {
    cout << "Exportando arboles a archivos DOT...\n";
    bm.exportarAVL("avl.dot");
    bm.exportarB("b.dot");
    bm.exportarBPlus("bplus.dot");
    cout << "Listo. Use Graphviz: dot -Tpng archivo.dot -o salida.png\n";
}
