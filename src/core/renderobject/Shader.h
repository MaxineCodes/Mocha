//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_SHADER_H
#define MOCHA_SHADER_H
#include <string>

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace Mocha
{
    class Shader
    {
    public:
        unsigned int programID;
        std::string name;

        Shader(const char* vertexPath, const char* fragmentPath);
        Shader();
        ~Shader();

        GLuint shaderProgramID;

        char infoLog[512];
        int success;

        void use() const;
        void setBool(const std::string& name, bool value) const;
        void setInt(const std::string& name, int value) const;
        void setFloat(const std::string& name, float value) const;
        void setMat4(const std::string& name, const glm::mat4& matrix) const;
        void setVec3(const std::string &name, const glm::vec3 &value) const;
        void setVec3(const std::string &name, float x, float y, float z) const; // override

    private:
        static std::string readFileFromPath(const char* path);
        GLuint createShader(std::string shaderCode, GLenum type);


    };
} // Mocha

#endif //MOCHA_SHADER_H