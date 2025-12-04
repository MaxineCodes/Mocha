//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_SHADER_H
#define MOCHA_SHADER_H
#include <string>

#include "imgui_impl_opengl3_loader.h"

namespace Mocha
{
    class Shader
    {
    public:
        unsigned int programID;

        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        GLuint program;
        GLuint vertexShader;
        GLuint fragmentShader;

        void use();
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

    private:
        const char* readFileFromPath(const char* path);


    };
} // Mocha

#endif //MOCHA_SHADER_H