#pragma once

#include "window_manager.hpp"
#include "renderer.hpp"
#include "shader.hpp"
#include "joystick.hpp"
#include "keyboard.hpp"
#include "camera.hpp"

#include <vector>

class Engine
{
    public:
        Engine();
        void startGameLoop();
        void tearDown();

    private:
        GLFWwindow* window;
        Shader shader;
        WindowManager windowManager;
        Renderer renderer;

        void draw();
};
