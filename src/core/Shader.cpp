//
// Created by maxin on 04/12/2025.
//

#include "Shader.h"

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <glad/glad.h>
#include "../interface/logger.h"

namespace Mocha
{
    Shader::Shader(const char *vertexPath, const char *fragmentPath)
    {
        const char* vertexShaderCode = readFileFromPath(vertexPath);
        const char* fragmentShaderCode = readFileFromPath(fragmentPath);

        unsigned int vertexShader, fragmentShader;
        int success;
        char infoLog[512];

        // vertex Shader
        vertexShader = glCreateShader(GL_VERTEX_SHADER);
        glShaderSource(vertexShader, 1, &vertexShaderCode, NULL);
        glCompileShader(vertexShader);

        // print compile errors if any
        glGetShaderiv(vertexShader, GL_COMPILE_STATUS, &success);
        if(!success)
        {
            glGetShaderInfoLog(vertexShader, 512, NULL, infoLog);
            logger::logGLError("ERROR::SHADER::VERTEX::COMPILATION_FAILED");
            logger::logGLError(infoLog);
        };
    }

    const char * Shader::readFileFromPath(const char *path)
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
           shaderStream << rawShaderCode.rdbuf();
            // close file handlers
            shaderFile.close();
            // convert stream into string
            rawShaderCode = shaderStream.str();
        }
        catch (std::ifstream::failure e)
        {
            logger::logGLError("ERROR::SHADER::FILE_NOT_SUCCESFULLY_READ");
        }

        return rawShaderCode.c_str();
    }
} // Mocha