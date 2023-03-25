#pragma once

#include <GLFW/glfw3.h>

#include <glm/glm.hpp>

struct JoystickButtons 
{
    float leftX;
    float leftY;
    float L2;
    float rightX;
    float rightY;
    float R2;
};

class Joystick
{
    public:
        Joystick();
        unsigned int calculateNewFov(bool joystickPresent, unsigned int fov);
        glm::vec3 joystick_movement_callback(glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);
        JoystickButtons getJoystickButtons();

    private:
        JoystickButtons joystickButtons = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
        float deltaTime = 0.0f;	// Time between current frame and last frame
        float lastFrame = 0.0f; // Time of last frame
};
