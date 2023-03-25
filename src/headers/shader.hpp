#pragma once

#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h> 
#include <GLFW/glfw3.h>

#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>

class Shader
{
    public:
        Shader();
        // constructor generates the shader on the fly
        Shader(const char* vertexPath, const char* fragmentPath);

        // activate the shader
        void use();

        // Get shader program ID
        unsigned int getID();

        // utility uniform functions
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, glm::mat4& mat) const;
        void deleteProgram();

    private:
        unsigned int ID;
        // utility function for checking shader compilation/linking errors.
        void checkCompileErrors(unsigned int shader, std::string type);
};
#endif
