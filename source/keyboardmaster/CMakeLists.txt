#Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

project(km)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(km ${SOURCES})

find_package(SFML REQUIRED graphics network audio window system)
target_link_libraries(km ${SFML_LIBRARIES} frameworkLib)

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
