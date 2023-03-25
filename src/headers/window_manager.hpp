#pragma once

#include "shader.hpp"
#include "camera.hpp"
#include "keyboard.hpp"
#include "joystick.hpp"

#include <vector>
#include <optional>

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
