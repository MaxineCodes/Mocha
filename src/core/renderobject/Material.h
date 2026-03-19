//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_MATERIAL_H
#define MOCHA_MATERIAL_H

#include <vector>

#include "Shader.h"
#include "Texture.h"

namespace Mocha
{
    class Material
    {
    public:
        std::string name;
        Shader shader;
        std::vector<Texture> textures;

        Material();
        ~Material();

        void Use();


    };
} // Mocha

#endif //MOCHA_MATERIAL_H