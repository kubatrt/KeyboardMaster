cmake_minimum_required(VERSION 3.10)

# options
option(BUILD_SHARED_LIBS "Global flag to cause `add_library()` to create shared libraries if on." OFF)
option(CMAKE_EXPORT_COMPILE_COMMANDS "Enable/Disable output of compile commands during generation." ON)

set(CMAKE_INSTALL_PREFIX "${CMAKE_SOURCE_DIR}/stage" CACHE STRING "Install path prefix, prepended onto install directories.")


project(keyboardmaster)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

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

# Includes
if(BUILD_TESTING)
    #include(googletest-download)
endif()


add_subdirectory(doc)
add_subdirectory(source)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

