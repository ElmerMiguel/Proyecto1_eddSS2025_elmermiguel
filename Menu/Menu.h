#ifndef MENU_H
#define MENU_H

#pragma once
#include "../Objetos/BibliotecaMagica.h"

class Menu {
private:
    BibliotecaMagica bm;

    // Metodos de navegacion
    void mostrarMenuPrincipal();
    void submenuGestionLibros();
    void submenuBusquedas();
    void submenuComparaciones();
    void submenuArchivos();

    void opcionAgregar();
    void opcionEliminar();
    void opcionBuscarTitulo();
    void opcionBuscarISBN();
    void opcionBuscarFecha();
    void opcionMostrarPorTitulo();
    void opcionBuscarGenero();
    void opcionCargarCSV();
    void opcionBuscarRangoFechas();
    void opcionMedirRendimiento();
    void opcionExportarArboles();

    // Utilidades
    int leerEntero(const string& mensaje);
    void mostrarSeparador();
    void pausar();

public:
    Menu();
    void ejecutar();
};

#endif