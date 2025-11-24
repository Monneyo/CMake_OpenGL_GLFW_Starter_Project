cmake_minimum_required(VERSION 3.0.0)
project(CMAKE_OPENGL_GLFW_S_PROJECT VERSION 1.0.0)

find_package(OpenGL REQUIRED)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(CMAKE_OPENGL_GLFW_S_PROJECT 
    src/main.cpp
    src/glad.c
    src/triangle.cpp
    src/triangle.h
)

target_include_directories(CMAKE_OPENGL_GLFW_S_PROJECT PRIVATE 
    C:/msys64/ucrt64/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(CMAKE_OPENGL_GLFW_S_PROJECT PRIVATE 
    glfw3 OpenGL::GL
    opengl32
    gdi32
)