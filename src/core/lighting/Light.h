//
// Created by maxin on 13/12/2025.
//

#ifndef MOCHA_LIGHT_H
#define MOCHA_LIGHT_H

#include "../Object.h"

namespace Mocha
{
    namespace Light
    {
        // 8 + 16 + 8 = 32 lights total
        constexpr int NUMBER_OF_DIRECTIONAL_LIGHTS = 8;
        constexpr int NUMBER_OF_POINT_LIGHTS = 16;
        constexpr int NUMBER_OF_SPOT_LIGHTS = 8;

        enum TYPE {NONE, DIRECTIONAL_LIGHT, POINT_LIGHT, SPOT_LIGHT};

        struct Light : public Object
        {
            glm::vec3 position      = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 direction     = glm::vec3(0.0f, -1.0f, 0.0f);
            //glm::vec3 colour        = glm::vec3(0.0f, 0.0f, 0.0f);
            glm::vec3 ambient       = glm::vec3(0.1f, 0.1f, 0.1f);
            glm::vec3 diffuse       = glm::vec3(0.5f, 0.5f, 0.5f);
            glm::vec3 specular      = glm::vec3(1.0f, 1.0f, 1.0f);

            static TYPE getType() { return NONE; }
        };

        struct DirectionalLight : public Light
        {
            static TYPE getType() { return DIRECTIONAL_LIGHT; }
        };

        struct PointLight : public Light
        {
            float constant = 1.0f, linear = 0.09f, quadratic = 0.032f;
            static TYPE getType() { return POINT_LIGHT; }
        };

        struct SpotLight : public Light
        {
            static TYPE getType() { return SPOT_LIGHT; }
        };

    } // Light
} // Mocha

#endif //MOCHA_LIGHT_H