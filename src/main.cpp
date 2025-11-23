#include "config.h"
#include <iostream>

int main()
{
    GLFWwindow *window;
    if (!glfwInit())
    {
        std::cout << "GLFW init failed!" << std::endl;
        return -1;
    }
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Basic Window", NULL, NULL);
    std::cout << "GLFW works! Window: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;
    glfwMakeContextCurrent(window);

    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }
    glfwTerminate();
    return 0;
}