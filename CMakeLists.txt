cmake_minimum_required(VERSION 3.15)
project(jelly)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# Include directories for the jelly library
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/include)

# Convert shader files to C headers using xxd
file(GLOB SHADER_FILES
    ${CMAKE_SOURCE_DIR}/shaders/*.vert
    ${CMAKE_SOURCE_DIR}/shaders/*.frag
)

# List of shaders
set(SHADER_FILES 
    ${SHADERS_DIR}/default_vertex_shader.vert
    ${SHADERS_DIR}/default_fragment_shader.frag
)

# Add source files for the jelly library
file(GLOB JELLY_SOURCES 
    ${CMAKE_SOURCE_DIR}/lib/jelly/*.cpp
)

# Define the jelly library
add_library(jelly STATIC ${JELLY_SOURCES})
target_include_directories(jelly PUBLIC ${CMAKE_SOURCE_DIR}/include)

# Add Glad Library
add_library(glad STATIC ${CMAKE_SOURCE_DIR}/deps/lib/gl.c)
target_include_directories(glad PUBLIC ${CMAKE_SOURCE_DIR}/deps/include)

# Add GLFW library
# GLFW is dynamically built during the workflow and referenced here
add_library(glfw STATIC IMPORTED)
if (APPLE)
    set_target_properties(glfw PROPERTIES 
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/lib/libglfw3.a
    )
else ()
    set_target_properties(glfw PROPERTIES 
        IMPORTED_LOCATION ${CMAKE_SOURCE_DIR}/deps/lib/libglfw3.a
    )
endif()
target_include_directories(glfw INTERFACE ${CMAKE_SOURCE_DIR}/deps/include)

# Link the jelly library with dependencies
target_link_libraries(jelly glad glfw)

# Define the sandbox executable
add_executable(sandbox ${CMAKE_SOURCE_DIR}/sandbox/main.cpp)

# Link the sandbox executable with the jelly library and dependencies
if (WIN32)
    target_link_libraries(sandbox jelly glad glfw opengl32) # OpenGL32 for Windows
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(METAL_LIBRARY Metal REQUIRED)
    target_link_libraries(sandbox jelly glad glfw ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${METAL_LIBRARY})
else ()
    find_package(X11 REQUIRED)
    target_link_libraries(sandbox jelly glad glfw X11 pthread)
endif()
