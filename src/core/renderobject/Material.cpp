//
// Created by maxin on 04/12/2025.
//

#include "Material.h"
#include "../../interface/logger.h"

namespace Mocha {
    Material::Material() : shader()
    {

    }

    Material::~Material()
    {

    }

    void Material::Use()
    {
        logger::logDebug(("using material: " + name).c_str());

        // Naming convention for texture: [ texture_baseColour_N ] where N = number of textures
        // For material in shaders: [ material.texture_baseColour_N ]

        // Assume defaults
        unsigned int baseColourCount = 1;
        unsigned int normalCount = 0;
        unsigned int specularCount = 0;

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number; std::string textureName = textures[i].type;

            if      (textureName == "texture_baseColour_") number = std::to_string(baseColourCount++);
            else if (textureName == "texture_normal_")      number = std::to_string(normalCount++);
            else if (textureName == "texture_specular_")    number = std::to_string(specularCount++);

            shader.setInt(std::string ("material." + textureName + number), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].textureID);

            logger::logDebug(std::string ("using texture: " + textureName + " N=" + number));
            logger::logDebug(std::string ("shader.setInt: [material." + textureName + number + "] at " + std::to_string(i)));
        }
        glActiveTexture(GL_TEXTURE0);
    }
} // Mocha