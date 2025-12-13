//
// Created by maxin on 05/12/2025.
//

#include "Texture.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

#include "../../interface/logger.h"

namespace Mocha
{
    Texture::Texture(const char *path)
    {
        glGenTextures(1, &textureID);
        glBindTexture(GL_TEXTURE_2D, textureID);
        // set the texture wrapping/filtering options (on the currently bound texture object)
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR_MIPMAP_LINEAR);
        glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
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