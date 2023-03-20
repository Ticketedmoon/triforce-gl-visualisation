#pragma once

#include "../window/window_manager.hpp"
#include "../graphics/renderer.hpp"
#include "../shader/shader.hpp"
#include "../controller/joystick.hpp"
#include "../controller/keyboard.hpp"
#include "../camera/camera.hpp"

#include <vector>

static const uint32_t WINDOW_WIDTH = 1280;
static const uint32_t WINDOW_HEIGHT = 720;

static float lastMouseX = WINDOW_WIDTH / 2;
static float lastMouseY = WINDOW_HEIGHT / 2;

static bool firstMouse = true;

// Array in-case we want more positions
static const std::vector<glm::vec3> cubePositions = {
    glm::vec3(0.0f,  0.0f,  0.0f)
};

static Camera camera;

class Engine
{
    public:
        Engine()
        {
            windowManager = WindowManager(WINDOW_WIDTH, WINDOW_HEIGHT);
            window = windowManager.init();

            if (window == nullptr)
            {
                throw std::runtime_error("Failed to load window context, window is null");
            }

            Renderer renderer;
            renderer.enable(GL_DEPTH_TEST);
            renderer.storeVertexDataOnGpu();

            glfwSetCursorPosCallback(window, mouse_callback); 
            glfwSetScrollCallback(window, scroll_callback); 

            shader = Shader("src/data/shader/vertex.shader", "src/data/shader/fragment.shader");
            shader.use();

            glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
            glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

            camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, shader, cameraPos, cameraPos + cameraFront, cameraUp, 45.0f, 0.0f, -90.f);
        }

        void startGameLoop()
        {
            while(!glfwWindowShouldClose(window))
            {
                windowManager.processInput(camera, lastMouseX, lastMouseY);

                draw();

                glfwSwapBuffers(window);
                glfwPollEvents();    
            }
        }

        void tearDown()
        {
            renderer.clearVertexBuffer();
            shader.deleteProgram();
            glfwTerminate();
        }

    private:
        GLFWwindow* window;
        Shader shader;
        WindowManager windowManager;
        Renderer renderer;

        void draw()
        {
            glClearColor(0.0f, 0.0f, 0.5f, 0.2f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            camera.refresh();
            renderer.render(cubePositions, shader);
        }

        // Callbacks

        static void mouse_callback(GLFWwindow* window, double xpos, double ypos)
        {
            if (firstMouse)
            {
                lastMouseX = xpos;
                lastMouseY = ypos;
                firstMouse = false;
            }

            float xOffset = xpos - lastMouseX;
            float yOffset = lastMouseY - ypos; // reversed since y-coordinates range from bottom to top
            lastMouseX = xpos;
            lastMouseY = ypos;

            const float sensitivity = 0.1f;
            xOffset *= sensitivity;
            yOffset *= sensitivity;

            camera.updateRotationAxes(xOffset, yOffset, false);
            camera.updateCameraFront();
        }

        static void scroll_callback(GLFWwindow* window, double xOffset, double yOffset)
        {
            float fov = camera.getFov() - (float)yOffset;
            camera.setFov(fov);
        }
};
