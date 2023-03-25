#include "../../headers/joystick.hpp"

Joystick::Joystick() = default;

unsigned int Joystick::calculateNewFov(bool joystickPresent, unsigned int fov)
{
    if (joystickPresent)
    {
        int axesCount;
        const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
        joystickButtons = {axes[0], axes[1], axes[2], axes[3], axes[4], axes[5]};
        if (joystickButtons.R2 > -0.3)
        {
            fov -= (joystickButtons.R2 + 1);
        }
        if (joystickButtons.L2 > -0.3)
        {
            fov += (joystickButtons.L2 + 1);
        }
    }
    return fov;
}

glm::vec3 Joystick::joystick_movement_callback(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp)
{
    float currentFrame = glfwGetTime();
    deltaTime = currentFrame - lastFrame;
    lastFrame = currentFrame;

    if (joystickButtons.leftY < -0.3)
    {
        const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
        cameraPos += (cameraSpeed * cameraFront);
    }
    if (joystickButtons.leftY > 0.3)
    {
        const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
        cameraPos -= (cameraSpeed * cameraFront);
    }
    if (joystickButtons.leftX < -0.3)
    {
        const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
        cameraPos -= (glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
    }
    if (joystickButtons.leftX > 0.3)
    {
        const float cameraSpeed = 3.5f * deltaTime; // adjust accordingly
        cameraPos += (glm::normalize(glm::cross(cameraFront, cameraUp)) * cameraSpeed);
    }
    return cameraPos;
}

JoystickButtons Joystick::getJoystickButtons() 
{
    return joystickButtons;
}
