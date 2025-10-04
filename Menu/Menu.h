
#ifndef MENU_H
#define MENU_H

#pragma once
#include "../Objetos/BibliotecaMagica.h"

class Menu {
private:
    BibliotecaMagica bm;
    void mostrarMenu();
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
public:
    Menu();
    void ejecutar();
};


#endif
