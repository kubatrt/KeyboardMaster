project(frameworkLib)

file(GLOB_RECURSE SOURCES *.cpp)
add_library(frameworkLib SHARED STATIC ${SOURCES})

include_directories(${SFML_INCLUDE_DIR})
target_link_libraries(frameworkLib ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
