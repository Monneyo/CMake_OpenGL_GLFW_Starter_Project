#include "triangle.h"
#include <iostream>

/**
 * @brief Constructor - initializes the triangle with vertex data
 *
 * Initializes the triangle object by defining its vertices and
 * uploading the vertex data to the GPU.
 *
 * The vertices are defined in counter-clockwise winding order with
 * three floats per vertex (x, y, z coordinates). The bottom left
 * vertex is at (-0.5, -0.5, 0.0), the bottom right vertex is at
 * (0.5, -0.5, 0.0), and the top vertex is at (0.0, 0.5, 0.0).
 *
 * The vertex data is uploaded to the GPU with GL_STATIC_DRAW as
 * the usage pattern, and the vertex attributes are configured to
 * have three floats per vertex, with no normalization.
 */

Triangle::Triangle()
{
    // Define triangle vertices (x, y, z coordinates)
    // Counter-clockwise winding order
    vertices = {
        // positions
        -0.5f, -0.5f, 0.0f, // bottom left
        0.5f, -0.5f, 0.0f,  // bottom right
        0.0f, 0.5f, 0.0f    // top
    };

    // Generate and bind VAO
    glGenVertexArrays(1, &VAO);
    glBindVertexArray(VAO);

    // Generate and bind VBO
    glGenBuffers(1, &VBO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    // Upload vertex data to GPU
    glBufferData(GL_ARRAY_BUFFER,
                 vertices.size() * sizeof(float),
                 vertices.data(),
                 GL_STATIC_DRAW);

    // Configure vertex attributes (position)
    // location = 0, 3 floats per vertex, no normalization
    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(float), (void *)0);
    glEnableVertexAttribArray(0);

    // Unbind VAO (good practice)
    glBindVertexArray(0);

    std::cout << "Triangle created with VAO: " << VAO << std::endl;
}

/**
 * @brief Destructor - cleans up OpenGL resources
 *
 * Called automatically when the object is destroyed (e.g. when it goes
 * out of scope).  This function will delete the OpenGL resources
 * associated with the triangle, including the Vertex Array Object
 * (VAO) and the Vertex Buffer Object (VBO).  This is an important
 * part of the object's lifecycle, as it prevents memory leaks and
 * ensures that the OpenGL resources are properly cleaned up when they
 * are no longer needed.
 */
Triangle::~Triangle()
{
    // Clean up OpenGL resources
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    std::cout << "Triangle destroyed" << std::endl;
}

/**
 * @brief Draw the triangle
 *
 * Binds the Vertex Array Object (VAO) associated with the triangle
 * and draws the triangle using the vertex data stored in the GPU.
 * The drawing mode is set to GL_TRIANGLES (triangles), and the number of
 * vertices to draw is set to 3.
 *
 * This function is typically called once per frame when rendering the
 * triangle.
 */
void Triangle::draw()
{
    // Bind VAO and draw
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0, 3);
    glBindVertexArray(0);
}

/**
 * @brief Gets the VAO handle
 * @return unsigned int The VAO ID
 *
 * Returns the Vertex Array Object (VAO) handle associated with the triangle.
 * This can be used to bind the VAO and draw the triangle using the
 * vertex data stored in the GPU.
 */
unsigned int Triangle::getVAO() const
{
    return VAO;
}