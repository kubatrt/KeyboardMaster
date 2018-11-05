cmake_minimum_required(VERSION 3.9.2)

project(keyboardmaster)

# Options
option(BUILD_TESTS "Build test executable" ON)
option(GEN_DOCS "Generate documentation" OFF)
option(ENABLE_COVERAGE "Enable code coverage" OFF)
option(BUILD_SHARED_LIBS "Global flag to cause `add_library()` to create shared libraries if on." OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Enable/Disable output of compile commands during generation." ON)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/stage" CACHE STRING "Install path prefix, prepended onto install directories.")

# Project cache variables
set(PROJECT_ROOT_DIR ${PROJECT_SOURCE_DIR} CACHE INTERNAL "" FORCE)
set(PROJECT_DATA_DIR ${PROJECT_SOURCE_DIR}/data CACHE INTERNAL "" FORCE)
set(THIRD_PARTY_DIR ${PROJECT_SOURCE_DIR}/3rdparty CACHE INTERNAL "" FORCE)

set(CMAKE_SOURCE_DIR ${PROJECT_SOURCE_DIR}/source)	# not propagate
set(CMAKE_BINARY_DIR ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR}/lib)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR})

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake")

#find_package(Boost REQUIRED)
#find_package(Git REQUIRED)
find_package(SFML 2 REQUIRED graphics network audio window system)

# set C++ standard
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

# Set C standard
set(CMAKE_C_STANDARD 11)
set(CMAKE_C_STANDARD_REQUIRED ON)
set(CMAKE_C_EXTENSIONS OFF)
set(CMAKE_C_VISIBILITY_PRESET hidden)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    add_compile_options(-Wl,-fuse-ld=gold)
endif()

# Build configuration, 'Debug' by default
if (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)
    message(STATUS "Setting build type to 'Release' as no build type was specified")
    set(CMAKE_BUILD_TYPE "Debug" CACHE STRING "Choose the build type (Debug/Release)" FORCE)
endif (NOT CMAKE_BUILD_TYPE AND NOT CMAKE_CONFIGURATION_TYPES)

# Includes
if(BUILD_TESTS)
	include(CTest)
    include(download/googletest)
endif()


add_subdirectory(source)
if (GEN_DOCS)
    add_subdirectory(doc)
endif (GEN_DOCS)
if(BUILD_TESTS)
    add_subdirectory(test)
endif()

