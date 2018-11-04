project(km)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(km ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/.. ${SFML_INCLUDE_DIR})
target_link_libraries(km frameworkLib ${SFML_LIBRARIES})

file(COPY ${PROJECT_DATA_DIR} DESTINATION ${PROJECT_ROOT_DIR}/bin)
