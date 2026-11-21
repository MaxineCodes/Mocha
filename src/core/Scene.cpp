//
// Created by maxin on 02/12/2025.
//

#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time

#include "Scene.h"

#include "../interface/logger.h"

namespace Mocha
{
    Scene::Scene()
    {
        initialiseLights();
    }

    Scene Scene::DebugScene()
    {
        Scene debugScene;

        debugScene.skyColor = glm::vec4(0.6f, 0.7f, 0.8f, 1.0f); // gentle blue like the sky
        //debugScene.skyColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // Black

        // Create Shaders
        Shader* unlitShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/unlitFragmentShader.glsl"
            );
        debugScene.setShader("unlit", unlitShader);

        Shader* defaultShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/defaultFragmentShader.glsl"
            );
        debugScene.setShader("default", defaultShader);

        Shader* litShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/litFragmentShader.glsl"
        );
        debugScene.setShader("lit", litShader);

        // Create Textures
        Texture* brickTexture = new Texture("res/textures/stylizedBricks_diffuse.png");
        debugScene.setTexture("stylizedBricks_diffuse", brickTexture);
        Texture* cobblestoneTexture = new Texture("res/textures/cobblestone_diffuse.png");
        debugScene.setTexture("cobblestone_diffuse", cobblestoneTexture);
        Texture* minecraftFoxTexture = new Texture("res/textures/minecraftFox_diffuse.png");
        debugScene.setTexture("minecraftFox_diffuse", minecraftFoxTexture);
        Texture* minecraftSnowFoxTexture = new Texture("res/textures/minecraftSnowFox_diffuse.png");
        debugScene.setTexture("minecraftSnowFox_diffuse", minecraftSnowFoxTexture);
        Texture* orithTexture = new Texture("res/textures/orith_diffuse.png");
        debugScene.setTexture("orith_diffuse", orithTexture);
        Texture* specularTexture = new Texture("res/textures/test_specular.jpg");
        debugScene.setTexture("specular", specularTexture);

        // Create Materials
        Material* minecraftFoxMaterial = new Material(litShader);
        minecraftFoxMaterial->name = "minecraftFoxMaterial";
        minecraftFoxMaterial->setDiffuseTexture(&*minecraftSnowFoxTexture);
        minecraftFoxMaterial->setSpecularTexture(&*specularTexture);
        debugScene.setMaterial("mc fox", minecraftFoxMaterial);

        Material* bricksMaterial = new Material(litShader);
        bricksMaterial->name = "bricksMaterial";
        bricksMaterial->setDiffuseTexture(&*brickTexture);
        bricksMaterial->setSpecularTexture(&*specularTexture); // TODO: FIX BUG where specular is assigned to all materials
        debugScene.setMaterial("stylized bricks", bricksMaterial);

        Material* defaultMaterial = new Material(litShader);
        defaultMaterial->name = "defaultMaterial";
        debugScene.setMaterial("default", defaultMaterial);

        Material* cuteFoxMaterial = new Material(litShader);
        cuteFoxMaterial->name = "cuteFoxMaterial";
        //cuteFoxMaterial->setDiffuseTexture(&*blankTexture);
        debugScene.setMaterial("cute fox", cuteFoxMaterial);

        Material* orithMaterial = new Material(litShader);
        orithMaterial->name = "orithMaterial";
        orithMaterial->setDiffuseTexture(&*orithTexture);
        //orithMaterial->setSpecularTexture(&*specularTexture);
        debugScene.setMaterial("orith", orithMaterial);

        // Create RenderObjects
        RenderObject* myGloriousCube = new RenderObject("res/models/cube.obj");
        myGloriousCube->assignMaterial(*bricksMaterial);
        debugScene.setRenderObject("glorious cube", myGloriousCube);

        RenderObject* utahTeapot = new RenderObject("res/models/utah_teapot.obj");
        utahTeapot->assignMaterial(*defaultMaterial);
        debugScene.setRenderObject("utah teapot", utahTeapot);

        //RenderObject* stanfordDragon = new RenderObject("res/models/stanford_dragon.obj");
        //stanfordDragon->assignMaterial(cuteFoxMaterial);
        //debugScene.addRenderObject(stanfordDragon);
        RenderObject* orith = new RenderObject("res/models/orith.obj");
        orith->assignMaterial(*orithMaterial);
        debugScene.setRenderObject("orith", orith);

        RenderObject* minecraftFox = new RenderObject("res/models/minecraft_fox.obj");
        minecraftFox->assignMaterial(*minecraftFoxMaterial);
        debugScene.setRenderObject("fox from minecraft", minecraftFox);

        RenderObject* cuteFox = new RenderObject("res/models/cute_fox.obj");
        cuteFox->assignMaterial(*cuteFoxMaterial);
        debugScene.setRenderObject("cutefox", cuteFox);

        // Transformations
        cuteFox->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
        cuteFox->transform.position = glm::vec3(4.0f, 0.0f, 0.0f);
        //cuteFox->transform.rotation = glm::vec3(0.0f, 3.0f, 0.0f);

        minecraftFox->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
        minecraftFox->transform.position = glm::vec3(2.0f, 0.0f, 0.0f);
        //minecraftFox->transform.rotation = glm::vec3(0.0f, 0.0f, 1.5f);

        myGloriousCube->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
        myGloriousCube->transform.position = glm::vec3(-2.0f, 0.0f, 0.0f);

        //stanfordDragon->transform.scale = glm::vec3(0.01f, 0.01f, 0.01f);
        //stanfordDragon->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
        //stanfordDragon->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

        orith->transform.scale = glm::vec3(10.0f, 10.0f, 10.0f);

        utahTeapot->transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);
        utahTeapot->transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        //utahTeapot->transform.rotation = glm::vec3(45.0f, 45.0f, 45.0f);


        // Lights
        /*
        // Light values
        litShader->setVec3("pointLights[0].ambient",  0.2f, 0.2f, 0.2f);
        litShader->setVec3("pointLights[0].diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        litShader->setVec3("pointLights[0].specular", 1.0f, 1.0f, 1.0f);
        // Material values
        //litShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        //litShader->setFloat("material.shininess", 32.0f);
        litShader->setVec3("pointLights[0].position", lightPosition);
        */

        //debugScene.directionalLights["directionalLight_0"]->diffuse = glm::vec3(0.5f, 0.5f, 0.5f);
        //debugScene.directionalLights["directionalLight_0"]->ambient = glm::vec3(0.5f, 0.5f, 0.5f);
        glm::vec3 lightPosition = glm::vec3(0.0f, 5.0f, 5.0f);
        debugScene.pointLights["pointLight_0"]->position = lightPosition;
        debugScene.pointLights["pointLight_0"]->diffuse  = glm::vec3(0.8f, 0.8f, 0.8f);
        debugScene.pointLights["pointLight_0"]->ambient  = glm::vec3(0.2f, 0.2f, 0.2f);
        debugScene.pointLights["pointLight_0"]->specular = glm::vec3(1.0f, 1.0f, 1.0f);

        lightPosition = glm::vec3(5.0f, 5.0f, -5.0f);
        debugScene.pointLights["pointLight_1"]->position = lightPosition;
        debugScene.pointLights["pointLight_1"]->diffuse  = glm::vec3(0.0f, 1.0f, 1.0f);
        debugScene.pointLights["pointLight_1"]->ambient  = glm::vec3(0.0f, 0.0f, 0.0f);
        debugScene.pointLights["pointLight_1"]->specular = glm::vec3(1.0f, 1.0f, 1.0f);


        // Create light spheres
        for (unsigned int i = 0; i < debugScene.pointLights.size(); i++) {
            const std::string lightName = "pointLight_" + std::to_string(i);
            debugScene.spawnLightSphere(debugScene.pointLights[lightName]->position,
                                  debugScene.pointLights[lightName]->ambient);
        }








        return debugScene;
    }

    Scene Scene::spatialGridScene()
    {
        Scene scene;

        scene.skyColor = glm::vec4(0.6f, 0.7f, 0.8f, 1.0f); // gentle blue like the sky

        // Shader
        Shader* simpleShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/unlitFragmentShader.glsl"
            );
        scene.setShader("simpleShader", simpleShader);

        // Textures
        Texture* brickTexture      = new Texture("res/textures/stylizedBricks_diffuse.png");
        Texture* cobblestoneTexture= new Texture("res/textures/cobblestone_diffuse.png");
        scene.setTexture("stylized brick", brickTexture);
        scene.setTexture("cobblestone", cobblestoneTexture);

        // Materials
        Material* brickMaterial = new Material(simpleShader);
        brickMaterial->name = "brickMaterial";
        brickMaterial->setDiffuseTexture(&*brickTexture);
        scene.setMaterial("stylized bricks", brickMaterial);

        Material* cobbleMaterial = new Material(simpleShader);
        cobbleMaterial->name = "cobbleMaterial";
        cobbleMaterial->setDiffuseTexture(&*cobblestoneTexture);
        scene.setMaterial("cobblestone", cobbleMaterial);

        Material* variants[2] = { brickMaterial, cobbleMaterial};

        // 3D grid parameters
        const int   gridSize  = 5;
        const float spacing  = 1.5f;
        const glm::vec3 origin(-2.5f, -2.5f, -7.5f);

        // Seed once outside the loop
        std::srand(static_cast<unsigned>(std::time(nullptr)));

        // Loop to place random cubes
        for (int x = 0; x < gridSize; x++)
        {
            for (int y = 0; y < gridSize; y++)
            {
                for (int z = 0; z < gridSize; z++)
                {
                    RenderObject* cube = new RenderObject("res/models/cube.obj");

                    Material* randomMaterial = variants[std::rand() % 2];
                    cube->assignMaterial(*randomMaterial);

                    cube->transform.scale    = glm::vec3(0.5f, 0.5f, 0.5f); // half-spacing so cubes don't touch
                    cube->transform.position = origin +
                        glm::vec3(static_cast<float>(x),
                                  static_cast<float>(y),
                                  static_cast<float>(z)) * spacing;
                    scene.createRenderObject("cube", cube);
                }
            }
        }

        return scene;
    }

    Scene Scene::orithScene()
    {
        Scene scene;

        scene.skyColor = glm::vec4(0.12f, 0.1f, 0.12f, 1.0f); // purple

        // Create Shaders
        Shader* simpleShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/unlitFragmentShader.glsl"
            );
        scene.setShader("simple shader", simpleShader);

        // Create Textures
        Texture* orithTexture = new Texture("res/textures/orith_diffuse.png");
        scene.setTexture("orith diffuse", orithTexture);

        // Create Materials
        Material* orithMaterial = new Material(simpleShader);
        orithMaterial->assignTexture(*orithTexture, DIFFUSE);
        scene.setMaterial("orith", orithMaterial);

        // Create RenderObjects
        RenderObject* orith = new RenderObject("res/models/orith.obj");
        orith->assignMaterial(*orithMaterial);
        scene.setRenderObject("orith", orith);

        // Transformations
        orith->transform.scale = glm::vec3(15.0f, 15.0f, 15.0f);

        return scene;
    }

    void Scene::assignTextureToMaterial(const std::string& textureName, const std::string& materialName, const TEXTURE_TYPE textureType)
    {
        const Texture* texture = this->getTexture(textureName);
        Material* material = this->getMaterial(materialName);
        material->assignTexture(*texture, textureType);
    }
    void Scene::assignTextureToMaterial(const char* textureName, const char* materialName, const TEXTURE_TYPE textureType)
    { assignTextureToMaterial(std::string(textureName), std::string(materialName), textureType); }

    void Scene::assignMaterialToRenderObject(const std::string& materialName, const std::string& renderObjectName)
    {
        Material* material = this->getMaterial(materialName);
        RenderObject* renderObject = this->getRenderObject(renderObjectName);
        renderObject->assignMaterial(*material);
    }
    void Scene::assignMaterialToRenderObject(const char* materialName, const char* renderObjectName)
    { assignMaterialToRenderObject(std::string(materialName), std::string(renderObjectName)); }

    void Scene::createShader(const std::string &name, Shader* shader)
    {
        const std::string finalName = getAvailableName(name, shaders);
        shaders[finalName] = shader;
        if (shader->name == "") shader->name = name;
        if (finalName != name)
            logger::logWarn("Scene::createShader: '" + name + "' taken, created '" + finalName + "'.");
        else
            logger::logInfo("Scene::createShader: '" + name + "' created.");
    }
    void Scene::setShader(const std::string& name, Shader* shader)
    {
        if (!shaders.count(name))
        {
            logger::logError("Scene::setShader: '" + name + "' doesn't exist.");
            createShader(name, shader);
            return;
        }
        shaders.at(name) = shader;
        logger::logInfo("Scene::setShader: '" + name + "' updated.");
    }
    const Shader*  Scene::getShader(const std::string &name) const
    {
        if (!shaders.count(name))
        {
            logger::logError("Scene::getShader: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return shaders.at(name);
    }

    void Scene::createTexture(const std::string& name, Texture* texture)
    {
        const std::string finalName = getAvailableName(name, textures);
        textures[finalName] = texture;
        if (texture->name == "") texture->name = name;
        logger::logInfo("Scene::createTexture: '" + finalName + "' created.");
    }
    void Scene::setTexture(const std::string& name, Texture* texture)
    {
        if (!textures.count(name))
        {
            logger::logError("Scene::setTexture: '" + name + "' doesn't exist.");
            createTexture(name, texture);
            return;
        }
        textures.at(name) = texture;
    }
    const Texture* Scene::getTexture(const std::string& name) const
    {
        if (!textures.count(name))
        {
            logger::logError("Scene::getTexture: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return textures.at(name);
    }
    void Scene::createMaterial(const std::string& name, Material* material)
    {
        const std::string finalName = getAvailableName(name, materials);
        materials[finalName] = material;
        if (material->name == "") material->name = name;
        logger::logInfo("Scene::createMaterial: '" + finalName + "' created.");
    }
    void Scene::setMaterial(const std::string& name, Material* material)
    {
        if (!materials.count(name))
        {
            logger::logError("Scene::setMaterial: '" + name + "' doesn't exist.");
            createMaterial(name, material);
            return;
        }
        materials.at(name) = material;
    }
    Material* Scene::getMaterial(const std::string& name) const
    {
        if (!materials.count(name))
        {
            logger::logError("Scene::getMaterial: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return materials.at(name);
    }
    void Scene::createRenderObject(const std::string& name, RenderObject* renderObject)
    {
        const std::string finalName = getAvailableName(name, renderObjects);
        renderObjects[finalName] = renderObject;
        if (renderObject->name == "") renderObject->name = name;
        logger::logInfo("Scene::createRenderObject: '" + finalName + "' created.");
    }
    void Scene::setRenderObject(const std::string& name, RenderObject* renderObject)
    {
        if (!renderObjects.count(name))
        {
            logger::logError("Scene::setRenderObject: '" + name + "' doesn't exist.");
            createRenderObject(name, renderObject);
            return;
        }
        renderObjects.at(name) = renderObject;
    }
    RenderObject* Scene::getRenderObject(const std::string& name) const
    {
        if (!renderObjects.count(name))
        {
            logger::logError("Scene::getRenderObject: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return renderObjects.at(name);
    }
    void Scene::createCamera(const std::string& name, Camera* camera)
    {
        const std::string finalName = getAvailableName(name, cameras);
        cameras[finalName] = camera;
        if (camera->name == "") camera->name = name;
        logger::logInfo("Scene::createCamera: '" + finalName + "' created.");
    }
    void Scene::setCamera(const std::string& name, Camera* camera)
    {
        if (!cameras.count(name))
        {
            logger::logError("Scene::setCamera: '" + name + "' doesn't exist.");
            createCamera(name, camera);
            return;
        }
        cameras.at(name) = camera;
    }
    Camera* Scene::getCamera(const std::string& name) const
    {
        if (!cameras.count(name))
        {
            logger::logError("Scene::getCamera: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return cameras.at(name);
    }
    void Scene::createDirectionalLight(const std::string& name, Light::DirectionalLight* light)
    {
        const std::string finalName = getAvailableName(name, directionalLights);
        directionalLights[finalName] = light;
        if (light->name == "") light->name = name;
        logger::logInfo("Scene::createDirectionalLight: '" + finalName + "' created.");
    }
    void Scene::setDirectionalLight(const std::string& name, Light::DirectionalLight* light)
    {
        if (!directionalLights.count(name))
        {
            logger::logError("Scene::setDirectionalLight: '" + name + "' doesn't exist.");
            createDirectionalLight(name, light);
            return;
        }
        directionalLights.at(name) = light;
    }
    Light::DirectionalLight* Scene::getDirectionalLight(const std::string& name) const
    {
        if (!directionalLights.count(name))
        {
            logger::logError("Scene::getDirectionalLight: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return directionalLights.at(name);
    }
    void Scene::createPointLight(const std::string& name, Light::PointLight* light)
    {
        const std::string finalName = getAvailableName(name, pointLights);
        pointLights[finalName] = light;
        if (light->name == "") light->name = name;
        logger::logInfo("Scene::createPointLight: '" + finalName + "' created.");
    }
    void Scene::setPointLight(const std::string& name, Light::PointLight* light)
    {
        if (!pointLights.count(name))
        {
            logger::logError("Scene::setPointLight: '" + name + "' doesn't exist.");
            createPointLight(name, light);
            return;
        }
        pointLights.at(name) = light;
    }
    Light::PointLight* Scene::getPointLight(const std::string& name) const
    {
        if (!pointLights.count(name))
        {
            logger::logError("Scene::getPointLight: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return pointLights.at(name);
    }
    void Scene::createSpotLight(const std::string& name, Light::SpotLight* light)
    {
        const std::string finalName = getAvailableName(name, spotLights);
        spotLights[finalName] = light;
        if (light->name == "") light->name = name;
        logger::logInfo("Scene::createSpotLight: '" + finalName + "' created.");
    }
    void Scene::setSpotLight(const std::string& name, Light::SpotLight* light)
    {
        if (!spotLights.count(name))
        {
            logger::logError("Scene::setSpotLight: '" + name + "' doesn't exist.");
            createSpotLight(name, light);
            return;
        }
        spotLights.at(name) = light;
    }
    Light::SpotLight* Scene::getSpotLight(const std::string& name) const
    {
        if (!spotLights.count(name))
        {
            logger::logError("Scene::getSpotLight: '" + name + "' doesn't exist.");
            return nullptr;
        }
        return spotLights.at(name);
    }


    int Scene::getRenderObjectCount() const
    {
        return renderObjects.size();
    }

    void Scene::initialiseLights()
    {
        for (unsigned int i = 0; i < Light::NUMBER_OF_DIRECTIONAL_LIGHTS; i++)
        {
            const std::string lightName = "directionalLight_" + std::to_string(i);
            directionalLights[lightName] = new Light::DirectionalLight();
            logger::logInfo("Created light: " + lightName);
        }
        for (unsigned int i = 0; i < Light::NUMBER_OF_POINT_LIGHTS; i++)
        {
            const std::string lightName = "pointLight_" + std::to_string(i);
            pointLights[lightName] = new Light::PointLight();
            logger::logInfo("Created light: " + lightName);
        }
        for (unsigned int i = 0; i < Light::NUMBER_OF_SPOT_LIGHTS; i++)
        {
            const std::string lightName = "spotLight_" + std::to_string(i);
            spotLights[lightName] = new Light::SpotLight();
            logger::logInfo("Created light: " + lightName);
        }
    }

    void Scene::loadDirectionalLight(const Shader* shader, const uint index)
    {
        const std::string lightName = "directionalLight_" + std::to_string(index);
        const std::string prefix = "directionalLight[" + std::to_string(index) + "]";

        // Light base class uniforms
        shader->setVec3(lightName + ".position",     directionalLights[lightName]->position);
        shader->setVec3(lightName + ".direction",    directionalLights[lightName]->direction);
        shader->setVec3(lightName + ".ambient",      directionalLights[lightName]->ambient);
        shader->setVec3(lightName + ".diffuse",      directionalLights[lightName]->diffuse);
        shader->setVec3(lightName + ".specular",     directionalLights[lightName]->specular);
    }
    void Scene::loadPointLight(const Shader* shader, const uint index)
    {
        const std::string lightName = "pointLight_" + std::to_string(index);
        const std::string prefix = "pointLights[" + std::to_string(index) + "]";

        // Light base class uniforms
        shader->setVec3(prefix + ".position",     pointLights[lightName]->position);
        shader->setVec3(prefix + ".direction",    pointLights[lightName]->direction);
        shader->setVec3(prefix + ".ambient",      pointLights[lightName]->ambient);
        shader->setVec3(prefix + ".diffuse",      pointLights[lightName]->diffuse);
        shader->setVec3(prefix + ".specular",     pointLights[lightName]->specular);
        // PointLight unique uniforms
        shader->setFloat(prefix + ".constant",    pointLights[lightName]->constant);
        shader->setFloat(prefix + ".linear",      pointLights[lightName]->linear);
        shader->setFloat(prefix + ".quadratic",   pointLights[lightName]->quadratic);
    }
    void Scene::loadSpotLight(const Shader* shader, const uint index)
    {
        const std::string lightName = "spotLight_" + std::to_string(index);
        const std::string prefix = "spotLight[" + std::to_string(index) + "]";

        // Light base class uniforms
        shader->setVec3(lightName + ".position",     spotLights[lightName]->position);
        shader->setVec3(lightName + ".direction",    spotLights[lightName]->direction);
        shader->setVec3(lightName + ".ambient",      spotLights[lightName]->ambient);
        shader->setVec3(lightName + ".diffuse",      spotLights[lightName]->diffuse);
        shader->setVec3(lightName + ".specular",     spotLights[lightName]->specular);
    }

    void Scene::loadLights(const Shader* shader)
    {
        logger::logInfo("Loaded lights to shader: " + shader->name);
        for (unsigned int i = 0; i < directionalLights.size(); i++)
            loadDirectionalLight(shader, i);
        for (unsigned int i = 0; i < pointLights.size(); i++)
            loadPointLight(shader, i);
        for (unsigned int i = 0; i < spotLights.size(); i++)
            loadSpotLight(shader, i);
    }
    void Scene::loadLights()
    {
        logger::logInfo("Scene::loadLights called for all shaders.");
        for (auto& [name, shader] : shaders)
            loadLights(shader);
    }


    void Scene::spawnLightSphere(const glm::vec3& position, const glm::vec3& colour)
    {
        // If no lightMaterial in materials
        if (materials.find("lightMaterial") == materials.end())
        {
            Shader* lightShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/lightFragmentShader.glsl");
            createShader("lightshader", lightShader);
            Material* lightMaterial = new Material(lightShader);
            lightMaterial->name = "lightMaterial";
            createMaterial("lightMaterial", lightMaterial);
        }

        RenderObject* lightSphere = new RenderObject("res/models/icosphere.obj");
        Material* lightMaterial = materials["lightMaterial"];
        lightSphere->assignMaterial(*lightMaterial);
        std::string name = "lightSphere_"
                           + std::to_string(position.x)
                           + "_" + std::to_string(position.y)
                           + "_" + std::to_string(position.z);
        if (renderObjects.find(name) == renderObjects.end()) setRenderObject(name, lightSphere);
        else setRenderObject(name + "_DUPLICATE", lightSphere);

        lightSphere->transform.scale    = glm::vec3(0.1f, 0.1f, 0.1f);
        lightSphere->transform.position = position;
    }

}
