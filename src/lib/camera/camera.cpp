#include "../../headers/camera.hpp"

Camera::Camera() = default;

Camera::Camera(uint32_t windowWidth, uint32_t windowHeight, Shader& shader, 
               glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp,
               float fov, float pitch, float yaw)
{
    m_windowWidth = windowWidth;
    m_windowHeight = windowHeight;
    m_shader = shader;
    m_cameraPos = cameraPos;
    m_cameraFront = cameraFront;
    m_cameraUp = cameraUp;
    m_fov = fov;
    m_pitch = pitch;
    m_yaw = yaw;
    
    updateCameraFront();
}

void Camera::refresh()
{
    float radius = 30.0f;
    float camX = static_cast<float>(sin(glfwGetTime()) * radius);
    float camZ = static_cast<float>(cos(glfwGetTime()) * radius);

    glm::mat4 view = glm::lookAt(m_cameraPos, m_cameraPos + m_cameraFront, m_cameraUp); 
    view = glm::translate(view, glm::vec3(0.0f, 0.0f, -8.0f));
    glm::mat4 projection = glm::perspective(glm::radians(m_fov), (float)m_windowWidth / (float)m_windowHeight, 0.1f, 100.0f);

    m_shader.setMat4("view", view);
    m_shader.setMat4("projection", projection);
}

glm::vec3 Camera::getCameraPos()
{
    return this->m_cameraPos;
}

glm::vec3 Camera::getCameraFront()
{
    return this->m_cameraFront;
}

glm::vec3 Camera::getCameraUp()
{
    return this->m_cameraUp;
}

float Camera::getFov()
{
    return this->m_fov;
}

void Camera::setCameraPos(glm::vec3 cameraPos)
{
    this->m_cameraPos = cameraPos;
}

void Camera::updateCameraFront()
{
    glm::vec3 direction;
    direction.x = cos(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    direction.y = sin(glm::radians(m_pitch));
    direction.z = sin(glm::radians(m_yaw)) * cos(glm::radians(m_pitch));
    this->m_cameraFront = glm::normalize(direction);
}

void Camera::setFov(uint32_t fov)
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

void Camera::updateRotationAxes(float xoffset, float yoffset, bool invertedY)
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
