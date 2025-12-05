//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_SHADER_H
#define MOCHA_SHADER_H
#include <string>

#include <glad/glad.h>

namespace Mocha
{
    class Shader
    {
    public:
        unsigned int programID;

        Shader(const char* vertexPath, const char* fragmentPath);
        ~Shader();

        GLuint shaderProgramID;

        char infoLog[512];
        int success;

        void use() const;
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;

    private:
        static std::string readFileFromPath(const char* path);
        GLuint createShader(std::string shaderCode, GLenum type);


    };
} // Mocha

#endif //MOCHA_SHADER_H