#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"

class Camera
{
    public:
        Camera();
        Camera(uint32_t windowWidth, uint32_t windowHeight, Shader& shader, 
               glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
               float fov, float pitch, float yaw);

        void refresh();

        glm::vec3 getCameraPos();
        glm::vec3 getCameraFront();
        glm::vec3 getCameraUp();

        float getFov();

        void setCameraPos(glm::vec3 cameraPos);

        void updateCameraFront();
        void setFov(uint32_t fov);
        void updateRotationAxes(float xoffset, float yoffset, bool invertedY);

    private:
        uint32_t m_windowWidth, m_windowHeight;
        Shader m_shader;
        glm::vec3 m_cameraPos, m_cameraFront, m_cameraUp;
        float m_fov;
        float m_pitch, m_yaw;

};
