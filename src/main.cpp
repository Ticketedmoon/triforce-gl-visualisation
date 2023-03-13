#include <glad/glad.h> 
#include <GLFW/glfw3.h>
#include <irrKlang.h>
using namespace irrklang;

#include "stdlib.h"
#include <optional>
#include <iostream>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "lib/window/window_manager.hpp"
#include "lib/shader/shader.hpp"
#include "lib/controller/joystick.hpp"
#include "lib/controller/keyboard.hpp"
#include "lib/camera/camera.hpp"

#define STB_IMAGE_IMPLEMENTATION
#include "../include/stb/stb_image.h"

#include <filesystem>

// Variables
uint32_t WINDOW_WIDTH = 800;
uint32_t WINDOW_HEIGHT = 600;

float lastMouseX = WINDOW_WIDTH / 2;
float lastMouseY = WINDOW_HEIGHT / 2;

bool firstMouse = true;

// Array in-case we want more positions
static glm::vec3 cubePositions[] = {
    glm::vec3(0.0f,  0.0f,  0.0f)
};

static Camera camera;
static Joystick joystick;
static keyboard keyboard;

uint32_t TOTAL_VERTICES = 54;

// Function Declarations.
void processInput(GLFWwindow* window);
void startGameLoop(GLFWwindow* window, Shader& shader);
void draw(Shader& shader);

void mouse_callback(GLFWwindow* window, double xpos, double ypos);
void scroll_callback(GLFWwindow* window, double , double yoffset);
void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

int main() 
{
    std::cout << "Hello, Triforce!" << std::endl;
    WindowManager windowManager(WINDOW_WIDTH, WINDOW_HEIGHT);
    GLFWwindow* window = windowManager.init();
    if (window == NULL)
    {
        return 0;
    }

    glfwSetCursorPosCallback(window, mouse_callback); 
    glfwSetScrollCallback(window, scroll_callback); 
    glfwSetKeyCallback(window, key_callback);

	windowManager.storeVertexDataOnGpu();

    Shader shader("src/data/shader/vertex.shader", "src/data/shader/fragment.shader");

    glm::vec3 cameraPos   = glm::vec3(0.0f, 0.0f,  3.0f);
    glm::vec3 cameraFront = glm::vec3(0.0f, 0.0f, -1.0f);
    glm::vec3 cameraUp    = glm::vec3(0.0f, 1.0f,  0.0f);

    camera = Camera(WINDOW_WIDTH, WINDOW_HEIGHT, shader.getID(), cameraPos, cameraPos + cameraFront, cameraUp, 45.0f, 0.0f, -90.f);

	startGameLoop(window, shader);

    windowManager.clearVertexBuffer();
    shader.deleteProgram();
	glfwTerminate();
    return 0;
}

void startGameLoop(GLFWwindow* window, Shader& shader)
{
	while(!glfwWindowShouldClose(window))
	{
		processInput(window);

		draw(shader);

		glfwSwapBuffers(window);
		glfwPollEvents();    
	}
}

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

void processInput(GLFWwindow *window)
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

void draw(Shader& shader)
{
	// Clear the screen with a colour
	glClearColor(0.0f, 0.0f, 0.5f, 0.2f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT); // also clear the depth buffer now!

	// Every shader and rendering call after the `glUseProgram` call will now use this program object (and thus the shaders).
    shader.use();

    camera.view(cubePositions);

    glDrawElements(GL_TRIANGLES, TOTAL_VERTICES, GL_UNSIGNED_INT, 0);
}

// Callbacks

void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyboard.single_key_press_callback(window, key, action);
}

void mouse_callback(GLFWwindow* window, double xpos, double ypos)
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

void scroll_callback(GLFWwindow* window, double , double yoffset)
{
    float fov = camera.getFov() - (float)yoffset;
    camera.setFov(fov);
}