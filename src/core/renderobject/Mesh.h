//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_MESH_H
#define MOCHA_MESH_H

#include "Material.h"

namespace Mocha
{
    struct Vertex
    {
        glm::vec3 position;
        glm::vec3 normal;
        glm::vec2 texCoords;
    };

    class Mesh
    {
    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Material material;

        Mesh(const std::vector<Vertex> &vertices,
            const std::vector<unsigned int> &indices,
            Material &material)
        : vertices(vertices),
          indices(indices),
          material(material)
        {
            initializeMesh();
        }

        void Draw();

    private:
        unsigned int VAO, VBO, EBO;
        void initializeMesh();


    };
} // Mocha

#endif //MOCHA_MESH_H