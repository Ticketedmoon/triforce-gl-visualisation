#include "../../headers/renderer.hpp"

float vertices[] = {
    // Back
    -1.0f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.0f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
     0.0f,  1.5f, -0.5f,  1.0f, 1.0f,

     0.0f, -0.5f, -0.5f,  0.0f, 0.0f,
     1.0f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

    // Front
    -1.0f, -0.5f, 0.0f,  0.0f, 0.0f,
     0.0f, -0.5f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f,

    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f,
     0.0f,  1.5f, 0.0f,  1.0f, 1.0f,

     0.0f, -0.5f, 0.0f,  0.0f, 0.0f,
     1.0f, -0.5f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
};

int indices[] = {
    // back

    // left, right, top
    0, 1, 2, // left
    3, 4, 5, // top
    6, 7, 8, // right

    // front
    // left, right, top
    9, 10, 11, // left
    12, 13, 14, // top
    15, 16, 17, // right

    // left wall
    5, 14, 0,
    0, 9, 14,
    // right wall
    5, 14, 7,
    7, 16, 14,
    // floor
    0, 9, 7,
    7, 9, 16,
    // inner left wall
    1, 3, 11,
    1, 10, 11,
    // inner right wall
    6, 8, 15,
    8, 15, 17,
    // ceiling wall
    3, 4, 12,
    4, 12, 13
};

static const uint32_t TOTAL_VERTICES = 54;

void Renderer::enable(GLenum flag)
{
    glEnable(flag);
}

void Renderer::storeVertexDataOnGpu()
{
    glGenVertexArrays(1, &vaoId);
    glGenBuffers(1, &vboId);
    glGenBuffers(1, &eboId);

    glBindVertexArray(vaoId);

    glBindBuffer(GL_ARRAY_BUFFER, vboId);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
    glEnableVertexAttribArray(0);

    glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
    glEnableVertexAttribArray(1);

    glBindBuffer(GL_ARRAY_BUFFER, 0); 
    glBindVertexArray(0); 
    
    glBindVertexArray(vaoId);
}

void Renderer::render(const std::vector<glm::vec3> cubePositions, const Shader& shader)
{
    for (int i = 0; i < cubePositions.size(); i++)
    {
        glm::mat4 model = glm::mat4(1.0f);
        model = glm::translate(model, cubePositions[i]);

        float angle = 45.0f * (2.0f); 
        model = glm::rotate(model, glm::radians(angle) * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
        
        shader.setMat4("model", model);
        glDrawElements(GL_TRIANGLES, TOTAL_VERTICES, GL_UNSIGNED_INT, 0);
    }
}

void Renderer::clearVertexBuffer()
{
    glDeleteVertexArrays(1, &vaoId);
    glDeleteBuffers(1, &vboId);
}
