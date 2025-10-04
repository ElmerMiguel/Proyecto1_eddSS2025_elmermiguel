#include <iostream>

#include "Menu/Menu.h"

int main() {
    try {
        BibliotecaMagica bm; // dentro ya crea ArbolB(3)
        Menu menu;
        menu.ejecutar();
    } catch (const exception& e) {
        cerr << "Error al iniciar: " << e.what() << endl;
    }

    return 0;
}
