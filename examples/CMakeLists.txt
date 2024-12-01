cmake_minimum_required(VERSION 3.15)
project(MyCryptoApp)

include(${CMAKE_BINARY_DIR}/conan_toolchain.cmake)

add_executable(MyCryptoApp src/test_main.cpp)

find_package(cryptomaster REQUIRED)
target_link_libraries(MyCryptoApp cryptomaster::cryptomaster)
