#!/bin/bash
set -e

echo "🧹 Limpiando builds anteriores..."
rm -rf build-linux build-windows dist

mkdir -p dist

echo "🛠️ Compilando estáticamente para Linux..."
cmake -B build-linux -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-linux-static.cmake
cmake --build build-linux

echo "🔍 Verificando binario Linux..."
ldd build-linux/Proyecto1_eddSS2025 || echo "✅ Binario estático Linux generado correctamente."

echo "📦 Empaquetando binario Linux..."
cp build-linux/Proyecto1_eddSS2025 dist/
tar -czf dist/Proyecto1_eddSS2025-linux.tar.gz -C dist Proyecto1_eddSS2025
rm dist/Proyecto1_eddSS2025

echo "🛠️ Verificando disponibilidad de mingw-w64..."
if command -v x86_64-w64-mingw32-g++ >/dev/null 2>&1; then
    echo "✅ mingw-w64 encontrado. Compilando para Windows..."
    cmake -B build-windows -S . -DCMAKE_TOOLCHAIN_FILE=cmake/toolchain-windows-static.cmake
    cmake --build build-windows

    echo "🔍 Verificando binario Windows..."
    x86_64-w64-mingw32-objdump -p build-windows/Proyecto1_eddSS2025.exe | grep DLL || echo "✅ Binario estático Windows generado correctamente."

    echo "📦 Empaquetando binario Windows..."
    cp build-windows/Proyecto1_eddSS2025.exe dist/
    zip -j dist/Proyecto1_eddSS2025-windows.zip dist/Proyecto1_eddSS2025.exe
    rm dist/Proyecto1_eddSS2025.exe
else
    echo "⚠️ mingw-w64 no está instalado. Se omite la compilación para Windows."
fi

echo "🎉 Todo listo. Binarios empaquetados en el directorio 'dist'."

