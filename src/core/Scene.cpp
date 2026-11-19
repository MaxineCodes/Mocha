//
// Created by maxin on 02/12/2025.
//

#include <cstdlib>   // std::rand, std::srand
#include <ctime>     // std::time

#include "Scene.h"

namespace Mocha
{
    Scene Scene::DebugScene()
    {
        Scene debugScene;

        debugScene.skyColor = glm::vec4(0.6f, 0.7f, 0.8f, 1.0f); // gentle blue like the sky
        //debugScene.skyColor = glm::vec4(0.0f, 0.0f, 0.0f, 1.0f); // Black

        // Create Shaders
        Shader* unlitShader = new Shader(
            "res/shaders/unlitVertexShader.glsl",
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
        Texture* blankTexture = new Texture("res/textures/white_diffuse.png");
        debugScene.setTexture("white_diffuse", blankTexture);
        Texture* specularTexture = new Texture("res/textures/test_specular.jpg");
        debugScene.setTexture("specular", specularTexture);

        // Create Materials
        Material* minecraftFoxMaterial = new Material(litShader);
        minecraftFoxMaterial->name("minecraftFoxMaterial");
        minecraftFoxMaterial->setDiffuseTexture(&*minecraftSnowFoxTexture);
        minecraftFoxMaterial->setSpecularTexture(&*specularTexture);
        debugScene.setMaterial("mc fox", minecraftFoxMaterial);

        Material* bricksMaterial = new Material(litShader);
        bricksMaterial->name("bricksMaterial");
        bricksMaterial->setDiffuseTexture(&*brickTexture);
        bricksMaterial->setSpecularTexture(&*specularTexture); // TODO: FIX BUG where specular is assigned to all materials
        debugScene.setMaterial("stylized bricks", bricksMaterial);

        Material* defaultMaterial = new Material(litShader);
        defaultMaterial->name("defaultMaterial");
        debugScene.setMaterial("default", defaultMaterial);

        Material* cuteFoxMaterial = new Material(litShader);
        cuteFoxMaterial->name("cuteFoxMaterial");
        cuteFoxMaterial->setDiffuseTexture(&*blankTexture);
        debugScene.setMaterial("cute fox", cuteFoxMaterial);

        Material* orithMaterial = new Material(litShader);
        orithMaterial->name("orithMaterial");
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
        Shader* lightShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/lightFragmentShader.glsl");
        debugScene.setShader("lightshader", lightShader);
        Material* lightMaterial = new Material(lightShader);
        lightMaterial->name("lightMaterial");
        lightMaterial->setSpecularTexture(&*specularTexture);
        lightMaterial->setDiffuseTexture(&*specularTexture);

        debugScene.setMaterial("light", lightMaterial);
        RenderObject* lightSphere = new RenderObject("res/models/icosphere.obj");
        lightSphere->assignMaterial(*lightMaterial);
        debugScene.setRenderObject("lightsphere", lightSphere);
        lightSphere->transform.scale = glm::vec3(0.1f, 0.1f, 0.1f);

        // Light values
        litShader->setVec3("light.ambient",  0.2f, 0.2f, 0.2f);
        litShader->setVec3("light.diffuse",  0.5f, 0.5f, 0.5f); // darken diffuse light a bit
        litShader->setVec3("light.specular", 1.0f, 1.0f, 1.0f);
        // Material values
        //litShader->setVec3("material.ambient", 1.0f, 0.5f, 0.31f);
        //litShader->setFloat("material.shininess", 32.0f);

        glm::vec3 lightPosition = glm::vec3(0.0f, 5.0f, 5.0f);
        litShader->setVec3("light.position", lightPosition);
        lightSphere->transform.position = lightPosition;







        return debugScene;
    }

    Scene Scene::spatialGridScene()
    {
        Scene scene;

        scene.skyColor = glm::vec4(0.6f, 0.7f, 0.8f, 1.0f); // gentle blue like the sky

        // Shader
        Shader* simpleShader = new Shader(
            "res/shaders/unlitVertexShader.glsl",
            "res/shaders/unlitFragmentShader.glsl"
            );
        scene.setShader("simpleShader", simpleShader);

        // Textures
        Texture* brickTexture      = new Texture("res/textures/stylizedBricks_baseColour.png");
        Texture* cobblestoneTexture= new Texture("res/textures/cobblestone_baseColour.png");
        scene.setTexture("stylized brick", brickTexture);
        scene.setTexture("cobblestone", cobblestoneTexture);

        // Materials
        Material* brickMaterial = new Material(simpleShader);
        brickMaterial->name("brickMaterial");
        brickMaterial->setDiffuseTexture(&*brickTexture);
        scene.setMaterial("stylized bricks", brickMaterial);

        Material* cobbleMaterial = new Material(simpleShader);
        cobbleMaterial->name("cobbleMaterial");
        cobbleMaterial->setDiffuseTexture(&*cobblestoneTexture);
        scene.setMaterial("cobblestone", cobbleMaterial);

        Material* variants[2] = { brickMaterial, cobbleMaterial};

        // 3D grid parameters
        const int   gridSize  = 20;
        const float spacing  = 1.5f;
        const glm::vec3 origin(-10.0f, -10.0f, -10.0f);

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

                    std::string name = "cube_" + std::to_string(x) + "_" + std::to_string(y) + "_" + std::to_string(z);
                    scene.setRenderObject(name.c_str(), cube);
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
            "res/shaders/unlitVertexShader.glsl",
            "res/shaders/unlitFragmentShader.glsl"
            );
        scene.setShader("simple shader", simpleShader);

        // Create Textures
        Texture* orithTexture = new Texture("res/textures/orith_diffuse_01.png");
        scene.setTexture("orith diffuse", orithTexture);

        // Create Materials
        Material* orithMaterial = new Material(simpleShader);
        orithMaterial->name("orithMaterial");
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

    int Scene::getRenderObjectCount() const
    {
        return renderObjects.size();
    }
}
