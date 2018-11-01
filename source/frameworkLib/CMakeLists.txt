
project(frameworkLib)

#Add the files
file(GLOB_RECURSE SOURCES *.cpp)

add_library(frameworkLib SHARED STATIC ${SOURCES})

find_package(SFML 2 REQUIRED network audio graphics window system)
if(SFML_FOUND)
  include_directories(${SFML_INCLUDE_DIR})
  target_link_libraries(frameworkLib ${SFML_LIBRARIES} ${SFML_DEPENDENCIES})
endif()

