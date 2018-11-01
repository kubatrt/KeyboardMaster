#Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

project(km)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(km ${SOURCES})

message("Including..." ${PROJECT_SOURCE_DIR})
include_directories(${PROJECT_SOURCE_DIR})

find_package(SFML 2 REQUIRED graphics network audio window system)
if(SFML_FOUND)
message(${SFML_INCLUDE_DIR})
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(km ${SFML_LIBRARIES} frameworkLib)
endif()

file(COPY ${CMAKE_SOURCE_DIR}/data DESTINATION ${CMAKE_BINARY_DIR})
