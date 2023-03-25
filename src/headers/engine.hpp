#pragma once

#include "window_manager.hpp"
#include "renderer.hpp"

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
