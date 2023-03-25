#pragma once

#include "shader.hpp"

#include <vector>

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
