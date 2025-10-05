set(CMAKE_SYSTEM_NAME Linux)
set(CMAKE_C_COMPILER gcc)
set(CMAKE_CXX_COMPILER g++)

set(CMAKE_FIND_LIBRARY_SUFFIXES .a)
set(BUILD_SHARED_LIBS OFF)

set(CMAKE_C_FLAGS "-static")
set(CMAKE_CXX_FLAGS "-static -static-libgcc -static-libstdc++")
