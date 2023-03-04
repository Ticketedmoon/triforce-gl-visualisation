#include <GLFW/glfw3.h>

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
        Joystick() = default;

        unsigned int calculateNewFov(bool joystickPresent, unsigned int fov)
        {
            if (joystickPresent)
            {
                int axesCount;
                const float *axes = glfwGetJoystickAxes(GLFW_JOYSTICK_1, &axesCount);
                joystickButtons = {axes[0], axes[1], axes[2], axes[3], axes[4], axes[5]};
                if (joystickButtons.R2 > -0.3)
                {
                    fov -= (joystickButtons.R2 + 1);
                }
                if (joystickButtons.L2 > -0.3)
                {
                    fov += (joystickButtons.L2 + 1);
                }
            }
            return fov;
        }

        JoystickButtons getJoystickButtons() 
        {
            return joystickButtons;
        }

    private:
        JoystickButtons joystickButtons = { 0.0f, 0.0f, 0.0f, 0.0f, 0.0f, 0.0f };
};