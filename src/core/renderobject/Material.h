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
        std::string m_name;
        const Shader *shader;
        std::vector<Texture> textures;

        Material(const Shader* materialShader);
        Material();

        ~Material();

        void addTexture(const Texture& texture);
        void name(const char* name) { this->m_name = name; }

        void Use() const;

    private:
        static const Shader* getDefaultShader();
    };
} // Mocha

#endif //MOCHA_MATERIAL_H