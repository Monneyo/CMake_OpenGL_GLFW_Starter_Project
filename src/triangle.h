#ifndef TRIANGLE_H
#define TRIANGLE_H

#include <glad/glad.h>
#include <vector>

/**
 * @class Triangle
 * @brief Manages a simple triangle mesh with vertex data and rendering
 */
class Triangle
{
private:
    unsigned int VAO; // Vertex Array Object
    unsigned int VBO; // Vertex Buffer Object
    std::vector<float> vertices;

public:
    /**
     * @brief Constructor - initializes the triangle with vertex data
     */
    Triangle();

    /**
     * @brief Destructor - cleans up OpenGL buffers
     */
    ~Triangle();

    /**
     * @brief Renders the triangle
     */
    void draw();

    /**
     * @brief Gets the VAO handle
     * @return unsigned int The VAO ID
     */
    unsigned int getVAO() const;
};

#endif // TRIANGLE_H