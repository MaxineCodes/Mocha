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

        class Light : public Object
        {
            glm::vec3 position, direction;
            glm::vec3 colour;
            glm::vec3 ambient, diffuse, specular;

            static TYPE getType() { return NONE; }
        };

        class DirectionalLight : public Light
        {
            static TYPE getType() { return DIRECTIONAL_LIGHT; }
        };

        class PointLight : public Light
        {
            float constant = 0, linear = 0, quadratic = 0;
            static TYPE getType() { return POINT_LIGHT; }
        };

        class SpotLight : public Light
        {
            static TYPE getType() { return SPOT_LIGHT; }
        };

    } // Light
} // Mocha

#endif //MOCHA_LIGHT_H