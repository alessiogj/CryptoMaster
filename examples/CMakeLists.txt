cmake_minimum_required(VERSION 3.15)
project(MyCryptoApp)

# Includi il toolchain generato da Conan
include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

# Aggiungi l'eseguibile
add_executable(MyCryptoApp src/test_main.cpp)

# Trova e collega la libreria cryptomaster
find_package(cryptomaster REQUIRED)
target_link_libraries(MyCryptoApp cryptomaster::cryptomaster)

# Percorsi include configurati automaticamente da Conan
