
#include "Libro.h"

Libro::Libro() {}

Libro::Libro(string t, string i, string g, int a, string au){
    titulo = t;
    isbn = i;
    genero = g;
    anio = a;
    autor = au;
}