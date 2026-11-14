//
// Created by maxin on 02/12/2025.
//

#ifndef MOCHA_SCENE_H
#define MOCHA_SCENE_H

#include <vector>

#include "camera/Camera.h"
#include "renderobject/RenderObject.h"
#include "renderobject/Texture.h"

namespace Mocha
{
    class Scene
    {
    public:
        Scene() = default;

        // Create a debug scene with random dev testing stuff :)
        static Scene DebugScene();

    public:
        std::vector<RenderObject*> renderObjects; // mutatable
        std::vector<const Material*> materials;
        std::vector<const Texture*> textures;
        std::vector<const Shader*> shaders;
        // vector camera(s)
        // vector lights

    public:
        void addRenderObject(RenderObject* renderObject) { renderObjects.push_back(renderObject); }
        void addMaterial(const Material* material)       { materials.push_back(material); }
        void addTexture(const Texture* texture)          { textures.push_back(texture); }
        void addShader(const Shader* shader)             { shaders.push_back(shader); }

        void addCamera(); // Unimplemented
        void addLight(); // Unimplemented

        int getRenderObjectCount();
    };

}
#endif //MOCHA_SCENE_H