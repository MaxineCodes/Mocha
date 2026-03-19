//
// Created by maxin on 13/12/2025.
//

#ifndef MOCHA_OBJECT_H
#define MOCHA_OBJECT_H
#include "glm/vec3.hpp"
#include "glm/mat4x4.hpp"
#include <glm/gtc/matrix_transform.hpp>

namespace Mocha
{
    struct Transform
    {
        glm::vec3 position = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 rotation = glm::vec3(0.0f, 0.0f, 0.0f);
        glm::vec3 scale    = glm::vec3(1.0f, 1.0f, 1.0f);
    };

    class Object
    {
    public:
        Transform transform;
        glm::mat4 getModelMatrix() const
        {
            glm::mat4 model = glm::mat4(1.0f);
            model = glm::translate(model, transform.position);
            model = glm::rotate(model, glm::radians(transform.rotation.x), glm::vec3(1.0f, 0.0f, 0.0f));
            model = glm::rotate(model, glm::radians(transform.rotation.y), glm::vec3(0.0f, 1.0f, 0.0f));
            model = glm::rotate(model, glm::radians(transform.rotation.z), glm::vec3(0.0f, 0.0f, 1.0f));
            model = glm::scale(model, transform.scale);
            return model;
        }
    };
} // Mocha

#endif //MOCHA_OBJECT_H