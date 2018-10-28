cmake_minimum_required(VERSION 3.10)

# options



project(keyboardmaster)

list(APPEND CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake/modules")

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_CXX_VISIBILITY_PRESET hidden)

if(${CMAKE_CXX_COMPILER_ID} STREQUAL GNU)
    add_compile_options(-Wl,-fuse-ld=gold)
endif()

if(BUILD_TESTING)
    #include(googletest-download)
endif()

add_subdirectory(source)
if(BUILD_TESTING)
    add_subdirectory(test)
endif()

