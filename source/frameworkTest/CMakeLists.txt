project(frameworkTest)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(frameworkTest ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/.. ${SFML_INCLUDE_DIR})
target_link_libraries(frameworkTest ${SFML_LIBRARIES} frameworkLib) 
