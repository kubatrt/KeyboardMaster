
project(frameworkTest)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(frameworkTest ${SOURCES})

find_package(SFML REQUIRED graphics network audio window system)
target_link_libraries(frameworkTest ${SFML_LIBRARIES} frameworkLib) 