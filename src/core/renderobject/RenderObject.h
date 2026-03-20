//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_RENDEROBJECT_H
#define MOCHA_RENDEROBJECT_H
#include "Mesh.h"
#include "../Object.h"

#include <vector>

#include "assimp/scene.h"

namespace Mocha
{
    class RenderObject : public Object
    {
    private:
        const char* defaultObjectPath = "res/models/cube.obj";

    public:
        RenderObject(const char* path);
        RenderObject();
        void draw();
        // Assigns a material to all meshes belonging to this RenderObject
        void assignMaterial(Material* material);

    private:
        std::vector<Mesh> meshes;
        void loadModel(std::string path);
    };
} // Mocha

#endif //MOCHA_RENDEROBJECT_H