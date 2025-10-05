

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
