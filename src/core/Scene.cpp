//
// Created by maxin on 02/12/2025.
//

#include "Scene.h"

namespace Mocha
{
    Scene Scene::DebugScene()
    {
        Scene DebugScene;

        // Create Shaders
        Shader* simpleShader = new Shader(
            "res/shaders/basicVertexShader.glsl",
            "res/shaders/basicFragmentShader.glsl"
            );
        DebugScene.addShader(simpleShader);

        Shader* defaultShader = new Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/defaultFragmentShader.glsl"
            );
        DebugScene.addShader(defaultShader);

        // Create Textures
        Texture* brickTexture = new Texture("res/textures/stylizedBricks_baseColour.png");
        DebugScene.addTexture(brickTexture);
        Texture* cobblestoneTexture = new Texture("res/textures/cobblestone_baseColour.png");
        DebugScene.addTexture(cobblestoneTexture);
        Texture* minecraftFoxTexture = new Texture("res/textures/minecraftFox_baseColour.png");
        DebugScene.addTexture(minecraftFoxTexture);
        Texture* minecraftSnowFoxTexture = new Texture("res/textures/minecraftSnowFox_baseColour.png");
        DebugScene.addTexture(minecraftSnowFoxTexture);

        // Create Materials
        Material* minecraftFoxMaterial = new Material(simpleShader);
        minecraftFoxMaterial->name("minecraftFoxMaterial");
        minecraftFoxMaterial->addTexture(*minecraftSnowFoxTexture);
        DebugScene.addMaterial(minecraftFoxMaterial);

        Material* bricksMaterial = new Material(simpleShader);
        bricksMaterial->name("bricksMaterial");
        bricksMaterial->addTexture(*brickTexture);
        DebugScene.addMaterial(bricksMaterial);

        Material* defaultMaterial = new Material(defaultShader);
        defaultMaterial->name("defaultMaterial");
        DebugScene.addMaterial(defaultMaterial);

        Material* cuteFoxMaterial = new Material(simpleShader);
        cuteFoxMaterial->name("cuteFoxMaterial");
        cuteFoxMaterial->addTexture(*brickTexture);
        DebugScene.addMaterial(cuteFoxMaterial);

        // Create RenderObjects
        RenderObject* myGloriousCube = new RenderObject("res/models/cube.obj");
        myGloriousCube->assignMaterial(bricksMaterial);
        DebugScene.addRenderObject(myGloriousCube);
        RenderObject* utahTeapot = new RenderObject("res/models/utah_teapot.obj");
        utahTeapot->assignMaterial(defaultMaterial);
        DebugScene.addRenderObject(utahTeapot);
        RenderObject* minecraftFox = new RenderObject("res/models/minecraft_fox.obj");
        minecraftFox->assignMaterial(minecraftFoxMaterial);
        DebugScene.addRenderObject(minecraftFox);
        RenderObject* cuteFox = new RenderObject("res/models/cute_fox.obj");
        cuteFox->assignMaterial(cuteFoxMaterial);
        DebugScene.addRenderObject(cuteFox);

        // Transformations
        cuteFox->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
        cuteFox->transform.position = glm::vec3(4.0f, 0.0f, 0.0f);

        minecraftFox->transform.scale = glm::vec3(0.5f, 0.5f, 0.5f);
        minecraftFox->transform.position = glm::vec3(2.0f, 0.0f, 0.0f);
        minecraftFox->transform.rotation = glm::vec3(0.0f, 0.0f, 1.5f);

        myGloriousCube->transform.scale = glm::vec3(1.0f, 1.0f, 1.0f);
        myGloriousCube->transform.position = glm::vec3(-2.0f, 0.0f, 0.0f);

        utahTeapot->transform.position = glm::vec3(0.0f, 0.0f, 0.0f);
        utahTeapot->transform.scale = glm::vec3(0.2f, 0.2f, 0.2f);
        utahTeapot->transform.rotation = glm::vec3(45.0f, 45.0f, 45.0f);


        return DebugScene;
    }

    int Scene::getRenderObjectCount()
    {
        return renderObjects.size();
    }
}
