class keyboard
{
    public:
        keyboard() = default;

        void single_key_press_callback(GLFWwindow* window, int key, int action)
        {
            if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS) 
            {
                glfwSetWindowShouldClose(window, true);
            }

            if (key == GLFW_KEY_H && action == GLFW_PRESS) 
            {
                if (polygonState == 0)
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
                }
                else if (polygonState == 1)
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
                }
                else
                {
                    glPolygonMode(GL_FRONT_AND_BACK, GL_POINT);
                    polygonState = -1;
                }
                polygonState++;
            }

            if (key == GLFW_KEY_SPACE && action == GLFW_PRESS)
            {
                if (canPlayAudio)
                {
                    SoundEngine->stopAllSounds();
                } 
                else 
                {
                    SoundEngine->play2D("src/data/audio/light_spirit_appears.ogg", true);
                }
                canPlayAudio = !canPlayAudio;
            }
        }

        glm::vec3 movement_key_press_callback(GLFWwindow* window, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
        {
            float currentFrame = glfwGetTime();
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
            {
                const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
                cameraPos += (cameraSpeed * cameraFront);
            }
            if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
            {
                const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
                cameraPos -= (cameraSpeed * cameraFront);
            }
            if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
            {
                const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
                cameraPos -= (glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
            }
            if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
            {
                const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
                cameraPos += (glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
            }
            return cameraPos;
        }

    private:
        ISoundEngine *SoundEngine = createIrrKlangDevice();
        bool canPlayAudio = false;
        unsigned short polygonState = 1;
        float deltaTime = 0.0f;	// Time between current frame and last frame
        float lastFrame = 0.0f; // Time of last frame
};