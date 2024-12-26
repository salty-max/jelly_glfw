cmake_minimum_required(VERSION 3.15)
project(jelly)

# Set C++ standard
set(CMAKE_CXX_STANDARD 23)

# Force 64-bit architecture
if (WIN32)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
elseif (UNIX)
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -m64")
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -m64")
endif()

# Set output directories
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

set (SANDBOX_DIR ${CMAKE_SOURCE_DIR}/sandbox)

# Include directories for the jelly library
include_directories(${CMAKE_SOURCE_DIR}/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/include)
include_directories(${CMAKE_SOURCE_DIR}/deps/imgui)
include_directories(${CMAKE_SOURCE_DIR}/deps/imgui/backends)

# Add source files for the jelly library
file(GLOB JELLY_SOURCES 
    ${CMAKE_SOURCE_DIR}/lib/jelly/*.cpp
)

# Include ImGui source files
set(IMGUI_SOURCES
    deps/imgui/imgui.cpp
    deps/imgui/imgui_draw.cpp
    deps/imgui/imgui_demo.cpp
    deps/imgui/imgui_widgets.cpp
    deps/imgui/imgui_tables.cpp
)

# Include ImGui GLFW source files
set(IMGUI_GLFW_SOURCES
    deps/imgui/backends/imgui_impl_glfw.cpp
    deps/imgui/backends/imgui_impl_opengl3.cpp
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

# Add ImGui Library
add_library(imgui STATIC ${IMGUI_SOURCES})
target_include_directories(imgui PUBLIC deps/imgui)

# Add ImGui GLFW Library
add_library(imgui_glfw STATIC ${IMGUI_GLFW_SOURCES})
target_include_directories(imgui_glfw PUBLIC deps/imgui/backends)

# Link the jelly library with dependencies
target_link_libraries(jelly glad glfw imgui imgui_glfw)

# Define the sandbox executable
add_executable(sandbox ${SANDBOX_DIR}/main.cpp)

# Copy textures to the build directory
file(COPY ${SANDBOX_DIR}/textures DESTINATION ${CMAKE_BINARY_DIR}/bin)

# Link the sandbox executable with the jelly library and dependencies
if (WIN32)
    target_link_libraries(sandbox jelly glad glfw imgui imgui_glfw opengl32) # OpenGL32 for Windows
elseif (APPLE)
    find_library(COCOA_LIBRARY Cocoa REQUIRED)
    find_library(IOKIT_LIBRARY IOKit REQUIRED)
    find_library(COREVIDEO_LIBRARY CoreVideo REQUIRED)
    find_library(METAL_LIBRARY Metal REQUIRED)
    target_link_libraries(sandbox jelly glad glfw imgui imgui_glfw ${COCOA_LIBRARY} ${IOKIT_LIBRARY} ${COREVIDEO_LIBRARY} ${METAL_LIBRARY})
else ()
    find_package(X11 REQUIRED)
    target_link_libraries(sandbox jelly glad glfw imgui imgui_glfw X11 pthread)
endif()
