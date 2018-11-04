set(TEST_NAME frameworkUT)

include_directories(${CMAKE_SOURCE_DIR}/source ${SFML_INCLUDE_DIR} ${THIRD_PARTY_DIR})

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(${TEST_NAME} ${SOURCES})

target_link_libraries(${TEST_NAME} gmock_main frameworkLib ${SFML_LIBRARIES})