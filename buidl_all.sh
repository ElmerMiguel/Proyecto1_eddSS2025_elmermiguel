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

