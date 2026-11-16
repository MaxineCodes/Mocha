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

        // Create Shaders
        Shader* simpleShader = new Shader(
            "res/shaders/basicVertexShader.glsl",
            "res/shaders/basicFragmentShader.glsl"
            );
        debugScene.addShader(simpleShader);

        Shader* defaultShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/defaultFragmentShader.glsl"
            );
        debugScene.addShader(defaultShader);

        // Create Textures
        Texture* brickTexture = new Texture("res/textures/stylizedBricks_baseColour.png");
        debugScene.addTexture(brickTexture);
        Texture* cobblestoneTexture = new Texture("res/textures/cobblestone_baseColour.png");
        debugScene.addTexture(cobblestoneTexture);
        Texture* minecraftFoxTexture = new Texture("res/textures/minecraftFox_baseColour.png");
        debugScene.addTexture(minecraftFoxTexture);
        Texture* minecraftSnowFoxTexture = new Texture("res/textures/minecraftSnowFox_baseColour.png");
        debugScene.addTexture(minecraftSnowFoxTexture);
        Texture* orithTexture = new Texture("res/textures/orith_diffuse_01.png");
        debugScene.addTexture(orithTexture);

        // Create Materials
        Material* minecraftFoxMaterial = new Material(simpleShader);
        minecraftFoxMaterial->name("minecraftFoxMaterial");
        minecraftFoxMaterial->addTexture(*minecraftSnowFoxTexture);
        debugScene.addMaterial(minecraftFoxMaterial);

        Material* bricksMaterial = new Material(simpleShader);
        bricksMaterial->name("bricksMaterial");
        bricksMaterial->addTexture(*brickTexture);
        debugScene.addMaterial(bricksMaterial);

        Material* defaultMaterial = new Material(defaultShader);
        defaultMaterial->name("defaultMaterial");
        debugScene.addMaterial(defaultMaterial);

        Material* cuteFoxMaterial = new Material(simpleShader);
        cuteFoxMaterial->name("cuteFoxMaterial");
        cuteFoxMaterial->addTexture(*brickTexture);
        debugScene.addMaterial(cuteFoxMaterial);

        Material* orithMaterial = new Material(simpleShader);
        orithMaterial->name("orithMaterial");
        orithMaterial->addTexture(*orithTexture);
        debugScene.addMaterial(orithMaterial);

        // Create RenderObjects
        RenderObject* myGloriousCube = new RenderObject("res/models/cube.obj");
        myGloriousCube->assignMaterial(bricksMaterial);
        debugScene.addRenderObject(myGloriousCube);

        RenderObject* utahTeapot = new RenderObject("res/models/utah_teapot.obj");
        utahTeapot->assignMaterial(defaultMaterial);
        debugScene.addRenderObject(utahTeapot);

        //RenderObject* stanfordDragon = new RenderObject("res/models/stanford_dragon.obj");
        //stanfordDragon->assignMaterial(cuteFoxMaterial);
        //debugScene.addRenderObject(stanfordDragon);
        RenderObject* orith = new RenderObject("res/models/orith.obj");
        orith->assignMaterial(orithMaterial);
        debugScene.addRenderObject(orith);

        RenderObject* minecraftFox = new RenderObject("res/models/minecraft_fox.obj");
        minecraftFox->assignMaterial(minecraftFoxMaterial);
        debugScene.addRenderObject(minecraftFox);

        RenderObject* cuteFox = new RenderObject("res/models/cute_fox.obj");
        cuteFox->assignMaterial(cuteFoxMaterial);
        debugScene.addRenderObject(cuteFox);

        // Transformations
        cuteFox->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
        cuteFox->transform.position = glm::vec3(4.0f, 0.0f, 0.0f);

        minecraftFox->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
        minecraftFox->transform.position = glm::vec3(2.0f, 0.0f, 0.0f);
        minecraftFox->transform.rotation = glm::vec3(0.0f, 0.0f, 1.5f);

        myGloriousCube->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
        myGloriousCube->transform.position = glm::vec3(-2.0f, 0.0f, 0.0f);

        //stanfordDragon->transform.scale = glm::vec3(0.01f, 0.01f, 0.01f);
        //stanfordDragon->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
        //stanfordDragon->transform.rotation = glm::vec3(0.0f, 0.0f, 0.0f);

        orith->transform.scale = glm::vec3(10.0f, 10.0f, 10.0f);

        utahTeapot->transform.position = glm::vec3(-5.0f, 0.0f, 0.0f);
        utahTeapot->transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        utahTeapot->transform.rotation = glm::vec3(45.0f, 45.0f, 45.0f);


        return debugScene;
    }

    Scene Scene::spatialGridScene()
    {
        Scene scene;

        scene.skyColor = glm::vec4(0.6f, 0.7f, 0.8f, 1.0f); // gentle blue like the sky

        // Shader
        Shader* simpleShader = new Shader(
            "res/shaders/basicVertexShader.glsl",
            "res/shaders/basicFragmentShader.glsl"
            );
        scene.addShader(simpleShader);

        // Textures
        Texture* brickTexture      = new Texture("res/textures/stylizedBricks_baseColour.png");
        Texture* cobblestoneTexture= new Texture("res/textures/cobblestone_baseColour.png");
        scene.addTexture(brickTexture);
        scene.addTexture(cobblestoneTexture);

        // Materials
        Material* brickMaterial = new Material(simpleShader);
        brickMaterial->name("brickMaterial");
        brickMaterial->addTexture(*brickTexture);
        scene.addMaterial(brickMaterial);

        Material* cobbleMaterial = new Material(simpleShader);
        cobbleMaterial->name("cobbleMaterial");
        cobbleMaterial->addTexture(*cobblestoneTexture);
        scene.addMaterial(cobbleMaterial);

        Material* variants[2] = { brickMaterial, cobbleMaterial};

        // 3D grid parameters
        const int   gridSize  = 20;
        const float spacing  = 1.5f;
        const glm::vec3 origin(-10.0f, -10.0f, -10.0f);

        // Seed once, outside the loop
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
                    cube->assignMaterial(randomMaterial);

                    cube->transform.scale    = glm::vec3(0.5f, 0.5f, 0.5f); // half-spacing so cubes don't touch
                    cube->transform.position = origin +
                        glm::vec3(static_cast<float>(x),
                                  static_cast<float>(y),
                                  static_cast<float>(z)) * spacing;

                    scene.addRenderObject(cube);
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
            "res/shaders/basicVertexShader.glsl",
            "res/shaders/basicFragmentShader.glsl"
            );
        scene.addShader(simpleShader);

        // Create Textures
        Texture* orithTexture = new Texture("res/textures/orith_diffuse_01.png");
        scene.addTexture(orithTexture);

        // Create Materials
        Material* orithMaterial = new Material(simpleShader);
        orithMaterial->name("orithMaterial");
        orithMaterial->addTexture(*orithTexture);
        scene.addMaterial(orithMaterial);

        // Create RenderObjects
        RenderObject* orith = new RenderObject("res/models/orith.obj");
        orith->assignMaterial(orithMaterial);
        scene.addRenderObject(orith);

        // Transformations
        orith->transform.scale = glm::vec3(15.0f, 15.0f, 15.0f);

        return scene;
    }

    int Scene::getRenderObjectCount()
    {
        return renderObjects.size();
    }
}
