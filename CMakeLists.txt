cmake_minimum_required(VERSION 3.14)
project(GraphingCalculator)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)


include_directories(
    includes
    lib/glad/include
    lib/imgui
    lib/imgui/backends
)


file(GLOB_RECURSE SOURCES
    src/*.cpp
)

set(IMGUI_SOURCES
    lib/imgui/imgui.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/imgui_demo.cpp
    lib/imgui/backends/imgui_impl_glfw.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
)


add_library(glad STATIC
    lib/glad/src/glad.c
)


find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)
include_directories(${GLFW_INCLUDE_DIRS})


find_package(OpenGL REQUIRED)


add_executable(GraphingCalculator
    ${SOURCES}
    ${IMGUI_SOURCES}
)

target_link_libraries(GraphingCalculator
    glad
    ${GLFW_LIBRARIES}
    ${OPENGL_gl_LIBRARY}
    dl
)


add_custom_command(TARGET GraphingCalculator POST_BUILD
    COMMAND ${CMAKE_COMMAND} -E make_directory "${CMAKE_CURRENT_BINARY_DIR}/shaders"
    COMMAND ${CMAKE_COMMAND} -E copy_directory
        "${CMAKE_SOURCE_DIR}/shaders"
        "${CMAKE_CURRENT_BINARY_DIR}/shaders"
)
