# 📚 Manual Técnico - Biblioteca Mágica

## 📋 Índice
1. [Introducción](#introducción)
2. [Arquitectura del Sistema](#arquitectura-del-sistema)
3. [Estructuras de Datos](#estructuras-de-datos)
4. [Diagramas de Clases](#diagramas-de-clases)
5. [Complejidad Algorítmica](#complejidad-algorítmica)
6. [TAD's (Tipos Abstractos de Datos)](#tads-tipos-abstractos-de-datos)
7. [Especificaciones Técnicas](#especificaciones-técnicas)

---

## 🔍 Introducción

El sistema "Biblioteca Mágica" es una aplicación desarrollada en C++ que implementa múltiples estructuras de datos para la gestión eficiente de libros. El sistema utiliza árboles binarios de búsqueda, árboles AVL, árboles B y B+ para optimizar las operaciones de inserción, búsqueda y eliminación.

### Objetivos del Sistema
- Gestión eficiente de una colección de libros
- Implementación de múltiples estructuras de datos
- Comparación de rendimiento entre estructuras
- Interfaz de usuario intuitiva

---

## 🏗️ Arquitectura del Sistema

### Diagrama de Arquitectura General

```dot
digraph Sistema {
    rankdir=TB;
    node [shape=box, style=filled, fillcolor=lightblue];
    
    subgraph cluster_presentacion {
        label="Capa de Presentación";
        style=filled;
        fillcolor=lightgray;
        Menu [label="Menu\n(Interfaz Usuario)"];
    }
    
    subgraph cluster_logica {
        label="Capa de Lógica de Negocio";
        style=filled;
        fillcolor=lightgreen;
        BibliotecaMagica [label="BibliotecaMagica\n(Controlador Principal)"];
        Libro [label="Libro\n(Modelo de Datos)"];
    }
    
    subgraph cluster_datos {
        label="Capa de Estructuras de Datos";
        style=filled;
        fillcolor=lightyellow;
        BST [label="Árbol BST"];
        AVL [label="Árbol AVL"];
        BTree [label="Árbol B"];
        BPlus [label="Árbol B+"];
        Lista [label="Lista Enlazada"];
    }
    
    Menu -> BibliotecaMagica;
    BibliotecaMagica -> Libro;
    BibliotecaMagica -> BST;
    BibliotecaMagica -> AVL;
    BibliotecaMagica -> BTree;
    BibliotecaMagica -> BPlus;
    BibliotecaMagica -> Lista;
}
```

---

## 🌳 Estructuras de Datos

### 1. Árbol Binario de Búsqueda (BST)

```dot
digraph BST_Structure {
    node [shape=circle, style=filled, fillcolor=lightcoral];
    
    50 -> 30;
    50 -> 70;
    30 -> 20;
    30 -> 40;
    70 -> 60;
    70 -> 80;
    
    label="Ejemplo: Árbol BST\nOrdenado por ISBN";
}
```

**Características:**
- **Inserción**: O(log n) promedio, O(n) peor caso
- **Búsqueda**: O(log n) promedio, O(n) peor caso
- **Eliminación**: O(log n) promedio, O(n) peor caso

### 2. Árbol AVL (Autobalanceado)

```dot
digraph AVL_Structure {
    node [shape=circle, style=filled, fillcolor=lightgreen];
    
    40 [label="40\nBF:0"];
    20 [label="20\nBF:0"];
    60 [label="60\nBF:1"];
    10 [label="10\nBF:0"];
    30 [label="30\nBF:0"];
    50 [label="50\nBF:0"];
    70 [label="70\nBF:0"];
    
    40 -> 20;
    40 -> 60;
    20 -> 10;
    20 -> 30;
    60 -> 50;
    60 -> 70;
    
    label="Ejemplo: Árbol AVL\nBalance Factor (BF) mantenido";
}
```

**Características:**
- **Inserción**: O(log n) garantizado
- **Búsqueda**: O(log n) garantizado
- **Eliminación**: O(log n) garantizado
- **Balance Factor**: |BF| ≤ 1 para todos los nodos

### 3. Árbol B

```dot
digraph BTree_Structure {
    node [shape=record, style=filled, fillcolor=lightyellow];
    
    root [label="{<f0>|30|<f1>|60|<f2>}"];
    left [label="{<f0>|10|<f1>|20|<f2>}"];
    middle [label="{<f0>|40|<f1>|50|<f2>}"];
    right [label="{<f0>|70|<f1>|80|<f2>}"];
    
    root:f0 -> left;
    root:f1 -> middle;
    root:f2 -> right;
    
    label="Ejemplo: Árbol B de orden 3\nPara almacenamiento en disco";
}
```

**Características:**
- **Orden**: m (número máximo de hijos)
- **Claves por nodo**: m-1 máximo
- **Altura**: O(log_m n)
- **Operaciones**: O(log n)

### 4. Árbol B+

```dot
digraph BPlus_Structure {
    node [shape=record, style=filled, fillcolor=lightsteelblue];
    
    root [label="{<f0>|30|<f1>|60|<f2>}"];
    left [label="{<f0>|10|<f1>|20|<f2>|30|<f3>}"];
    middle [label="{<f0>|30|<f1>|40|<f2>|50|<f3>|60|<f4>}"];
    right [label="{<f0>|60|<f1>|70|<f2>|80|<f3>|90|<f4>}"];
    
    root:f0 -> left;
    root:f1 -> middle;
    root:f2 -> right;
    
    left:f3 -> middle:f0 [style=dashed, color=red];
    middle:f4 -> right:f0 [style=dashed, color=red];
    
    label="Ejemplo: Árbol B+\nCon enlaces horizontales para búsquedas secuenciales";
}
```

---

## 📊 Diagramas de Clases

### Diagrama UML Principal

```dot
digraph UML_Classes {
    node [shape=record, style=filled];
    
    Menu [fillcolor=lightblue, label="{Menu|+ mostrarMenuPrincipal(): void\l+ mostrarSubMenu1(): void\l+ mostrarSubMenu2(): void\l+ mostrarSubMenu3(): void\l+ validarEntrada(): bool\l}"];
    
    BibliotecaMagica [fillcolor=lightgreen, label="{BibliotecaMagica|- bst: ArbolBST*\l- avl: ArbolAVL*\l- btree: ArbolB*\l- bplus: ArbolBPlus*\l- lista: ListaLibros*\l|+ agregarLibro(): void\l+ eliminarLibro(): void\l+ buscarLibro(): Libro*\l+ listarLibros(): void\l+ cargarCSV(): void\l+ generarReportes(): void\l}"];
    
    Libro [fillcolor=lightyellow, label="{Libro|- titulo: string\l- isbn: string\l- autor: string\l- genero: string\l- anio: int\l|+ getTitulo(): string\l+ getISBN(): string\l+ getAutor(): string\l+ getGenero(): string\l+ getAnio(): int\l+ validarISBN(): bool\l}"];
    
    ArbolBST [fillcolor=lightcoral, label="{ArbolBST|- raiz: NodoBST*\l|+ insertar(): void\l+ buscar(): NodoBST*\l+ eliminar(): void\l+ inorden(): void\l+ generarDOT(): void\l}"];
    
    ArbolAVL [fillcolor=lightpink, label="{ArbolAVL|- raiz: NodoAVL*\l|+ insertar(): void\l+ buscar(): NodoAVL*\l+ eliminar(): void\l+ rotacionDerecha(): void\l+ rotacionIzquierda(): void\l+ obtenerBalance(): int\l}"];
    
    Menu -> BibliotecaMagica [label="usa"];
    BibliotecaMagica -> Libro [label="gestiona"];
    BibliotecaMagica -> ArbolBST [label="utiliza"];
    BibliotecaMagica -> ArbolAVL [label="utiliza"];
}
```

---

## ⚡ Complejidad Algorítmica

### Tabla Comparativa de Complejidades

| Estructura | Inserción | Búsqueda | Eliminación | Espacio |
|------------|-----------|----------|-------------|---------|
| **BST** | O(log n) / O(n) | O(log n) / O(n) | O(log n) / O(n) | O(n) |
| **AVL** | O(log n) | O(log n) | O(log n) | O(n) |
| **Árbol B** | O(log n) | O(log n) | O(log n) | O(n) |
| **Árbol B+** | O(log n) | O(log n) | O(log n) | O(n) |
| **Lista** | O(1) | O(n) | O(n) | O(n) |

### Diagrama de Complejidad Temporal

```dot
digraph Complexity {
    rankdir=LR;
    node [shape=box, style=filled];
    
    subgraph cluster_best {
        label="Mejor Caso";
        fillcolor=lightgreen;
        BST_best [label="BST: O(log n)", fillcolor=lightcoral];
        AVL_best [label="AVL: O(log n)", fillcolor=lightgreen];
        B_best [label="B/B+: O(log n)", fillcolor=lightyellow];
    }
    
    subgraph cluster_worst {
        label="Peor Caso";
        fillcolor=lightcoral;
        BST_worst [label="BST: O(n)", fillcolor=red];
        AVL_worst [label="AVL: O(log n)", fillcolor=lightgreen];
        B_worst [label="B/B+: O(log n)", fillcolor=lightyellow];
    }
}
```

---

## 🔧 TAD's (Tipos Abstractos de Datos)

### TAD Libro

```
TAD Libro {
    Dominio:
        titulo: Cadena
        isbn: Cadena (formato específico)
        autor: Cadena
        genero: Cadena
        anio: Entero [1000..2025]
    
    Operaciones:
        crear(t: Cadena, i: Cadena, a: Cadena, g: Cadena, año: Entero): Libro
        obtenerTitulo(): Cadena
        obtenerISBN(): Cadena
        obtenerAutor(): Cadena
        obtenerGenero(): Cadena
        obtenerAnio(): Entero
        validarISBN(): Booleano
        compararPor(criterio: TipoCriterio, otro: Libro): Entero
    
    Restricciones:
        - ISBN debe tener formato válido
        - Año debe estar en rango válido
        - Campos no pueden estar vacíos
}
```

### TAD ArbolBST

```
TAD ArbolBST {
    Dominio:
        raiz: Puntero a NodoBST
    
    Operaciones:
        crear(): ArbolBST
        insertar(dato: Libro): Booleano
        buscar(clave: Cadena): Puntero a Libro
        eliminar(clave: Cadena): Booleano
        estaVacio(): Booleano
        recorrerInorden(): Lista de Libro
        obtenerAltura(): Entero
        generarDOT(): Cadena
    
    Axiomas:
        - Para todo nodo n: izquierdo(n) < n < derecho(n)
        - Árbol vacío tiene altura 0
        - Inserción mantiene propiedad BST
}
```

### TAD BibliotecaMagica

```
TAD BibliotecaMagica {
    Dominio:
        estructuras: Conjunto de EstructurasDatos
        
    Operaciones:
        crearBiblioteca(): BibliotecaMagica
        agregarLibro(libro: Libro, estructura: TipoEstructura): Booleano
        eliminarLibro(isbn: Cadena, estructura: TipoEstructura): Booleano
        buscarLibro(criterio: Criterio, valor: Cadena): Lista de Libro
        listarLibros(orden: TipoOrden): Lista de Libro
        cargarDesdeCSV(archivo: Cadena): Booleano
        medirRendimiento(operacion: TipoOperacion): TiempoEjecucion
        generarReportes(): Booleano
    
    Invariantes:
        - Todas las estructuras mantienen los mismos datos
        - ISBN es único en cada estructura
        - Operaciones mantienen consistencia entre estructuras
}
```

---

## 🔧 Especificaciones Técnicas

### Compilación
- **Lenguaje**: C++17
- **Compilador**: GCC 9.0+ / Clang 10.0+
- **Sistema de Build**: CMake 3.16+
- **Dependencias**: Graphviz (para generación de diagramas)

### Estructura de Archivos
```
Proyecto1_eddSS2025/
├── Objetos/
│   ├── Libro.h/.cpp
│   └── BibliotecaMagica.h/.cpp
├── Estructuras/
│   ├── ArbolBST.h/.cpp
│   ├── ArbolAVL.h/.cpp
│   ├── ArbolB.h/.cpp
│   ├── ArbolBPlus.h/.cpp
│   └── ListaLibros.h/.cpp
├── Menu/
│   └── Menu.h/.cpp
└── documentacion/
    └── ManualTecnico.md
```

### Patrones de Diseño Utilizados
1. **Singleton**: Para la gestión de la biblioteca
2. **Strategy**: Para diferentes algoritmos de búsqueda
3. **Template**: Para reutilización de código en estructuras
4. **Observer**: Para notificaciones de cambios

### Consideraciones de Rendimiento
- Uso de punteros inteligentes para gestión de memoria
- Implementación de pools de memoria para nodos
- Optimización de cache mediante localidad de referencia
- Medición de tiempos con alta precisión

---

## 📈 Análisis de Rendimiento

### Benchmarks Esperados (n = 10,000 libros)

| Operación | BST | AVL | Árbol B | Árbol B+ |
|-----------|-----|-----|---------|----------|
| Inserción | 15ms | 18ms | 12ms | 14ms |
| Búsqueda | 8ms | 6ms | 5ms | 4ms |
| Eliminación | 12ms | 10ms | 8ms | 9ms |

### Uso de Memoria Aproximado
- **Libro**: 200 bytes por instancia
- **Nodo BST/AVL**: 40 bytes + punteros
- **Nodo B/B+**: Variable según orden del árbol
- **Overhead del sistema**: ~10% adicional

---

*Manual Técnico v1.0 - Biblioteca Mágica*  
*Generado el 5 de octubre de 2025*