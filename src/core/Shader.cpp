//
// Created by maxin on 04/12/2025.
//

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <cstdlib>

#include "../interface/logger.h"
#include <string>


namespace Mocha
{
    Shader::Shader(const char *vertexPath, const char *fragmentPath)
    {
        // Read the code from the shader file
        std::string vertexShaderCode = readFileFromPath(vertexPath);
        std::string fragmentShaderCode = readFileFromPath(fragmentPath);

        logger::logDebug(vertexShaderCode.c_str());

        // Compile shaders and store the ID as GLuint
        vertexShaderID = createShader(vertexShaderCode);
        fragmentShaderID = createShader(fragmentShaderCode);

        // Shader program
        shaderProgramID = glCreateProgram();
        glAttachShader(shaderProgramID, vertexShaderID);
        glAttachShader(shaderProgramID, fragmentShaderID);
        glLinkProgram(shaderProgramID);
        // Log linking errors if any
        glGetProgramiv(shaderProgramID, GL_LINK_STATUS, &success);
        if(!success)
        {
            glGetProgramInfoLog(shaderProgramID, 512, NULL, infoLog);
            logger::logGLError("ERROR::SHADER::PROGRAM::LINKING_FAILED");
            logger::logGLError(infoLog);
        }

        // delete the shaders as they're linked into our program now and no longer necessary
        glDeleteShader(vertexShaderID);
        glDeleteShader(fragmentShaderID);
    }

    Shader::~Shader()
    {
        glDeleteProgram(shaderProgramID);
    }

    void Shader::use() const
    {
        glUseProgram(shaderProgramID);
    }

    void Shader::setBool(const std::string &name, bool value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), (int)value);
    }
    void Shader::setInt(const std::string &name, int value) const
    {
        glUniform1i(glGetUniformLocation(shaderProgramID, name.c_str()), value);
    }
    void Shader::setFloat(const std::string &name, float value) const
    {
        glUniform1f(glGetUniformLocation(shaderProgramID, name.c_str()), value);
    }

    std::string Shader::readFileFromPath(const char *path)
    {
        std::string rawShaderCode;
        std::ifstream shaderFile;

        // ensure ifstream objects can throw exceptions:
        shaderFile.exceptions (std::ifstream::failbit | std::ifstream::badbit);

        try
        {
            // open files
            shaderFile.open(path);
            std::stringstream shaderStream;
            // read file's buffer contents into streams
           shaderStream << shaderFile.rdbuf();
            // close file handlers
            shaderFile.close();
            // convert stream into string
            rawShaderCode = shaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            logger::logGLError("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }

        logger::logDebug(path);
        logger::logDebug(rawShaderCode.c_str());

        return rawShaderCode;
    }

    GLuint Shader::createShader(const std::string shaderCode)
    {
        const char* shaderSource = shaderCode.c_str();

        // Compile shader
        GLuint shader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShaderID, 1, &shaderSource, NULL);
        glCompileShader(vertexShaderID);

        // Log compile errors if any
        glGetShaderiv(vertexShaderID, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShaderID, 512, NULL, infoLog);
            logger::logGLError("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
            logger::logGLError(infoLog);
        };

        return shader;
    }
} // Mocha