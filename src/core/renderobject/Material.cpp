//
// Created by maxin on 04/12/2025.
//

#include "Material.h"
#include "../../interface/logger.h"

namespace Mocha {
    Material::Material(const Shader* materialShader)
    {
        shader = materialShader;
    }

    Material::Material()
        : shader(getDefaultShader())
    {
    }

    const Shader *Material::getDefaultShader()
    {
        static const Shader defaultShader;
        return &defaultShader;
    }

    Material::~Material() = default;

    void Material::addTexture(const Texture& texture)
    {
        textures.push_back(texture);
    }

    void Material::Use() const
    {
        shader->use();
        logger::logDebugFrame(("using material: " + m_name).c_str());

        // Naming convention for texture: [ texture_baseColour_N ] where N = number of textures
        // For material in shaders: [ material.texture_baseColour_N ]

        // Assume defaults
        unsigned int baseColourCount = 1;
        unsigned int normalCount = 0;
        unsigned int specularCount = 0;

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number; std::string textureType = textures[i].type; std::string name = textures[i].name;

            if      (textureType == "texture_baseColour_") number = std::to_string(baseColourCount++);
            else if (textureType == "texture_normal_")      number = std::to_string(normalCount++);
            else if (textureType == "texture_specular_")    number = std::to_string(specularCount++);

            shader->setInt(std::string ("material." + textureType + number), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].textureID);

            logger::logDebugFrame(std::string ("using texture: " + name + textureType + " N=" + number));
            logger::logDebugFrame(std::string ("shader.setInt: [material." + textureType + number + "] at " + std::to_string(i)));
        }
        glActiveTexture(GL_TEXTURE0);
    }
} // Mocha