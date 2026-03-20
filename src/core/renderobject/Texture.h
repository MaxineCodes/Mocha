//
// Created by maxin on 05/12/2025.
//

#ifndef MOCHA_TEXTURE_H
#define MOCHA_TEXTURE_H
#include <glad/glad.h>
#include <string>

namespace Mocha
{
    struct Texture
    {
        GLuint textureID;
        std::string type;
        int width, height, channels;

        Texture(const char* path);
        Texture() { Texture("res/textures/cobblestone_basecolour.png");}

        void use();
    };
} // Mocha

#endif //MOCHA_TEXTURE_H