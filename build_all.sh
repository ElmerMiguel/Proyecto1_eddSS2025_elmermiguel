#!/bin/bash
set -e

echo "🧹 Limpiando builds anteriores y dist/..."
rm -rf build-linux build-windows dist
mkdir -p dist

echo "🛠️ Compilando estáticamente para Linux..."
cmake -B build-linux -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
cmake --build build-linux

echo "🔍 Detectando binario Linux..."
LINUX_BIN=$(find build-linux -maxdepth 1 -type f -executable | head -n 1)
if [[ -z "$LINUX_BIN" ]]; then
    echo "❌ No se encontró binario ejecutable en build-linux/"
    exit 1
fi

LINUX_NAME=$(basename "$LINUX_BIN")
echo "✅ Binario Linux detectado: $LINUX_NAME"

echo "🔍 Verificando binario Linux..."
ldd "$LINUX_BIN" || echo "✅ Binario estático Linux generado correctamente."

echo "📦 Copiando binario Linux a dist/..."
cp "$LINUX_BIN" "dist/${LINUX_NAME}-linux"

echo "🛠️ Verificando disponibilidad de mingw-w64..."
if command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1; then
    echo "✅ mingw-w64 encontrado. Compilando para Windows..."
    cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
    cmake --build build-windows

    echo "🔍 Detectando binario Windows..."
    WIN_BIN=$(find build-windows -maxdepth 1 -type f -name "*.exe" | head -n 1)
    if [[ -z "$WIN_BIN" ]]; then
        echo "❌ No se encontró binario .exe en build-windows/"
        exit 1
    fi

    WIN_NAME=$(basename "$WIN_BIN")
    echo "✅ Binario Windows detectado: $WIN_NAME"

    echo "🔍 Verificando binario Windows..."
    x86_64-w64-mingw32-objdump -p "$WIN_BIN" | grep DLL || echo "✅ Binario estático Windows generado correctamente."

    echo "📦 Copiando binario Windows a dist/..."
    cp "$WIN_BIN" "dist/${WIN_NAME%.exe}-windows.exe"

else
    echo "⚠️ mingw-w64 no está instalado. Se omite la compilación para Windows."
fi

echo "🎉 Todo listo. Binarios disponibles en el directorio 'dist/'."

