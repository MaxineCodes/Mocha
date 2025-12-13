//
// Created by maxin on 13/12/2025.
//

#ifndef MOCHA_OBJECT_H
#define MOCHA_OBJECT_H
#include "glm/vec3.hpp"

namespace Mocha
{
    class Object
    {
    public:
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 scale    = glm::vec3(1.0f, 1.0f, 1.0f);
    };
} // Mocha

#endif //MOCHA_OBJECT_H