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

        // TODO: SET NAME TO MAP KEY AND SEPERATE 'ADD' FROM 'EDIT'
        // Setters + const char* overload
        void setShader          (const std::string& name, const Shader* shader) { shaders[name] = shader; }
        void setShader          (const char* name, const Shader* shader) { setShader(std::string(name), shader); }
        void setTexture         (const std::string& name, const Texture* texture) { textures[name] = texture; }
        void setTexture         (const char* name, const Texture* texture) { setTexture(std::string(name), texture); }
        void setMaterial        (const std::string& name, Material* material) { materials[name] = material; }
        void setMaterial        (const char* name, Material* material) { setMaterial(std::string(name), material); }
        void setRenderObject    (const std::string& name, RenderObject* renderObject) { renderObjects[name] = renderObject; }
        void setRenderObject    (const char* name, RenderObject* renderObject) { setRenderObject(std::string(name), renderObject); }
        void setCamera          (const std::string& name, Camera* camera) { cameras[name] = camera; }
        void setCamera          (const char* name, Camera* camera) { setCamera(std::string(name), camera); }
        void setActiveCamera    (const std::string& name) { m_activeCamera = name; }
        void setActiveCamera    (const char* name) { setActiveCamera(std::string(name)); }
        void setDirectionalLight(const std::string& name, Light::DirectionalLight* light) { directionalLights[name] = light; }
        void setDirectionalLight(const char* name, Light::DirectionalLight* light) { setDirectionalLight(std::string(name), light); }
        void setPointLight      (const std::string& name, Light::PointLight* light) { pointLights[name] = light; }
        void setPointLight      (const char* name, Light::PointLight* light) { setPointLight(std::string(name), light); }
        void setSpotLight       (const std::string& name, Light::SpotLight* light) { spotLights[name] = light; }
        void setSpotLight(      const char* name, Light::SpotLight* light) { setSpotLight(std::string(name), light); }

        // Getters + const char* overload
        const Shader* getShader(const std::string& name) { return shaders[name]; }
        const Shader* getShader(const char* name) { return getShader(std::string(name)); }
        const Texture* getTexture(const std::string& name) { return textures[name]; }
        const Texture* getTexture(const char* name) { return getTexture(std::string(name)); }
        Material* getMaterial(const std::string& name) { return materials[name]; }
        Material* getMaterial(const char* name) { return getMaterial(std::string(name)); }
        RenderObject* getRenderObject(const std::string& name) { return renderObjects[name]; }
        RenderObject* getRenderObject(const char* name) { return getRenderObject(std::string(name)); }
        Camera* getCamera(const std::string& name) { return cameras[name]; }
        Camera* getCamera(const char* name) { return getCamera(std::string(name)); }
        Camera* getActiveCamera() { return getCamera(m_activeCamera); }
        Light::DirectionalLight* getDirectionalLight(const std::string& name) { return directionalLights[name]; }
        Light::DirectionalLight* getDirectionalLight(char* name) { return getDirectionalLight(std::string(name)); }
        Light::PointLight* getPointLight(const std::string& name) { return pointLights[name]; }
        Light::PointLight* getPointLight(char* name) { return getPointLight(std::string(name)); }
        Light::SpotLight* getSpotLight(const std::string& name) { return spotLights[name]; }
        Light::SpotLight* getSpotLight(char* name) { return getSpotLight(std::string(name)); }

        // Other utility functions
        int getRenderObjectCount() const;
        void loadLights(const Shader *shader);
        void loadLights();

    private:
        void initialiseLights();
    };

}
#endif //MOCHA_SCENE_H