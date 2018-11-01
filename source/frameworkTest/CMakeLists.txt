
project(frameworkTest)

file(GLOB_RECURSE SOURCES *.cpp)
add_executable(frameworkTest ${SOURCES})

include_directories(${PROJECT_SOURCE_DIR}/source)

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(frameworkTest ${SFML_LIBRARIES} frameworkLib) 
endif()

