
project(frameworkLib)

#Add the files
file(GLOB_RECURSE SOURCES Source/*.cpp)

add_library(frameworkLib SHARED STATIC ${SOURCE_FILES})