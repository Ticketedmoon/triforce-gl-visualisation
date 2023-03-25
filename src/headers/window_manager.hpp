#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "shader.hpp"
#include "camera.hpp"
#include "keyboard.hpp"
#include "joystick.hpp"

class WindowManager
{
    public:
        WindowManager();
        WindowManager(uint32_t width, uint32_t height);
        GLFWwindow* init();
        void processInput(Camera& camera, float lastMouseX, float lastMouseY);

    private:
        uint32_t m_width, m_height;
        GLFWwindow* m_window;

        std::optional<std::pair<float, float>> updatePositionsFromJoystick(float xpos, float ypos, float lastMouseX, float lastMouseY);
};
