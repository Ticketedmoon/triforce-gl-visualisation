#include "../../headers/window_manager.hpp"

static Joystick joystick;
static Keyboard keyboard;

// Callbacks
static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    keyboard.single_key_press_callback(window, key, action);
}

WindowManager::WindowManager() = default;

WindowManager::WindowManager(uint32_t width, uint32_t height)
{
    m_width = width;
    m_height = height;
}

GLFWwindow* WindowManager::init()
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

void WindowManager::processInput(Camera& camera, float lastMouseX, float lastMouseY)
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

std::optional<std::pair<float, float>> WindowManager::updatePositionsFromJoystick(float xpos, float ypos, float lastMouseX, float lastMouseY)
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
