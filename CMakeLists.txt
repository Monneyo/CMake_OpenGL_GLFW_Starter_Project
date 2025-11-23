cmake_minimum_required(VERSION 3.0.0)
project(BlackHoleSimulator VERSION 1.0.0)
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(BlackHoleSimulator 
    src/main.cpp
    src/glad.c
)

target_include_directories(BlackHoleSimulator PRIVATE 
    C:/msys64/ucrt64/include
    ${CMAKE_SOURCE_DIR}/src
)

target_link_libraries(BlackHoleSimulator PRIVATE 
    glfw3
    opengl32
    gdi32
)