project(frameworkTest)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(frameworkTest ${SOURCES})

#target_include_directories(frameworkTest PRIVATE ${SFML_INCLUDE_DIR})
include_directories(${PROJECT_SOURCE_DIR}/.. ${SFML_INCLUDE_DIR})
target_link_libraries(frameworkTest ${SFML_LIBRARIES} frameworkLib) 
