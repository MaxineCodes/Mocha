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
    enum TEXTURE_TYPE {DIFFUSE, SPECULAR, EMISSION, NORMAL};

    class Material
    {
    public:
        std::string m_name = "material";
        const Shader *shader;

        /*
         *
         * Texture is paired with a vector3 value:
         *      The texture and value are either multiplied or added together
         *      within the shader code.
         * This allows for both to be used by the same material without requiring
         * shader-code generation and runtime re-compiling.
         *
         * MaterialX is not implemented: Mocha is supposed to be simple.
         *
         */

        //  Blinn-Phong
        glm::vec3 m_ambient = glm::vec3(0.1f, 0.1f, 0.1f);
        float m_shininess = 32.0f;
        const Texture* m_diffuseTexture = nullptr;      glm::vec3 m_diffuseValue = glm::vec3(1);
        const Texture* m_specularTexture = nullptr;     glm::vec3 m_specularValue = glm::vec3(0);
        const Texture* m_emissionTexture = nullptr;     glm::vec3 m_emissionValue = glm::vec3(0);
        const Texture* m_normalTexture = nullptr;       float m_normalIntensity;

        Material(const Shader* materialShader);
        Material();

        ~Material();

        //void addTexture(const Texture& texture);
        void name(const char* name) { this->m_name = name; }

        void assignTexture(const Texture& texture, TEXTURE_TYPE textureType);
        void setDiffuseTexture(Texture* texture) { m_diffuseTexture = texture; }
        void setSpecularTexture(Texture* texture) { m_specularTexture = texture; }
        void setEmissionTexture(Texture* texture) { m_emissionTexture = texture; }
        void setNormalTexture(Texture* texture) { m_normalTexture = texture; }

        void Use() const;

    private:
        static const Shader* getDefaultShader();
        void bindTexture(TEXTURE_TYPE textureType) const;
        static GLuint getFallbackTexture(TEXTURE_TYPE textureType);
    };
} // Mocha

#endif //MOCHA_MATERIAL_H