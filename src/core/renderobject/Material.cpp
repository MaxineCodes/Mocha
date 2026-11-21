//
// Created by maxin on 04/12/2025.
//

#include "Material.h"
#include "../../interface/logger.h"

namespace Mocha {
    Material::Material(const Shader* materialShader) { shader = materialShader;}
    Material::Material() : shader(getDefaultShader()) {}

    const Shader *Material::getDefaultShader()
    {
        static const Shader defaultShader;
        return &defaultShader;
    }

    Material::~Material() = default;

    void Material::assignTexture(const Texture &texture, TEXTURE_TYPE textureType)
    {
        switch (textureType)
        {
            case DIFFUSE:  m_diffuseTexture  = &texture; break;
            case SPECULAR: m_specularTexture = &texture; break;
            case EMISSION: m_emissionTexture = &texture; break;
            case NORMAL:   m_normalTexture   = &texture; break;
            default: logger::logError("Material::assignTexture: UNKNOWN TYPE: '" + name + "'");
        }
    }

    void Material::bindTexture(TEXTURE_TYPE textureType) const
    {
        const Texture* texture = nullptr;
        const char* uniformVariable = nullptr;

        switch (textureType)
        {
            case DIFFUSE:  texture = m_diffuseTexture;      uniformVariable = "material.diffuse"; break;
            case SPECULAR: texture = m_specularTexture;     uniformVariable = "material.specular"; break;
            case EMISSION : texture = m_emissionTexture;    uniformVariable = "material.emission"; break;
            case NORMAL:   texture = m_normalTexture;       uniformVariable = "material.normal"; break;
            default: logger::logError("Material " + name + ": unknown texture type." );
        }

        glActiveTexture(GL_TEXTURE0 + textureType);
        shader->setInt(uniformVariable, static_cast<int>(textureType));

        if (texture) glBindTexture(GL_TEXTURE_2D, texture->textureID);
        else
        {
            //logger::logError("Material::bindTexture on " + m_name + ": NULL texture: " + std::string(uniformVariable));
            glBindTexture(GL_TEXTURE_2D, getFallbackTexture(textureType) );
        }
    }

    void Material::Use() const
    {
        shader->use();
        logger::logDebugFrame(("using material: " + name).c_str());

        // Blinn-Phong
        shader->setVec3("material.ambient", m_ambient);
        shader->setFloat("material.shininess", m_shininess);
        shader->setVec3("material.diffuseValue", m_diffuseValue);
        shader->setVec3("material.specularValue", m_specularValue);
        shader->setVec3("material.emissionValue", m_emissionValue);
        shader->setFloat("material.normalIntensity", m_normalIntensity);

        bindTexture(DIFFUSE);
        bindTexture(SPECULAR);
        bindTexture(EMISSION);  // unused
        bindTexture(NORMAL);    // unused

        glActiveTexture(GL_TEXTURE0);
    }

    GLuint Material::getFallbackTexture(TEXTURE_TYPE textureType)
    {
        // One 1x1 white and one 1x1 black texture, created lazily on first use.
        static GLuint whiteTextureID   = 0;
        static GLuint blackTextureID   = 0;
        static GLuint magentaTextureID = 0;

        if (whiteTextureID == 0)
        {
            const unsigned char white   [3] = { 255, 255, 255 };
            const unsigned char black   [3] = {   0,   0,   0 };
            const unsigned char magenta [3] = { 255,   0, 255 };

            glGenTextures(1, &whiteTextureID);
            glBindTexture(GL_TEXTURE_2D, whiteTextureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, white);

            glGenTextures(1, &blackTextureID);
            glBindTexture(GL_TEXTURE_2D, blackTextureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, black);

            glGenTextures(1, &magentaTextureID);
            glBindTexture(GL_TEXTURE_2D, magentaTextureID);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
            glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, 1, 1, 0, GL_RGB, GL_UNSIGNED_BYTE, magenta);


            logger::logInfo("Created fallback textures (1x1 white/black)");

        }

        switch (textureType)
        {
            // White for multiplicative (value * 1.0 = value)
            // Black for additive (value + 0.0 = value)
            // Magenta to boldly show that something is wrong
            case DIFFUSE:   return whiteTextureID;
            case SPECULAR:  return whiteTextureID;
            case EMISSION:  return blackTextureID;
            default:        return blackTextureID;
        }
    }
} // Mocha