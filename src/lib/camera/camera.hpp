#pragma once

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

class Camera
{
    public:
        Camera() = default;

        Camera(uint32_t windowWidth, uint32_t windowHeight, uint32_t shaderProgramId, 
               glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
               float fov, float pitch, float yaw)
        {
            m_windowWidth = windowWidth;
            m_windowHeight = windowHeight;
            m_shaderProgramId = shaderProgramId;
            m_cameraPos = cameraPos;
            m_cameraFront = cameraFront;
            m_cameraUp = cameraUp;
            m_fov = fov;
            m_pitch = pitch;
            m_yaw = yaw;
            
            updateCameraFront();
        }

        void view(glm::vec3 cubePositions[])
        {
            glm::mat4 view = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            float radius = 30.0f;
            float camX = static_cast<float>(sin(glfwGetTime()) * radius);
            float camZ = static_cast<float>(cos(glfwGetTime()) * radius);

            view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp); 
            view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));

            glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramId, "view"), 1, GL_FALSE, glm::value_ptr(view));

            glm::mat4 projection = glm::perspective(glm::radians(m_fov), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);
            glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramId, "projection"), 1, GL_FALSE, glm::value_ptr(projection));

         
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, cubePositions[0]);

            float angle = 45.0f * (2.0f); 
            model = glm::rotate(model, glm::radians(angle) * (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f));
            
            glUniformMatrix4fv(glGetUniformLocation(m_shaderProgramId, "model"), 1, GL_FALSE, glm::value_ptr(model));
        }

        glm::vec3 getCameraPos()
        {
            return this->m_cameraPos;
        }

        glm::vec3 getCameraFront()
        {
            return this->m_cameraFront;
        }

        glm::vec3 getCameraUp()
        {
            return this->m_cameraUp;
        }

        float getFov()
        {
            return this->m_fov;
        }

        void setCameraPos(glm::vec3 cameraPos)
        {
            this->m_cameraPos = cameraPos;
        }

        void updateCameraFront()
        {
            glm::vec3 direction;
            direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            direction.y = sin(glm::radians(m_pitch));
            direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
            this->m_cameraFront = glm::normalize(direction);
        }

        void setFov(uint32_t fov)
        {
            if (fov < 1.0f)
            {
                fov = 1.0f;
            }
            if (fov > 45.0f)
            {
                fov = 45.0f; 
            }
            this->m_fov = fov;
        }

        void updateRotationAxes(float xoffset, float yoffset, bool invertedY)
        {
            this->m_yaw   += xoffset;
            if (invertedY) 
            {
                this->m_pitch -= yoffset;      
            } 
            else
            {
                this->m_pitch += yoffset;
            }

            if (m_pitch > 89.0f)
            {
                m_pitch =  89.0f;
            }
            if (m_pitch < -89.0f)
            {
                m_pitch = -89.0f;
            }
        }

    private:
        uint32_t m_windowWidth, m_windowHeight, m_shaderProgramId;
        glm::vec3 m_cameraPos, m_cameraFront, m_cameraUp;
        float m_fov;
        float m_pitch, m_yaw;

};