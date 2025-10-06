# 📚 Biblioteca Mágica - Sistema de Gestión de Libros

![C++](https://img.shields.io/badge/c++-%2300599C.svg?style=for-the-badge&logo=c%2B%2B&logoColor=white)
![CMake](https://img.shields.io/badge/CMake-%23008FBA.svg?style=for-the-badge&logo=cmake&logoColor=white)



## 📋 Descripción

**Biblioteca Mágica** es un sistema avanzado de gestión de libros desarrollado en C++ que implementa múltiples estructuras de datos para optimizar las operaciones de almacenamiento, búsqueda y manipulación de una colección de libros.

### ✨ Características Principales

- 🌳 **Múltiples Estructuras de Datos**: BST, AVL, Árbol B, Árbol B+, Lista Enlazada
- 🔍 **Búsquedas Avanzadas**: Por título, ISBN, autor, género, año y rangos
- 📊 **Análisis de Rendimiento**: Comparación de tiempos entre estructuras
- 📈 **Visualización**: Generación automática de diagramas DOT/Graphviz
- 📄 **Importación CSV**: Carga masiva de datos desde archivos
- ✅ **Validaciones**: ISBN, años y formato de datos
- 🖥️ **Interfaz Intuitiva**: Menús interactivos y fácil navegación

---

## 🚀 Inicio Rápido

### 📦 Prerrequisitos

#### 🐧 Linux

```bash
sudo apt update
sudo apt install build-essential cmake g++ graphviz
```

#### 🪟 Windows

- **MinGW-w64** o **Visual Studio Build Tools**
- **CMake 3.16+**
- **Graphviz** (opcional, para diagramas)

### ⚡ Compilación Rápida

```bash
# Clonar o descomprimir el proyecto
cd Proyecto1_eddSS2025

# Compilación simple
mkdir build && cd build
cmake ..
make

# Ejecutar
./Proyecto1_eddSS2025
```

---

## 🛠️ Compilación Avanzada

### 🎯 Compilación Estática (Recomendada)

#### 🐧 Linux Estático

1. **Crear toolchain**:
   
   ```bash
   mkdir -p cmake
   ```

Crear `cmake/toolchain-linux-static.cmake`:

```cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_C_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
```

2. **Compilar**:
   
   ```bash
   cmake -B build-linux -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
   cmake --build build-linux
   ```

3. **Verificar**:
   
   ```bash
   ldd build-linux/Proyecto1_eddSS2025
   # Debe mostrar: "not a dynamic executable"
   ```

#### 🪟 Windows Estático

1. **Crear toolchain**:

Crear `cmake/toolchain-windows-static.cmake`:

```cmake
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_C_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
```

2. **Compilar**:
   
   ```bash
   cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
   cmake --build build-windows
   ```

### 🔄 Compilación Cruzada (Linux → Windows)

```bash
# Instalar MinGW cross-compiler
sudo apt install mingw-w64

# Compilar para Windows desde Linux
cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
cmake --build build-windows
```

### 🚀 Scripts Automatizados

#### Script Todo-en-Uno (`build_all.sh`)

```bash
#!/bin/bash
set -e

echo "🧹 Limpiando builds anteriores..."
rm -rf build-linux build-windows

echo "🛠️ Compilando para Linux..."
cmake -B build-linux -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
cmake --build build-linux

echo "🛠️ Compilando para Windows..."
cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
cmake --build build-windows

echo "🎉 Compilación completa para ambos sistemas."
```

```bash
chmod +x build_all.sh
./build_all.sh
```

---

## 🎮 Uso del Sistema

### 🏠 Menú Principal

El sistema presenta un menú principal con las siguientes opciones:

1. **📚 Gestión de Libros**
   
   - Agregar nuevo libro
   - Eliminar libro existente
   - Listar todos los libros

2. **🔍 Búsquedas Avanzadas**
   
   - Búsqueda por título
   - Búsqueda por ISBN
   - Búsqueda por año
   - Búsqueda por género
   - Búsqueda por rango de años

3. **📊 Análisis y Reportes**
   
   - Medición de rendimiento
   - Generación de diagramas
   - Comparación de estructuras

4. **📁 Importación de Datos**
   
   - Carga desde archivos CSV
   - Validación automática de datos

5. **🚪 Salir del Sistema**

### 📝 Formato de Datos

#### Estructura de Libro

```cpp
struct Libro {
    string titulo;      // Título del libro
    string isbn;        // ISBN (formato: XXX-X-XX-XXXXXX-X)
    string autor;       // Nombre del autor
    string genero;      // Género literario
    int anio;          // Año de publicación (1000-2025)
};
```

#### Formato CSV

```csv
titulo,isbn,autor,genero,anio
"El Quijote","978-0-12-345678-9","Miguel de Cervantes","Novela",1605
"Cien Años de Soledad","978-0-98-765432-1","Gabriel García Márquez","Realismo Mágico",1967
```

---

## 📁 Estructura del Proyecto

```
Proyecto1_eddSS2025/
├── 📂 Objetos/                 # Clases principales
│   ├── Libro.h/.cpp           # Modelo de datos
│   └── BibliotecaMagica.h/.cpp # Controlador principal
├── 📂 Estructuras/             # Estructuras de datos
│   ├── ArbolBST.h/.cpp        # Árbol Binario de Búsqueda
│   ├── ArbolAVL.h/.cpp        # Árbol AVL autobalanceado
│   ├── ArbolB.h/.cpp          # Árbol B multicamino
│   ├── ArbolBPlus.h/.cpp      # Árbol B+ optimizado
│   └── ListaLibros.h/.cpp     # Lista enlazada
├── 📂 Menu/                   # Interfaz de usuario
│   └── Menu.h/.cpp           # Sistema de menús
├── 📂 cmake/                  # Configuraciones de compilación
├── 📂 documentacion/          # Documentación técnica
├── 📄 CMakeLists.txt         # Configuración CMake
├── 📄 Makefile              # Compilación tradicional
└── 📄 README.md             # Este archivo
```

---

## ⚙️ Configuración en CLion

### 🎯 Para Compilación Estática

1. **Abrir CLion** y cargar el proyecto
2. **File → Settings → Build, Execution, Deployment → CMake**
3. **En "CMake options"** agregar:
   
   ```
   -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
   ```
4. **Aplicar cambios** y esperar reconfiguración
5. **Build → Build Project** o `Ctrl + F9`

### 🔧 Configuraciones Múltiples

Puedes crear múltiples configuraciones en CLion:

- **Debug-Linux**: Compilación normal para desarrollo
- **Release-Linux-Static**: Compilación estática Linux
- **Release-Windows-Static**: Compilación cruzada Windows

---

## 🧪 Testing y Verificación

### ✅ Verificar Compilación Estática

**Linux:**

```bash
ldd build-linux/Proyecto1_eddSS2025
# Salida esperada: "not a dynamic executable"
```

**Windows:**

```bash
objdump -p build-windows/Proyecto1_eddSS2025.exe | findstr "DLL"
# Sin salida = ejecutable estático
```

### 🎯 Pruebas Funcionales

1. **Agregar libros** con diferentes formatos
2. **Validar ISBN** con formatos incorrectos
3. **Realizar búsquedas** en cada estructura
4. **Medir rendimiento** con datasets grandes
5. **Importar CSV** con datos de prueba

---

## 📊 Rendimiento Esperado

### 🚀 Complejidades Algorítmicas

| Estructura | Inserción | Búsqueda  | Eliminación |
| ---------- | --------- | --------- | ----------- |
| BST        | O(log n)* | O(log n)* | O(log n)*   |
| AVL        | O(log n)  | O(log n)  | O(log n)    |
| Árbol B    | O(log n)  | O(log n)  | O(log n)    |
| Árbol B+   | O(log n)  | O(log n)  | O(log n)    |
| Lista      | O(1)      | O(n)      | O(n)        |

*\* O(n) en el peor caso para BST no balanceado*

### 📈 Benchmarks (10,000 libros)

| Operación   | BST   | AVL   | B-Tree | B+ Tree |
| ----------- | ----- | ----- | ------ | ------- |
| Inserción   | ~15ms | ~18ms | ~12ms  | ~14ms   |
| Búsqueda    | ~8ms  | ~6ms  | ~5ms   | ~4ms    |
| Eliminación | ~12ms | ~10ms | ~8ms   | ~9ms    |

---

## 🐛 Solución de Problemas

### ❌ Errores Comunes

**Error de compilación static:**

```bash
# Asegurar flags estáticos en CMakeLists.txt
set_target_properties(Proyecto1_eddSS2025 PROPERTIES 
    LINK_FLAGS "-static -static-libgcc -static-libstdc++")
```

**Error MinGW no encontrado:**

```bash
# Instalar MinGW cross-compiler
sudo apt install mingw-w64
```

**Error CMake versión:**

```bash
# Verificar versión CMake
cmake --version
# Mínimo requerido: 3.16
```

### 🔧 Debugging

```bash
# Compilar con símbolos de debug
cmake -DCMAKE_BUILD_TYPE=Debug -B build-debug
cmake --build build-debug

# Ejecutar con GDB
gdb build-debug/Proyecto1_eddSS2025
```

---

## 📖 Documentación Adicional

- 📘 **[Manual Técnico](documentacion/ManualTecnico.md)** - Arquitectura y TADs
- 📗 **[Manual de Usuario](documentacion/ManualUsuario.md)** - Guía de uso
- 📙 **[Compilación Avanzada](Compilacion_cmake.md)** - Configuraciones detalladas

---

## 👥 Información del Proyecto

- **Materia**: Estructuras de Datos (EDD) SS2025
- **Proyecto**: Proyecto 1 - Biblioteca Mágica
- **Lenguaje**: C++17
- **Paradigma**: Programación Orientada a Objetos
- **Estructuras Implementadas**: BST, AVL, B-Tree, B+ Tree, Lista Enlazada

---

## 📄 Licencia

Este proyecto es desarrollado con fines académicos para el curso de Estructuras de Datos SS2025.

---

**¡Disfruta explorando la Biblioteca Mágica! 📚✨**