project(frameworkLib)

file(GLOB_RECURSE SOURCES *.cpp)
add_library(frameworkLib SHARED STATIC ${SOURCES})

#target_include_directories(frameworkLib PUBLIC ${PROJECT_SOURCE_DIR} ${SFML_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR} ${SFML_INCLUDE_DIR})
target_link_libraries(frameworkLib ${SFML_LIBRARIES})
