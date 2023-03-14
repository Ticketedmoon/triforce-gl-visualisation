#include "../window/window_manager.hpp"
#include "../shader/shader.hpp"
#include "../controller/joystick.hpp"
#include "../controller/keyboard.hpp"
#include "../camera/camera.hpp"

#include <optional>

#pragma once

static const uint32_t WINDOW_WIDTH = 1280;
static const uint32_t WINDOW_HEIGHT = 720;

static float lastMouseX = WINDOW_WIDTH / 2;
static float lastMouseY = WINDOW_HEIGHT / 2;

static bool firstMouse = true;

// Array in-case we want more positions
static const glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f)
};

static Camera camera;
static Joystick joystick;
static keyboard keyboard;

static const uint32_t TOTAL_VERTICES = 54;

class Engine
{
    public:
        Engine()
        {
            windowManager = WindowManager(WINDOW_WIDTH, WINDOW_HEIGHT);
            window = windowManager.init();
        }

        bool create()
        {
            if (window == NULL)
            {
                return false;
            }
            
            windowManager.storeVertexDataOnGpu();
            glfwSetCursorPosCallback(window, mouse_callback); 
            glfwSetScrollCallback(window, scroll_callback); 
            glfwSetKeyCallback(window, key_callback);

            shader = Shader("src/data/shader/vertex.shader", "src/data/shader/fragment.shader");

            glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
            glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
            glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

            camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, shader.getID(), cameraPos, cameraPos + cameraFront, cameraUp, 45.0f, 0.0f, -90.f);
            return true;
        }

        void startGameLoop()
        {
            while(!glfwWindowShouldClose(window))
            {
                processInput();

                draw();

                glfwSwapBuffers(window);
                glfwPollEvents();    
            }
        }

        void tearDown()
        {
            windowManager.clearVertexBuffer();
            shader.deleteProgram();
            glfwTerminate();
        }

    private:
        GLFWwindow* window;
        Shader shader;
        WindowManager windowManager;

        std::optional<std::pair<float, float>> updatePositionsFromJoystick(float xpos, float ypos)
        {
            if (xpos > 0.3 || xpos < -0.3 || ypos > 0.3 || ypos < -0.3)
            {
                lastMouseX -= xpos;
                lastMouseY += ypos;
                
                const float sensitivity = 3.0f;
                float xOffset = xpos * sensitivity;
                float yOffset = ypos * sensitivity;
                return std::make_pair(xOffset, yOffset);
            }
            return std::nullopt;
        }

        void processInput()
        {
            bool joystickPresent = glfwJoystickPresent(GLFW_JOYSTICK_1);
            uint32_t fov = joystick.calculateNewFov(joystickPresent, camera.getFov());
            camera.setFov(fov);
            JoystickButtons buttons = joystick.getJoystickButtons();

            glm::vec3 cameraPos = keyboard.movement_key_press_callback(window, camera.getCameraPos(), camera.getCameraFront(), camera.getCameraUp());
            cameraPos = joystick.joystick_movement_callback(cameraPos, camera.getCameraFront(), camera.getCameraUp());
            camera.setCameraPos(cameraPos);

            auto offsetPair = updatePositionsFromJoystick(buttons.rightX, buttons.rightY);
            if (offsetPair)
            {
                camera.updateRotationAxes(offsetPair.value().first, offsetPair.value().second, true);
                camera.updateCameraFront();
            }
        }

        void draw()
        {
            glClearColor(0.0f, 0.0f, 0.5f, 0.2f);
            glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

            shader.use();
            camera.view(cubePositions);

            glDrawElements(GL_TRIANGLES, TOTAL_VERTICES, GL_UNSIGNED_INT, 0);
        }

        // Callbacks

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            keyboard.single_key_press_callback(window, key, action);
        }

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

        static void scroll_callback(GLFWwindow* window, double , double yoffset)
        {
            float fov = camera.getFov() - (float)yoffset;
            camera.setFov(fov);
        }
};