//
// Created by maxin on 02/12/2025.
//

#ifndef MOCHA_SCENE_H
#define MOCHA_SCENE_H

#include <map>
#include <vector>

#include "camera/Camera.h"
#include "lighting/Light.h"
#include "renderobject/RenderObject.h"
#include "renderobject/Texture.h"

namespace Mocha
{
    class Scene
    {
    public:
        Scene();

        // Create a debug scene with random dev testing stuff :)
        static Scene DebugScene();
        static Scene spatialGridScene(); // Generated stuff
        static Scene orithScene();

    public:
        glm::vec4 skyColor = glm::vec4(1.0f, 0.0f, 1.0f, 1.0f); // Debug-magenta as default

    public:
        // <name, type>
        // string name acts as ID, no int ID is used.
        std::map<std::string, const Shader*> shaders;
        std::map<std::string, const Texture*> textures;
        std::map<std::string, Material*> materials; // mutatable
        std::map<std::string, RenderObject*> renderObjects; // mutatable

        std::map<std::string, Camera*> cameras; // mutatable
        std::map<std::string, Light::DirectionalLight*> directionalLights; // mutatable
        std::map<std::string, Light::PointLight*> pointLights; // mutatable
        std::map<std::string, Light::SpotLight*> spotLights; // mutatable

    private:
        // Currently active camera variable is only used for getter/setter
        std::string m_activeCamera;

    public:
        void assignTextureToMaterial(const std::string& textureName, const std::string& materialName, TEXTURE_TYPE textureType);
        void assignTextureToMaterial(const char* textureName, const char* materialName, TEXTURE_TYPE textureType);
        void assignMaterialToRenderObject(const std::string& materialName, const std::string& renderObjectName);
        void assignMaterialToRenderObject(const char* materialName, const char* renderObjectName);

        // ----- GETTERS / SETTERS -----
        // Shader
        void createShader(const std::string& name, const Shader* shader);
        void setShader(const std::string& name, const Shader* shader);
        const Shader*  getShader(const std::string& name) const;
        // Texture
        void createTexture(const std::string& name, const Texture* texture);
        void setTexture(const std::string& name, const Texture* texture);
        const Texture* getTexture(const std::string& name) const;
        // Material
        void createMaterial(const std::string& name, Material* material);
        void setMaterial(const std::string& name, Material* material);
        Material* getMaterial(const std::string& name) const;
        // RenderObject
        void createRenderObject(const std::string& name, RenderObject* renderObject);
        void setRenderObject(const std::string& name, RenderObject* renderObject);
        RenderObject* getRenderObject(const std::string &name) const;
        // Camera
        void createCamera(const std::string& name, Camera* camera);
        void setCamera(const std::string& name, Camera* camera);
        Camera* getCamera(const std::string& name) const;
        // DirectionalLight
        void createDirectionalLight(const std::string& name, Light::DirectionalLight* light);
        void setDirectionalLight(const std::string& name, Light::DirectionalLight* light);
        Light::DirectionalLight* getDirectionalLight(const std::string& name) const;
        // PointLight
        void createPointLight(const std::string& name, Light::PointLight* light);
        void setPointLight(const std::string& name, Light::PointLight* light);
        Light::PointLight* getPointLight(const std::string& name) const;
        // SpotLight
        void createSpotLight(const std::string& name, Light::SpotLight* light);
        void setSpotLight(const std::string& name, Light::SpotLight* light);
        Light::SpotLight* getSpotLight(const std::string& name) const;
        // -----------------------------

        // Other utility functions
        int getRenderObjectCount() const;

        // Set the shader's light uniforms for every light.
        void loadLights(const Shader *shader);
        void loadLights(); // No arguments? Just do all of them.

    private:
        // Fill the lights maps to avoid NULLs
        void initialiseLights();

        // Set light uniforms to shader
        void loadDirectionalLight(const Shader *shader, uint index);
        void loadPointLight(const Shader *shader, uint index);
        void loadSpotLight(const Shader *shader, uint index);

        void spawnLightSphere(const glm::vec3 &position, const glm::vec3 &colour);

        // Recursively get a name that is available.
        // example: "cube" is taken? then "cube_1" < "cube_2" etc...
        template<typename Map>
        std::string getAvailableName(const std::string& name, const Map& mapStructure)
        {
            if (!mapStructure.count(name)) return name;
            std::string base = name;
            int suffix = 0;
            while (mapStructure.count(base + "_" + std::to_string(++suffix))) {}
            return base + "_" + std::to_string(suffix);
        }
    };
}
#endif //MOCHA_SCENE_H