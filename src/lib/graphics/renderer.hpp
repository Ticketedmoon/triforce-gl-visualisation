class Renderer
{
    public:

        void enable(GLenum flag)
        {
            glEnable(flag);
        }

        void storeVertexDataOnGpu()
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

        void render(const std::vector<glm::vec3> cubePositions, const Shader& shader)
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

        void clearVertexBuffer()
        {
            glDeleteVertexArrays(1, &vaoId);
            glDeleteBuffers(1, &vboId);
        }

    private:
        uint32_t vboId, vaoId, eboId;
        
};