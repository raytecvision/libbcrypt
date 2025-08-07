###################################################################################
#
#  Copyright (c) 2014, webvariants GmbH, http://www.webvariants.de
#
#  This file is released under the terms of the MIT license. You can find the
#  complete text in the attached LICENSE file or online at:
#
#  http://www.opensource.org/licenses/mit-license.php
#
#  @author: Tino Rusch (tino.rusch@webvariants.de)
#
###################################################################################

cmake_minimum_required(VERSION 3.5)

project(bcrypt)

enable_language(ASM)

set(MYLIB_VERSION_MAJOR 1)
set(MYLIB_VERSION_MINOR 0)
set(MYLIB_VERSION_PATCH 0)
set(MYLIB_VERSION_STRING ${MYLIB_VERSION_MAJOR}.${MYLIB_VERSION_MINOR}.${MYLIB_VERSION_PATCH})

# just doing cmake . will build a shared or static lib and honor existing environment setting
# to force build static, cmake . -DBUILD_SHARED_LIBS=Off
# to force build shared, cmake . -DBUILD_SHARED_LIBS=On

set(BUILD_SHARED_LIBS Off)

if (NOT BUILD_SHARED_LIBS)
	message ("Building a static library")
else ()
	message ("Building a shared library")
endif ()


set( CMAKE_COLOR_MAKEFILE ON )

set( CMAKE_CXX_FLAGS  "${CMAKE_CXX_FLAGS} -Wall --std=c++11 -O3" )
set( CMAKE_C_FLAGS  "${CMAKE_C_FLAGS} -Wall -O3" )

set( CMAKE_ASM_FLAGS "${CXXFLAGS} -x assembler-with-cpp")

if (MSVC)
    set( SRCFILES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/bcrypt.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/crypt_blowfish.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/crypt_gensalt.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/wrapper.c
)
else ()
    set( SRCFILES
            ${CMAKE_CURRENT_SOURCE_DIR}/src/bcrypt.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/crypt_blowfish.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/crypt_gensalt.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/wrapper.c
            ${CMAKE_CURRENT_SOURCE_DIR}/src/x86.S
)
endif ()

if (NOT WIN32)
        include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include/bcrypt)
else()
        include_directories( ${CMAKE_CURRENT_SOURCE_DIR}/include)
endif()

if (NOT WIN32)
    add_library(${PROJECT_NAME} SHARED ${SRCFILES})
    set_target_properties(${PROJECT_NAME} PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})
    set_target_properties(${PROJECT_NAME} PROPERTIES PUBLIC_HEADER include/bcrypt/BCrypt.hpp)
    target_include_directories(${PROJECT_NAME} PRIVATE include)
    target_include_directories(${PROJECT_NAME} PRIVATE src)
else()
    add_library(${PROJECT_NAME}_shared SHARED ${SRCFILES})
    add_library(${PROJECT_NAME}_static STATIC ${SRCFILES})
    set_target_properties(${PROJECT_NAME}_shared PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})
    set_target_properties(${PROJECT_NAME}_shared PROPERTIES PUBLIC_HEADER include/bcrypt/BCrypt.hpp)
    set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME}_shared PRIVATE include)
    target_include_directories(${PROJECT_NAME}_shared PRIVATE src)
    set_target_properties(${PROJECT_NAME}_static PROPERTIES VERSION ${MYLIB_VERSION_STRING} SOVERSION ${MYLIB_VERSION_MAJOR})
    set_target_properties(${PROJECT_NAME}_static PROPERTIES PUBLIC_HEADER include/bcrypt/BCrypt.hpp)
    set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
    target_include_directories(${PROJECT_NAME}_static PRIVATE include)
    target_include_directories(${PROJECT_NAME}_static PRIVATE src)
    if(CMAKE_BUILD_TYPE STREQUAL "Debug")
        set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME}d)
        set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME}d)
        message("-- Bullet: Debug build")
    elseif(CMAKE_BUILD_TYPE STREQUAL "Release")
        set_target_properties(${PROJECT_NAME}_shared PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
        set_target_properties(${PROJECT_NAME}_static PROPERTIES OUTPUT_NAME ${PROJECT_NAME})
        message("-- Bullet: Release build")
    endif()
endif()

add_executable( ${PROJECT_NAME}_test ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)


if (NOT WIN32)
    target_link_libraries( ${PROJECT_NAME}_test ${PROJECT_NAME})
else()
    target_link_libraries( ${PROJECT_NAME}_test ${PROJECT_NAME}_static)
endif()

include(GNUInstallDirs)

if (NOT WIN32)
    install(TARGETS ${PROJECT_NAME}
        LIBRARY DESTINATION "/opt/raytec/dev/lib"
        ARCHIVE DESTINATION "/opt/raytec/dev/lib"
        RUNTIME DESTINATION "/opt/raytec/dev/lib"
        PUBLIC_HEADER DESTINATION "/opt/raytec/dev/include/bcrypt")
else()
    if (MSVC)
        install(TARGETS ${PROJECT_NAME}_shared
            LIBRARY DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/lib"
            ARCHIVE DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/lib"
            RUNTIME DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/lib"
            PUBLIC_HEADER DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/include/bcrypt")
        install(TARGETS ${PROJECT_NAME}_static
            LIBRARY DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/lib"
            ARCHIVE DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/lib"
            RUNTIME DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/lib"
            PUBLIC_HEADER DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/include/bcrypt")
    else()
        install(TARGETS ${PROJECT_NAME}_shared
            LIBRARY DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/lib"
            ARCHIVE DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/lib"
            RUNTIME DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/lib"
            PUBLIC_HEADER DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/include/bcrypt")
        install(TARGETS ${PROJECT_NAME}_static
            LIBRARY DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/lib"
            ARCHIVE DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/lib"
            RUNTIME DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/lib"
            PUBLIC_HEADER DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/include/bcrypt")
    endif()
endif()

if (NOT WIN32)
    install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION "/opt/raytec/dev/include"
            FILES_MATCHING PATTERN "*.h")
else()
    if (MSVC)
        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION "C:/Raytec-Dev-3/msvc/x64/5.12.12/libbcrypt/include"
                FILES_MATCHING PATTERN "*.h")
    else()
        install(DIRECTORY ${CMAKE_CURRENT_SOURCE_DIR}/include/ DESTINATION "C:/Raytec-Dev-3/mingw/x86/5.5.1/libbcrypt/include"
                FILES_MATCHING PATTERN "*.h")
    endif()
endif()

SET(CPACK_GENERATOR "DEB")
SET(CPACK_SET_DESTDIR ON)

SET(CPACK_DEBIAN_PACKAGE_MAINTAINER "Manuel Romei")
SET(CPACK_PACKAGE_VERSION "1.0.0")
SET(CPACK_PACKAGE_VERSION_MAJOR "1")
SET(CPACK_PACKAGE_VERSION_MINOR "0")
SET(CPACK_PACKAGE_VERSION_PATCH "0")

INCLUDE(CPack)
