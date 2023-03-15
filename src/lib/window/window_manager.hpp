#pragma once

#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include <optional>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "../shader/shader.hpp"
#include "../camera/camera.hpp"
#include "../controller/keyboard.hpp"
#include "../controller/joystick.hpp"

float vertices[] = {
    // Back
    -1.0f, -0.5f, -0.5f,  0.0f, 0.0f,
     0.0f, -0.5f, -0.5f,  1.0f, 0.0f,
    -0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

    -0.5f,  0.5f, -0.5f,  0.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 0.0f,
     0.0f,  1.5f, -0.5f,  1.0f, 1.0f,

     0.0f, -0.5f, -0.5f,  0.0f, 0.0f,
     1.0f, -0.5f, -0.5f,  1.0f, 0.0f,
     0.5f,  0.5f, -0.5f,  1.0f, 1.0f,

    // Front
    -1.0f, -0.5f, 0.0f,  0.0f, 0.0f,
     0.0f, -0.5f, 0.0f,  1.0f, 0.0f,
    -0.5f,  0.5f, 0.0f,  1.0f, 1.0f,

    -0.5f,  0.5f, 0.0f,  0.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 0.0f,
     0.0f,  1.5f, 0.0f,  1.0f, 1.0f,

     0.0f, -0.5f, 0.0f,  0.0f, 0.0f,
     1.0f, -0.5f, 0.0f,  1.0f, 0.0f,
     0.5f,  0.5f, 0.0f,  1.0f, 1.0f,
};

int indices[] = {
    // back

    // left, right, top
    0, 1, 2, // left
    3, 4, 5, // top
    6, 7, 8, // right

    // front
    // left, right, top
    9, 10, 11, // left
    12, 13, 14, // top
    15, 16, 17, // right

    // left wall
    5, 14, 0,
    0, 9, 14,
    // right wall
    5, 14, 7,
    7, 16, 14,
    // floor
    0, 9, 7,
    7, 9, 16,
    // inner left wall
    1, 3, 11,
    1, 10, 11,
    // inner right wall
    6, 8, 15,
    8, 15, 17,
    // ceiling wall
    3, 4, 12,
    4, 12, 13
};

static const uint32_t TOTAL_VERTICES = 54;

static Joystick joystick;
static keyboard keyboard;

class WindowManager
{
    public:
        WindowManager() = default;
        
        WindowManager(uint32_t width, uint32_t height)
        {
            m_width = width;
            m_height = height;
        }

        GLFWwindow* init()
        {
            glfwInit();
            glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
            glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
            glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

            m_window = glfwCreateWindow(m_width, m_height, "Application", NULL, NULL);
            if (m_window == NULL)
            {
                std::cout << "Failed to create GLFW window" << std::endl;
                glfwTerminate();
                return NULL;
            }

            glfwMakeContextCurrent(m_window);
            if (!gladLoadGLLoader((GLADloadproc) glfwGetProcAddress))
            {
                std::cout << "Failed to initialize GLAD" << std::endl;
                return NULL;
            }  

            glfwSetFramebufferSizeCallback(m_window, framebuffer_size_callback); 
            glfwSetInputMode(m_window, GLFW_CURSOR, GLFW_CURSOR_DISABLED);
            
            glfwSetKeyCallback(m_window, key_callback);

            return m_window;
        }

        void processInput(Camera& camera, float lastMouseX, float lastMouseY)
        {
            bool joystickPresent = glfwJoystickPresent(GLFW_JOYSTICK_1);
            uint32_t fov = joystick.calculateNewFov(joystickPresent, camera.getFov());
            camera.setFov(fov);
            JoystickButtons buttons = joystick.getJoystickButtons();

            glm::vec3 cameraPos = keyboard.movement_key_press_callback(m_window, camera.getCameraPos(), camera.getCameraFront(), camera.getCameraUp());
            cameraPos = joystick.joystick_movement_callback(cameraPos, camera.getCameraFront(), camera.getCameraUp());
            camera.setCameraPos(cameraPos);

            auto offsetPair = updatePositionsFromJoystick(buttons.rightX, buttons.rightY, lastMouseX, lastMouseY);
            if (offsetPair)
            {
                camera.updateRotationAxes(offsetPair.value().first, offsetPair.value().second, true);
                camera.updateCameraFront();
            }
        }

    private:
        uint32_t m_width, m_height;
        GLFWwindow* m_window;

        std::optional<std::pair<float, float>> updatePositionsFromJoystick(float xpos, float ypos, float lastMouseX, float lastMouseY)
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

        // Callbacks

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

        static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
        {
            keyboard.single_key_press_callback(window, key, action);
        }

};