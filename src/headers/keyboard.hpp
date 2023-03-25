#pragma once

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <irrKlang.h>
using namespace irrklang;

class Keyboard
{
    public:
        Keyboard();
        void single_key_press_callback(GLFWwindow* window, int key, int action);
        glm::vec3 movement_key_press_callback(GLFWwindow* window, glm::vec3 cameraPos, glm::vec3 cameraFront, glm::vec3 cameraUp);

    private:
        ISoundEngine *SoundEngine = createIrrKlangDevice();
        bool canPlayAudio = false;
        unsigned short polygonState = 1;
        float deltaTime = 0.0f;	// Time between current frame and last frame
        float lastFrame = 0.0f; // Time of last frame
};
