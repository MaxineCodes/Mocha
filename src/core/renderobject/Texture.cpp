//
// Created by maxin on 05/12/2025.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <sstream>
#include <stb_image.h>

#include "../../interface/logger.h"

namespace Mocha
{
    std::string extractTextureName(const char *path)
    {
        std::string p = std::string(path);
        size_t lastSlash = p.find_last_of("/\\");
        std::string filename = (lastSlash != std::string::npos) ? p.substr(lastSlash + 1) : p;
        filename = filename.substr(0, filename.find_last_of('.'));
        return filename.substr(0, filename.find('_'));
    }
    std::string extractTextureType(const char *path)
    {
        std::string p(path);
        size_t lastSlash = p.find_last_of("/\\");
        std::string filename = (lastSlash != std::string::npos)
            ? p.substr(lastSlash + 1) : p;
        filename = filename.substr(0, filename.find_last_of('.'));

        size_t first = filename.find('_');
        size_t second = filename.find('_', first + 1);
        return filename.substr(first + 1, second - first - 1);
    }

    Texture::Texture(const char *path)
    {
        type = extractTextureType(path);
        name = extractTextureName(path);

        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
        // load and generate the texture
        unsigned char *data = stbi_load(path, &width, &height, &channels, 0);
        if (data)
        {
            GLenum format = GL_RGB;
            if (channels == 1)      format = GL_RED;
            else if (channels == 3) format = GL_RGB;
            else if (channels == 4) format = GL_RGBA;

            glTexImage2D(GL_TEXTURE_2D, 0, format, width, height, 0, format, GL_UNSIGNED_BYTE, data);
            glGenerateMipmap(GL_TEXTURE_2D);
        }
        else
        {
            logger::logError("Failed to load texture.");
            logger::logError(path);
            logger::logError(stbi_failure_reason());
        }


        stbi_image_free(data);
    }

    void Texture::use()
    {
        glBindTexture(GL_TEXTURE_2D, textureID);
    }


} // Mocha