cmake_minimum_required(VERSION 3.15)
project(CryptoMaster VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

find_package(OpenSSL REQUIRED)

add_library(CryptoMaster STATIC
        src/FileHandler.cpp
        src/Utils.cpp
)

target_include_directories(CryptoMaster PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
        $<INSTALL_INTERFACE:include/CryptoMaster>
)

target_link_libraries(CryptoMaster PUBLIC OpenSSL::SSL OpenSSL::Crypto)

set_target_properties(CryptoMaster PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        EXPORT_NAME CryptoMaster
)

add_library(CryptoMaster::CryptoMaster ALIAS CryptoMaster)

include(GNUInstallDirs)
install(TARGETS CryptoMaster
        EXPORT CryptoMasterTargets
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CryptoMaster
)

install(DIRECTORY include/ DESTINATION ${CMAKE_INSTALL_INCLUDEDIR})

install(EXPORT CryptoMasterTargets
        FILE CryptoMasterTargets.cmake
        NAMESPACE CryptoMaster::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CryptoMaster
)

include(CMakePackageConfigHelpers)
write_basic_package_version_file(
        ${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfigVersion.cmake
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        ${CMAKE_CURRENT_SOURCE_DIR}/Config/Config.cmake.in
        ${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfig.cmake
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CryptoMaster
)

install(FILES
        ${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfig.cmake
        ${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfigVersion.cmake
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CryptoMaster
)
