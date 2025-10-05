set(CMAKE_SYSTEM_NAME Windows)
set(CMAKE_C_COMPILER x86_64-w64-mingw32-gcc)
set(CMAKE_CXX_COMPILER x86_64-w64-mingw32-g++)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_C_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")

