#include "BibliotecaMagica.h"
#include <fstream>
#include <sstream>
#include <iostream>
#include <chrono>
#include <filesystem>  
#include <vector>       
#include <cstdlib>

using namespace std::chrono;


BibliotecaMagica::BibliotecaMagica() : arbolFechas(3), arbolGeneros(2) {}

void BibliotecaMagica::agregarLibro(Libro libro) {
    if (tablaISBN.buscar(libro.isbn) != nullptr) {
        cout << "Error: Ya existe un libro con ISBN " << libro.isbn << endl;
        cout << "No se puede agregar libro duplicado." << endl;
        return;
    }
    
    listaSecuencial.insertar(libro);
    arbolTitulos.insertar(libro);
    arbolFechas.insertar(libro);
    tablaISBN.insertar(libro);
    arbolGeneros.insertar(libro);
    
    cout << "Libro agregado correctamente: " << libro.titulo << endl;
}

void BibliotecaMagica::eliminarLibro(string isbn) {
    Libro* libro = tablaISBN.buscar(isbn);
    if (!libro) {
        cout << "Libro con ISBN " << isbn << " no encontrado." << endl;
        return;
    }
    
    string titulo = libro->titulo;
    
    listaSecuencial.eliminar(isbn);
    arbolTitulos.eliminar(titulo);
    tablaISBN.eliminar(isbn);
    
    cout << "Libro eliminado correctamente: " << titulo << endl;
}


Libro* BibliotecaMagica::buscarPorTitulo(string titulo) {
    return arbolTitulos.buscar(titulo);
}

Libro* BibliotecaMagica::buscarPorISBN(string isbn) {
    return tablaISBN.buscar(isbn);
}

Libro* BibliotecaMagica::buscarPorFecha(int anio) {
    return arbolFechas.buscar(anio);
}

void BibliotecaMagica::mostrarPorTitulo() {
    arbolTitulos.mostrarInOrder();
}

vector<Libro> BibliotecaMagica::buscarPorGenero(string genero) {
    return arbolGeneros.buscar(genero);
}




void BibliotecaMagica::cargarDesdeCSV(const std::string& rutaArchivoParam = "") {
    namespace fs = std::filesystem;
    std::string rutaArchivo = rutaArchivoParam;

 // === NUEVO BLOQUE: manejo de carpeta ./csv ===
if (rutaArchivo.empty()) {
    std::string carpeta = "./csv";
    std::vector<std::string> archivosCSV;

    if (fs::exists(carpeta) && fs::is_directory(carpeta)) {
        for (const auto& entry : fs::directory_iterator(carpeta)) {
            if (entry.is_regular_file() && entry.path().extension() == ".csv") {
                archivosCSV.push_back(entry.path().filename().string()); 
            }
        }
    }

    if (!archivosCSV.empty()) {
        std::cout << "\n=== ARCHIVOS CSV DISPONIBLES EN ./CSV===" << std::endl;
        for (size_t i = 0; i < archivosCSV.size(); ++i) {
            std::cout << i + 1 << ". " << archivosCSV[i] << std::endl;
        }
        std::cout << "0. Ingresar ruta manual" << std::endl;
        std::cout << "Seleccione una opcion: ";

        int opcion;
        std::cin >> opcion;
        std::cin.ignore(); 

        if (opcion == 0) {
            std::cout << "Ingrese la ruta del archivo CSV: ";
            std::getline(std::cin, rutaArchivo);
        } else if (opcion > 0 && opcion <= (int)archivosCSV.size()) {
            rutaArchivo = carpeta + "/" + archivosCSV[opcion - 1];
        } else {
            std::cerr << "Opcion invalida. Cancelando importacion." << std::endl;
            return;
        }
    } else {
        std::cout << "No se encontraron archivos CSV en ./csv.\n";
        std::cout << "Ingrese la ruta manual del archivo CSV: ";
        std::getline(std::cin, rutaArchivo);
    }
}


    std::ifstream archivo(rutaArchivo);
    if (!archivo.is_open()) {
        std::cerr << "Error: no se pudo abrir el archivo " << rutaArchivo << std::endl;
        return;
    }

    std::string linea;
    int librosImportados = 0;
    int librosIgnorados = 0;

    if (!getline(archivo, linea)) {
        std::cerr << "Archivo vacio o sin cabecera." << std::endl;
        return;
    }

    while (getline(archivo, linea)) {
        if (linea.empty()) continue;

        std::stringstream ss(linea);
        std::string titulo, isbn, genero, anioStr, autor;

        if (!getline(ss, titulo, ',')) continue;
        if (!getline(ss, isbn, ',')) continue;
        if (!getline(ss, genero, ',')) continue;
        if (!getline(ss, anioStr, ',')) continue;
        if (!getline(ss, autor, ',')) continue;

        auto clean = [](std::string& s) {
            if (!s.empty() && s.front() == '"') s.erase(0, 1);
            if (!s.empty() && s.back() == '"') s.pop_back();
        };
        clean(titulo);
        clean(isbn);
        clean(genero);
        clean(anioStr);
        clean(autor);

        int anio;
        try {
            anio = std::stoi(anioStr);
        } catch (...) {
            std::cerr << "(X) Linea ignorada - anio invalido: " << titulo << std::endl;
            librosIgnorados++;
            continue;
        }

        if (tablaISBN.buscar(isbn) != nullptr) {
            std::cerr << "(X) ISBN duplicado ignorado: " << isbn << " - " << titulo << std::endl;
            librosIgnorados++;
            continue;
        }

        Libro libro(titulo, isbn, genero, anio, autor);
        agregarLibro(libro);
        std::cout << "(√) Importado: " << titulo << std::endl;
        librosImportados++;
    }

    archivo.close();
    std::cout << "\n=== RESUMEN IMPORTACION ===" << std::endl;
    std::cout << "Libros importados correctamente: " << librosImportados << std::endl;
    std::cout << "Libros ignorados por duplicados/errores: " << librosIgnorados << std::endl;
    std::cout << "Carga desde CSV completada." << std::endl;
}





ListaLibros BibliotecaMagica::buscarPorRangoFechas(int inicio, int fin) {
    return arbolFechas.buscarPorRangoFechas(inicio, fin);
}

//Medicion
long long BibliotecaMagica::medirBusquedaTituloSecuencial(const string& titulo) {
    auto start = high_resolution_clock::now();
    listaSecuencial.buscarPorTitulo(titulo);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

long long BibliotecaMagica::medirBusquedaTituloAVL(const string& titulo) {
    auto start = high_resolution_clock::now();
    arbolTitulos.buscar(titulo);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

long long BibliotecaMagica::medirBusquedaISBNBST(const string& isbn) {
    auto start = high_resolution_clock::now();
    tablaISBN.buscar(isbn);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

long long BibliotecaMagica::medirBusquedaISBNSecuencial(const string& isbn) {
    auto start = high_resolution_clock::now();
    listaSecuencial.buscarPorISBN(isbn);
    auto end = high_resolution_clock::now();
    return duration_cast<microseconds>(end - start).count();
}

void BibliotecaMagica::exportarAVL(const string& archivo) {
    arbolTitulos.exportarDOT(archivo);
    generarPNGdesdeDOT(archivo.substr(0, archivo.find(".dot")));
}

void BibliotecaMagica::exportarB(const string& archivo) {
    arbolFechas.exportarDOT(archivo);
    generarPNGdesdeDOT(archivo.substr(0, archivo.find(".dot")));
}

void BibliotecaMagica::exportarBPlus(const string& archivo) {
    arbolGeneros.exportarDOT(archivo);
    generarPNGdesdeDOT(archivo.substr(0, archivo.find(".dot")));
}

void BibliotecaMagica::exportarBST(const string& archivo) {
    tablaISBN.exportarDOT(archivo);
    generarPNGdesdeDOT(archivo.substr(0, archivo.find(".dot")));
}



void BibliotecaMagica::generarPNGdesdeDOT(const string& archivoBase) {
    string comandoDOT = "dot -Tpng " + archivoBase + ".dot -o " + archivoBase + ".png 2>/dev/null";
    int resultado = system(comandoDOT.c_str());
    
    string archivoPNG = archivoBase + ".png";
    ifstream verificar(archivoPNG);
    
    if (verificar.good()) {
        verificar.close();
        cout << "(√) PNG generado: " << archivoPNG << endl;
    } else {
        cout << "(X) Error generando PNG para: " << archivoBase << endl;
    }
}

void BibliotecaMagica::exportarTodosLosDOTs() {
    system("mkdir -p graficos_arboles");
    
    cout << "Exportando todos los arboles a DOT y PNG..." << endl;
    cout << "=============================================" << endl;
    
    exportarAVL("graficos_arboles/arbol_avl_titulos.dot");
    exportarB("graficos_arboles/arbol_b_fechas.dot");
    exportarBST("graficos_arboles/arbol_bst_isbn.dot");
    exportarBPlus("graficos_arboles/arbol_bplus_generos.dot");
    
    cout << "=============================================" << endl;
    cout << "Archivos generados en carpeta 'graficos_arboles/'" << endl;
}
