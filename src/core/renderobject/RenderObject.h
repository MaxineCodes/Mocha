//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_RENDEROBJECT_H
#define MOCHA_RENDEROBJECT_H
#include "Mesh.h"
#include "../Object.h"

#include <vector>

namespace Mocha
{
    class RenderObject : public Object
    {
    public:
        void draw();

    private:
        std::vector<Mesh> meshes;
        std::vector<Material> materials;

    };
} // Mocha

#endif //MOCHA_RENDEROBJECT_H