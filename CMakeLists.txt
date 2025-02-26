cmake_minimum_required(VERSION 3.16)
if(NOT EXISTS ${CMAKE_SOURCE_DIR}/cmake/modules/VersionInfo.cmake)
    message(FATAL_ERROR "cmake submodule directory empty, did you 'git clone --recursive'?")
endif()

if(POLICY CMP0122)
    cmake_policy(SET CMP0122 NEW)
endif()
project(libdigidocpp VERSION 3.18.0)
set(CMAKE_MODULE_PATH ${CMAKE_SOURCE_DIR}/cmake/modules)

include(VersionInfo)
include(GNUInstallDirs)

set_env( TSL_URL "https://ec.europa.eu/tools/lotl/eu-lotl.xml" CACHE STRING "TSL trust list primary URL" )
set_env( TSL_CERTS
    ${CMAKE_SOURCE_DIR}/etc/tl-mp1.crt
    ${CMAKE_SOURCE_DIR}/etc/tl-mp2.crt
    ${CMAKE_SOURCE_DIR}/etc/tl-mp3.crt
    ${CMAKE_SOURCE_DIR}/etc/tl-mp4.crt
    ${CMAKE_SOURCE_DIR}/etc/tl-mp5.crt
    ${CMAKE_SOURCE_DIR}/etc/tl-mp6.crt
    ${CMAKE_SOURCE_DIR}/etc/tl-mp7.crt
    ${CMAKE_SOURCE_DIR}/etc/tl-mp8.crt
    CACHE FILEPATH "TSL trust list signing certificates" )
set_env( TSA_URL "http://dd-at.ria.ee/tsa" CACHE STRING "Default TSA URL" )
set_env( SIVA_URL "https://siva.eesti.ee/V3/validate" CACHE STRING "Default SiVa validation service URL" )
set( BUILD_TOOLS YES CACHE BOOL "Build digidoc-tool" )
set( BUILD_SHARED_LIBS YES CACHE BOOL "Build library as SHARED or STATIC" )
set( SIGNCERT "" CACHE STRING "Common name of certificate to used sign binaries, empty skip signing" )
set( CROSSSIGNCERT "" CACHE STRING "Common name of certificate to used cross sign binaries, empty skip signing" )
set(CMAKE_DEBUG_POSTFIX "d" CACHE STRING "Adds a postfix for debug-built libraries.")
set(CPACK_PACKAGE_VERSION ${VERSION})
set(CPACK_GENERATOR RPM)
set(CPACK_PACKAGE_CONTACT "RIA <info@ria.ee>")
set(CPACK_PACKAGE_VENDOR RIA)
set(CPACK_PACKAGING_INSTALL_PREFIX /usr)
list(APPEND CPACK_RPM_RELOCATION_PATHS ${CMAKE_INSTALL_SYSCONFDIR})
set(CPACK_RPM_FILE_NAME RPM-DEFAULT)
set(CPACK_RPM_PACKAGE_RELEASE_DIST ON)
include(CPack)
if( APPLE )
    set( FRAMEWORK YES CACHE BOOL "Build library as Mac OS X Framework" )
endif()

find_package(Doxygen)
find_package(OpenSSL 1.1.1 REQUIRED)
find_package(PKCS11)
#find_package(PoDoFo)
find_package(Threads)
find_package(XmlSecurityC REQUIRED)
find_package(XSD 4.0 REQUIRED)
find_package(ZLIB REQUIRED)
find_package(MiniZip 1 QUIET) # version range (0...<2.0.0) requires CMake>=3.19
if(UNIX AND NOT APPLE)
    find_package(PkgConfig)
    pkg_check_modules(MINIZIP minizip IMPORTED_TARGET)
endif()
find_package(SWIG)
find_package(JNI)
find_package(Python3 COMPONENTS Interpreter Development)

if( DOXYGEN_FOUND )
    configure_file( ${CMAKE_SOURCE_DIR}/etc/Doxyfile.in Doxyfile @ONLY )
    add_custom_target( docs ALL
        Doxygen::doxygen Doxyfile
        WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
        COMMENT "Generating API documentation with Doxygen" VERBATIM
    )
    install( DIRECTORY ${CMAKE_BINARY_DIR}/doc/ DESTINATION ${CMAKE_INSTALL_DOCDIR} )
    install( DIRECTORY doc/ DESTINATION ${CMAKE_INSTALL_DOCDIR} )
endif()

if( WIN32 )
    add_definitions( -DUNICODE -D_CRT_SECURE_NO_WARNINGS -D_SCL_SECURE_NO_WARNINGS -DWIN32_LEAN_AND_MEAN )
endif()

enable_testing()
add_subdirectory(src)
add_subdirectory(test)
add_subdirectory(examples)
