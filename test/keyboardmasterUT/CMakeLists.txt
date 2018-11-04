#project(keyboardMasterUT)
set(TEST_NAME keyboardmasterUT)

target_include_directories(${TEST_NAME} ${CMAKE_CURRENT_SOURCE_DIR}/../../3rdparty)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(${TEST_NAME} ${SOURCES})

target_link_libraries(${TEST_NAME} gmock_main frameworkLib)