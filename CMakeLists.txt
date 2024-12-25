cmake_minimum_required(VERSION 3.15)
project(jelly)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories
include_directories(${CMAKE_SOURCE_DIR}/deps/include)

# Add source files
file(GLOB SOURCES 
    ${CMAKE_SOURCE_DIR}/src/*.cpp
)

# Add Glad Library
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/deps/lib/gl.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/deps/include)

# Add GLFW library
# GLFW is dynamically built during the workflow and referenced here
add_library(glfw STATIC IMPORTED)
if (APPLE)
    set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/lib/libglfw3.a ${CMAKE_SOURCE_DIR}/deps/lib/libglfw3.dylib)
else ()
    set_target_properties(glfw PROPERTIES IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/lib/libglfw3.a)
endif()
target_include_directories(glfw INTERFACE ${CMAKE_SOURCE_DIR}/deps/include)

# Define the executable
add_executable(jelly ${SOURCES})

# Link libraries to the executable
if (WIN32)
    target_link_libraries(jelly glfw glad opengl32) # OpenGL32 for Windows
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(METAL_LIBRARY Metal REQUIRED)
    target_link_libraries(jelly glfw glad ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${METAL_LIBRARY})
else ()
    find_package(X11 REQUIRED)
    target_link_libraries(jelly glfw glad X11 pthread)
endif()
