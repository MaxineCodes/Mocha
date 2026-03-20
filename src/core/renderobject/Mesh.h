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
        glm::vec3 position;                         // pos 0
        glm::vec3 normal;                           // pos 1
        glm::vec2 texCoords;                        // pos 2
        glm::vec4 colour = glm::vec4(1.0f);   // pos 3
    };

    class Mesh
    {
    private:
        static Material* getDefaultMaterial();

    public:
        std::vector<Vertex> vertices;
        std::vector<unsigned int> indices;
        Material* m_material;

        Mesh(const std::vector<Vertex> &vertices,
            const std::vector<unsigned int> &indices,
            Material &material)
        : vertices(vertices),
          indices(indices),
          m_material(&material)
        {
            initializeMesh();
        }

        Mesh(const std::vector<Vertex> &vertices,
            const std::vector<unsigned int> &indices)
        : vertices(vertices),
          indices(indices)
        {
            m_material = getDefaultMaterial();
            initializeMesh();
        }

        void CleanUp();
        void Draw();
        void AssignMaterial(Material &material);

    private:
        GLuint VAO, VBO, EBO;
        void initializeMesh();


    };
} // Mocha

#endif //MOCHA_MESH_H