cmake_minimum_required(VERSION 3.26)
project(CryptoMaster VERSION 1.0.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

option(BUILD_SHARED_LIBS "Build CryptoMaster as a shared library" ON)

add_library(CryptoMaster
        FileHandler.cpp
        FileHandler.h
        Utils.cpp
        Utils.h
)

target_include_directories(CryptoMaster PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<INSTALL_INTERFACE:include>
)

set_target_properties(CryptoMaster PROPERTIES
        VERSION ${PROJECT_VERSION}
        SOVERSION ${PROJECT_VERSION_MAJOR}
        CXX_VISIBILITY_PRESET hidden
        VISIBILITY_INLINES_HIDDEN ON
)

include(GNUInstallDirs)

install(TARGETS CryptoMaster
        EXPORT CryptoMasterTargets
        LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}    # (.so/.dylib)
        ARCHIVE DESTINATION ${CMAKE_INSTALL_LIBDIR}    # (.a)
        RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}    # (opzionale)
        INCLUDES DESTINATION ${CMAKE_INSTALL_INCLUDEDIR} # Per header
)

install(FILES
        FileHandler.h
        Utils.h
        DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/CryptoMaster
)

install(EXPORT CryptoMasterTargets
        FILE CryptoMasterTargets.cmake
        NAMESPACE CryptoMaster::
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CryptoMaster
)

include(CMakePackageConfigHelpers)

write_basic_package_version_file(
        "${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfigVersion.cmake"
        VERSION ${PROJECT_VERSION}
        COMPATIBILITY SameMajorVersion
)

configure_package_config_file(
        "${CMAKE_CURRENT_SOURCE_DIR}/Config/CryptoMasterConfig.cmake.in"
        "${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfig.cmake"
        INSTALL_DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CryptoMaster
        PATH_VARS CMAKE_INSTALL_INCLUDEDIR
)

install(FILES
        "${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterConfigVersion.cmake"
        DESTINATION ${CMAKE_INSTALL_LIBDIR}/cmake/CryptoMaster
)

export(EXPORT CryptoMasterTargets
        FILE "${CMAKE_CURRENT_BINARY_DIR}/CryptoMasterTargets.cmake"
        NAMESPACE CryptoMaster::
)