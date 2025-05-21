cmake_minimum_required(VERSION 3.10)
project(GraphingCalculator)

set(CMAKE_CXX_STANDARD 17)

# Include paths
include_directories(
    ${PROJECT_SOURCE_DIR}/include
    ${PROJECT_SOURCE_DIR}/lib/glad/include
    ${PROJECT_SOURCE_DIR}/lib/imgui
	${PROJECT_SOURCE_DIR}/src
)

# Source files
file(GLOB_RECURSE SRC
    test_main.cpp
    lib/glad/glad.c
    lib/imgui/imgui.cpp
    lib/imgui/imgui_draw.cpp
    lib/imgui/imgui_tables.cpp
    lib/imgui/imgui_widgets.cpp
    lib/imgui/backends/imgui_impl_opengl3.cpp
    lib/imgui/backends/imgui_impl_glfw.cpp
)

add_executable(GraphingCalculator ${SRC})

# Link with OpenGL and other system libraries
find_package(OpenGL REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_search_module(GLFW REQUIRED glfw3)

target_include_directories(GraphingCalculator PRIVATE ${GLFW_INCLUDE_DIRS})
target_link_libraries(GraphingCalculator ${OPENGL_LIBRARIES} ${GLFW_LIBRARIES})
