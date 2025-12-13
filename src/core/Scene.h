//
// Created by maxin on 02/12/2025.
//

#ifndef MOCHA_SCENE_H
#define MOCHA_SCENE_H

#include <vector>
#include "renderobject/RenderObject.h"
#include "renderobject/Texture.h"

namespace Mocha
{
    class Scene
    {
    public:
        Scene() = default;

        void addRenderObject(RenderObject renderObject);
        void addMaterial(Material material);
        void addTexture(Texture texture);

        void addCamera(); // Unimplemented
        void addLight(); // Unimplemented


    private:
        std::vector<RenderObject> renderObjects;
        std::vector<Material> materials;
        std::vector<Texture> textures;
        // vector camera(s)
        // vector lights


    };

}
#endif //MOCHA_SCENE_H