#project(frameworkUT)
set(TEST_NAME frameworkUT)

include_directories(${TEST_NAME} ${SFML_INCLUDE_DIR} ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(${TEST_NAME} ${SOURCES})

target_link_libraries(${TEST_NAME} gmock_main frameworkLib ${SFML_LIBRARIES})