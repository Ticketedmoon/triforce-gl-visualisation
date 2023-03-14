#pragma once

#include <glad/glad.h> 
#include <iostream>
#include <GLFW/glfw3.h>

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

            GLFWwindow* m_window = glfwCreateWindow(m_width, m_height, "Application", NULL, NULL);
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
            glEnable(GL_DEPTH_TEST);

            return m_window;
        }

        void storeVertexDataOnGpu()
        {
            glGenVertexArrays(1, &vaoId);
            glGenBuffers(1, &vboId);
            glGenBuffers(1, &eboId);

            glBindVertexArray(vaoId);

            glBindBuffer(GL_ARRAY_BUFFER, vboId);
            glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

            glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, eboId);
            glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

            glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)0);
            glEnableVertexAttribArray(0);

            glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 5 * sizeof(float), (void*)(3 * sizeof(float)));
            glEnableVertexAttribArray(1);

            glBindBuffer(GL_ARRAY_BUFFER, 0); 
            glBindVertexArray(0); 
            
            glBindVertexArray(vaoId);
        }

        void clearVertexBuffer()
        {
            glDeleteVertexArrays(1, &vaoId);
            glDeleteBuffers(1, &vboId);
        }

    private:
        uint32_t m_width, m_height;
        uint32_t vboId, vaoId, eboId;

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height)
        {
            glViewport(0, 0, width, height);
        }

};