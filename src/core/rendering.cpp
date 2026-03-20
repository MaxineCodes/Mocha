//
// Created by maxin on 02/12/2025.
//

#include "rendering.h"

#include <glad/glad.h>

#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Window.h"
#include "renderobject/Shader.h"
#include "renderobject/Texture.h"
#include "../interface/gui.h"
#include "camera/Camera.h"

namespace Mocha
{
    bool Render(Scene scene)
    {
        const int width = 1400, height = 800;
        // time
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        // Create camera
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f));

        // Create window through a GLFW wrapper
        Window window(width, height, "Mocha :: OpenGL Realtime Rendering", &camera);
        // Setup gui
        GUI::setup(window.getWindow());

        const Shader simpleShader = Shader(
            "res/shaders/basicVertexShader.glsl",
            "res/shaders/basicFragmentShader.glsl"
            );

        const Shader defaultShader = Shader(
            "res/shaders/defaultVertexShader.glsl",
            "res/shaders/defaultFragmentShader.glsl"
            );



        // Make sure depth test is enabled, otherwise
        // things will render ontop of each other,
        // without respecting the z-buffer.
        glEnable(GL_DEPTH_TEST);

        // GL_LINE = wireframe, GL_FILL = not wireframe
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        //Texture brickTexture = Texture("res/textures/stylized_bricks_basecolour.png");
        //Texture cobblestoneTexture = Texture("res/textures/cobblestone_basecolour.png");
        Texture minecraftFoxTexture = Texture("res/textures/minecraft_fox.png");
        Texture minecraftSnowFoxTexture = Texture("res/textures/minecraft_snow_fox.png");


        Material minecraftFoxMaterial = Material(&simpleShader);
        minecraftFoxMaterial.name("minecraftFoxMaterial");
        minecraftFoxMaterial.addTexture(minecraftSnowFoxTexture);

        Material bricksMaterial = Material(&simpleShader);
        bricksMaterial.name("bricksMaterial");
        bricksMaterial.addTexture(Texture("res/textures/stylized_bricks_basecolour.png"));

        Material defaultMaterial = Material(&defaultShader);
        defaultMaterial.name("defaultMaterial");
        defaultMaterial.addTexture(Texture("res/textures/cobblestone_basecolour.png"));

        RenderObject myGloriousCube = RenderObject("res/models/cube.obj");
        myGloriousCube.assignMaterial(&bricksMaterial);
        RenderObject utahTeapot = RenderObject("res/models/utah_teapot.obj");
        utahTeapot.assignMaterial(&defaultMaterial);
        RenderObject minecraftFox = RenderObject("res/models/minecraft_fox.obj");
        minecraftFox.assignMaterial(&minecraftFoxMaterial);
        RenderObject cuteFox = RenderObject("res/models/cute_fox.obj");
        cuteFox.assignMaterial(&defaultMaterial);



        // Render Loop
        while (!window.windowShouldClose())
        {
            // Calculate deltatime
            float currentFrame = static_cast<float>(glfwGetTime()); // TODO:　get time from window class function
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // Start ImGui frame
            GUI::newFrame();

            // Show ImGui demo window
            GUI::createGuiElements();

            // Render
            glClearColor(0.6f, 0.7f, 0.8f, 1.0f); // gentle blue like the sky
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);

            //simpleShader.setInt("texture1", 0);
            //simpleShader.setInt("texture2", 1);

            //glActiveTexture(GL_TEXTURE0);
            //minecraftFoxTexture.use();
            //glActiveTexture(GL_TEXTURE1);
            //minecraftSnowFoxTexture.use();

            //simpleShader.use();

            // create transformations
            glm::mat4 modelMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 viewMatrix = camera.GetViewMatrix();
            modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)); // TODO:　get time from window class function
            viewMatrix  = glm::translate(viewMatrix, glm::vec3(1.7f, -1.5f, -3.0f));
            // perspective matrix
            const float fov = camera.GetFOV(); //fov = glm::radians(45.0f);
            glm::mat4 perspectiveProjectionMatrix = glm::perspective(fov, float(width) / float(height), 0.1f, 100.0f);

            // retrieve the matrix uniform locations
            unsigned int modelLoc = glGetUniformLocation(simpleShader.shaderProgramID, "model");
            unsigned int viewLoc  = glGetUniformLocation(simpleShader.shaderProgramID, "view");
            // pass them to the shaders
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);

            simpleShader.setMat4("projection", perspectiveProjectionMatrix);
            defaultShader.setMat4("projection", perspectiveProjectionMatrix);
            //simpleShader.setMat4("view", viewMatrix);

            // Draw meshes
            //utahTeapot.draw();
            //myGloriousCube.transform.scale = glm::vec3(50.0f, 50.0f, 50.0f);
            //myGloriousCube.draw();
            minecraftFox.draw();
            //cuteFox.transform.scale = glm::vec3(2.5f, 2.5f, 2.5f);
            //cuteFox.draw();

            // Render ImGui
            GUI::draw();

            window.swapBuffers();
            window.pollEvents(deltaTime);
        }

        // Cleanup
        //glDeleteVertexArrays(1, &VAO);
        //glDeleteBuffers(1, &VBO);
        //glDeleteBuffers(1, &EBO);

        GUI::cleanup();
        window.cleanup();

        return false;
    }

} // Mocha