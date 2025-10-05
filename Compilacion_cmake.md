## 🧱 Paso a paso para compilar estáticamente en Linux desde CLion

### 🥇 Paso 1: Crear el archivo de toolchain

1. En la raíz del proyecto, crea una carpeta llamada `cmake`:

```bash
mkdir cmake
```

2. Dentro de esa carpeta, crea un archivo llamado `toolchain-linux-static.cmake`:

```bash
nano cmake/toolchain-linux-static.cmake
```

3. Agregar al archivo:

```cmake
set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_C_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
```

Guardar

---

### 🥈 Paso 2: Configurar CLion para usar ese toolchain

1. Abre CLion
2. Ve a **File > Settings > Build, Execution, Deployment > CMake**
3. En “CMake options”, agrega esta línea:

```
-DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
```

4. Aplica los cambios y espera a que CLion reconfigure el proyecto.

---

### 🥉 Paso 3: Compilar

Haz clic en el botón de “Build” en CLion o presiona `Ctrl + F9`.

---

### 🧪 Paso 4: Verificar que el ejecutable sea estático

Abre una terminal y ejecuta:

```bash
ldd cmake-build-debug/Proyecto1_eddSS2025
```

Si te dice:

```
not a dynamic executable
```

---

¡Perfecto, Adsf! Ahora te doy el equivalente para compilar **estáticamente en Windows usando CLion**, paso a paso y con la misma estructura que usaste para Linux. Esto funciona si tienes instalado **MinGW-w64** y lo configuraste como tu entorno de compilación en CLion.

---

----

---

## 🪟 Paso a paso para compilar estáticamente en Windows

### 🥇 Paso 1: Crear el archivo de toolchain

1. En la raíz del proyecto, crear la carpeta `cmake` si no existe:

```bash
mkdir cmake
```

2. Dentro de esa carpeta, crea el archivo `toolchain-windows-static.cmake`:

```bash
notepad cmake/toolchain-windows-static.cmake
```

3. Agrega esto al archivo:

```cmake
set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_C_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
```

💡 Si usas MinGW de 32 bits, cambia `x86_64-w64-mingw32-` por `i686-w64-mingw32-`.

---

### 🥈 Paso 2: Configurar CLion para usar ese toolchain

1. Abre CLion
2. Ve a **File > Settings > Build, Execution, Deployment > CMake**
3. En “CMake options”, agrega:

```
-DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
```

4. Aplica los cambios y espera a que CLion reconfigure el proyecto.

---

### 🥉 Paso 3: Compilar

Haz clic en el botón de “Build” o presiona `Ctrl + F9`.

---

### 🧪 Paso 4: Verificar que el ejecutable sea estático

1. Abre una terminal de MinGW o PowerShell
2. Ejecuta:

```bash
objdump -p cmake-build-debug/Proyecto1_eddSS2025.exe | findstr "DLL"
```

Si **no aparece ninguna DLL**, ¡tu ejecutable es completamente estático!

---

---

# Scripts para compilar

Usar Script siempre y cuando tengas instalado CMake y el compilador adecuado (GCC en Linux, MinGW en Windows). 

## 🧪 ¿Qué necesitas para compilar desde terminal?

### 🐧 En Linux

- Tener instalado: `cmake`, `gcc`, `g++`
- Tener tu `toolchain-linux-static.cmake`
- Script `build.sh` como este:

```bash
#!/bin/bash
set -e

echo "Compilando estáticamente en Linux..."

cmake -B build-linux -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
cmake --build build-linux

echo "Verificando binario..."
ldd build-linux/Proyecto1_eddSS2025 || echo "Binario estático generado correctamente."
```

Guárdalo como `build.sh`, dale permisos:

```bash
chmod +x build.sh
./build.sh
```

---

### 🪟 En Windows

- Tener instalado: MinGW-w64, CMake
- Tener tu `toolchain-windows-static.cmake`
- Script `build.bat` como este:

```bat
@echo off
echo Compilando estáticamente en Windows...

cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
cmake --build build-windows

echo Verificando binario...
objdump -p build-windows\Proyecto1_eddSS2025.exe | findstr DLL || echo Binario estático generado correctamente.
```

Guárdalo como `build.bat` y ejecútalo con doble clic o desde terminal.

---

## 🧠 Ventajas de usar scripts

- No dependes del IDE
- Puedes compilar en servidores, contenedores o CI/CD
- Puedes automatizar limpieza, empaquetado, pruebas, etc.

-----

# Script curzado lin y win

para compilar windows desde linux, tener instalado:
 `sudo apt install mingw-w64`

Crear en la raiz del proyecto:

### 🧩 `build_all.sh`

```bash
#!/bin/bash
set -e

echo "🧹 Limpiando builds anteriores..."
rm -rf build-linux build-windows

echo "🛠️ Compilando estáticamente para Linux..."
cmake -B build-linux -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
cmake --build build-linux

echo "🔍 Verificando binario Linux..."
ldd build-linux/Proyecto1_eddSS2025 || echo "✅ Binario estático Linux generado correctamente."

echo "🛠️ Compilando estáticamente para Windows (cross-compilation)..."
cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
cmake --build build-windows

echo "🔍 Verificando binario Windows..."
x86_64-w64-mingw32-objdump -p build-windows/Proyecto1_eddSS2025.exe | grep DLL || echo "✅ Binario estático Windows generado correctamente."

echo "🎉 Compilación completa para ambos sistemas."
```

*nota: agregar lo siguiente al fiinal de CMakeLists.txt:*

`set_target_properties(Proyecto1_eddSS2025 PROPERTIES LINK_FLAGS "-static -static-libgcc -static-libstdc++") `

---

solo buil win en linux, cruzado

```bash
#!/bin/bash
set -e

echo "Compilando estáticamente para Windows desde Linux..."

cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
cmake --build build-windows

echo "Verificando binario..."
x86_64-w64-mingw32-objdump -p build-windows/Proyecto1_eddSS2025.exe | grep DLL || echo "Binario estático generado correctamente."
```
