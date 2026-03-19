//
// Created by maxin on 04/12/2025.
//

#include "RenderObject.h"
#include "../../interface/logger.h"
#include "../importing/modelImporting.h"

namespace Mocha
{
    RenderObject::RenderObject(const char* path)
    {
        loadModel(path);
    }



    void RenderObject::draw()
    {
        // Nothing fancy, just draw every mesh
        for (unsigned int i = 0; i < meshes.size(); i++)
        {
            meshes[i].Draw();
        }
    }

    void RenderObject::loadModel(std::string path)
    {
        meshes = importModel(std::string(path));
    }
} // Mocha