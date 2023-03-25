#pragma once

#include "shader.hpp"

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <vector>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Renderer
{
    public:
        void enable(GLenum flag);
        void storeVertexDataOnGpu();
        void render(const std::vector<glm::vec3> cubePositions, const Shader& shader);
        void clearVertexBuffer();

    private:
        uint32_t vboId, vaoId, eboId;

};
