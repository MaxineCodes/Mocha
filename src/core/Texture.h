//
// Created by maxin on 05/12/2025.
//

#ifndef MOCHA_TEXTURE_H
#define MOCHA_TEXTURE_H
#include <glad/glad.h>

namespace Mocha
{
    struct Texture
    {
        GLuint textureID;
        int width, height, channels;

        Texture(const char* path);

        // Default constructor uses a minecraft cobblestone texture
        Texture() { Texture("../../res/textures/cobblestone_basecolour.png"); }
    };
} // Mocha

#endif //MOCHA_TEXTURE_H