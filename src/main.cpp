#include "config.h"
#include "triangle.h" // ← ADD THIS
#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>

// Function declarations
unsigned int make_shader(const std::string &vertex_filepath, const std::string &fragment_filepath);
unsigned int make_module(const std::string &filepath, unsigned int module_type);

int main()
{
    GLFWwindow *window;

    // Initialize GLFW library
    if (!glfwInit())
    {
        std::cout << "GLFW init failed!" << std::endl;
        return -1;
    }

    // Set OpenGL version to 3.3 Core
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    // Create window
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Triangle Demo", NULL, NULL);
    if (!window)
    {
        std::cout << "Failed to create window!" << std::endl;
        glfwTerminate();
        return -1;
    }

    std::cout << "GLFW works! Window: " << WINDOW_WIDTH << "x" << WINDOW_HEIGHT << std::endl;

    // Make context current
    glfwMakeContextCurrent(window);

    // Initialize GLAD
    if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to initialize GLAD" << std::endl;
        return -1;
    }

    // Set viewport
    glViewport(0, 0, WINDOW_WIDTH, WINDOW_HEIGHT);

    // Create shader program
    unsigned int shader = make_shader("src/shaders/vertex.txt", "src/shaders/fragment.txt");

    // Create triangle object
    Triangle triangle;

    // Set clear color
    glClearColor(0.1f, 0.2f, 0.3f, 1.0f);

    // Main render loop
    while (!glfwWindowShouldClose(window))
    {
        // Poll events
        glfwPollEvents();

        // Clear screen
        glClear(GL_COLOR_BUFFER_BIT);

        // Use shader and draw triangle
        glUseProgram(shader);
        triangle.draw();

        // Swap buffers
        glfwSwapBuffers(window);
    }

    // Cleanup
    glDeleteProgram(shader);
    glfwTerminate();

    return 0;
}

unsigned int make_shader(const std::string &vertex_filepath, const std::string &fragment_filepath)
{
    std::vector<unsigned int> modules;
    modules.push_back(make_module(vertex_filepath, GL_VERTEX_SHADER));
    modules.push_back(make_module(fragment_filepath, GL_FRAGMENT_SHADER));

    unsigned int shader = glCreateProgram();
    for (unsigned int shaderModule : modules)
    {
        glAttachShader(shader, shaderModule);
    }
    glLinkProgram(shader);
    int success;
    glGetProgramiv(shader, GL_LINK_STATUS, &success);
    if (!success)
    {
        char ErrorLog[1024];
        glGetProgramInfoLog(shader, 1024, NULL, ErrorLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << ErrorLog << std::endl;
    }

    for (unsigned int shaderModule : modules)
    {
        glDeleteShader(shaderModule);
    }
    return shader;
}
unsigned int make_module(const std::string &filepath, unsigned int module_type)
{
    std::ifstream file;
    std::stringstream bufferedLines;
    std::string line;

    file.open(filepath);
    while (std::getline(file, line))
    {
        bufferedLines << line << "\n";
    }
    std::string shaderSource = bufferedLines.str();
    const char *shaderSrc = shaderSource.c_str();
    bufferedLines.str(""); // Clear the buffer
    file.close();

    unsigned int shaderModule = glCreateShader(module_type);
    glShaderSource(shaderModule, 1, &shaderSrc, NULL);
    glCompileShader(shaderModule);

    int success;
    glGetShaderiv(shaderModule, GL_COMPILE_STATUS, &success);
    if (!success)
    {
        char ErrorLog[1024];
        glGetProgramInfoLog(shaderModule, 1024, NULL, ErrorLog);
        std::cout << "ERROR::SHADER::COMPILATION_FAILED\n"
                  << ErrorLog << std::endl;
    }

    return shaderModule;
}
