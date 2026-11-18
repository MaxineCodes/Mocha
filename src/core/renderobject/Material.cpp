//
// Created by maxin on 04/12/2025.
//

#include "Material.h"
#include "../../interface/logger.h"

namespace Mocha {
    Material::Material(const Shader* materialShader)
    {
        shader = materialShader;
        colour = glm::vec3(1.0f, 1.0f, 1.0f); // Default colour to white
        ambient = glm::vec3(0.1f, 0.1f, 0.1f); // Default a little bit ambient
        shininess = 3.0f; // Default shininess available
    }

    Material::Material()
        : shader(getDefaultShader())
    {
        colour = glm::vec3(1.0f, 1.0f, 1.0f); // Default colour to white
        ambient = glm::vec3(0.1f, 0.1f, 0.1f); // Default a little bit ambient
        shininess = 3.0f; // Default shininess available
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

        shader->setVec3("material.colour", colour);
        shader->setVec3("material.ambient", ambient);
        shader->setFloat("material.shininess", shininess);

        for (unsigned int i = 0; i < textures.size(); i++)
        {
            glActiveTexture(GL_TEXTURE0 + i);
            std::string number; std::string textureType = textures[i].type; std::string name = textures[i].name;

            if      (textureType == "diffuse")      shader->setInt("material.diffuse", i);
            else if (textureType == "normal")       shader->setInt("material.normal", i);
            else if (textureType == "specular")     shader->setInt("material.specular", i);
            else logger::logError("Material '" + m_name + "': unknown texture type '" + textureType + "' for texture '" + name + "'");

            //shader->setInt(std::string ("material." + textureType), i);
            glBindTexture(GL_TEXTURE_2D, textures[i].textureID);

            logger::logDebugFrame(std::string ("using texture: " + name + "." + textureType));
            logger::logDebugFrame(std::string ("shader.setInt: [material." + textureType + "] at " + std::to_string(i)));
        }
        glActiveTexture(GL_TEXTURE0);
    }
} // Mocha