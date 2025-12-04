//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_RENDEROBJECT_H
#define MOCHA_RENDEROBJECT_H
#include "Mesh.h"

namespace Mocha
{
    class RenderObject
    {
    public:
        void draw();

    private:
        Mesh mesh;

    };
} // Mocha

#endif //MOCHA_RENDEROBJECT_H