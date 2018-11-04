# Enable debug symbols
if (NOT CMAKE_BUILD_TYPE)
    set(CMAKE_BUILD_TYPE Debug CACHE STRING "Choose debug or release" FORCE)
endif()

project(km)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(km ${SOURCES})

# Add /source folder to includes 
include_directories(${PROJECT_SOURCE_DIR})

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(km frameworkLib ${SFML_LIBRARIES})

file(COPY ${PROJECT_DATA_DIR} DESTINATION ${PROJECT_ROOT_DIR}/bin)
