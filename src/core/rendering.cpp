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
#include "../interface/gui.h"
#include "camera/Camera.h"

namespace Mocha
{
    bool Render(Scene scene)
    {
        struct RenderSettings
        {
            glm::vec3 outlineColour = glm::vec3(1.0f, 1.0f, 0.0f); // Yellow
            float outlineThickness = 0.1f;
        };
        RenderSettings renderSettings;

        const int width = 1400, height = 800;
        // time
        float deltaTime = 0.0f;
        float lastFrame = 0.0f;

        // Create camera
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // TODO: create camera from scene

        // Create window through a GLFW wrapper
        Window window(width, height, "Mocha :: OpenGL Realtime Rendering", &camera);
        // Setup gui
        GUI::setup(window.getWindow());

        // Creating the scene here for now
        scene = Scene::DebugScene(); // TODO: seperate definition and implementation of scene
        GUI::updateScene(&scene); // pointer to scene for GUI

        // DEFAULT SHADERS
        // These are default/functional shaders, every scene must have them, and so they are declared in the renderer instead.
        // Ownership must also be handled by the renderer.
        Shader* outlineShader = new Shader("res/shaders/outlineVertex.glsl","res/shaders/outline.glsl");
        Shader* lightShader = new Shader("res/shaders/defaultVertexShader.glsl", "res/shaders/light.glsl");
        outlineShader->setVec3("colour", renderSettings.outlineColour);
        outlineShader->setFloat("outlineThickness", renderSettings.outlineThickness);

        // Make sure depth test is enabled, otherwise
        // things will render ontop of each other,
        // without respecting the z-buffer.
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LESS);

        // Enable stencil buffers for outlines
        glEnable(GL_STENCIL_TEST);
        glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
        glStencilOp(GL_KEEP, GL_KEEP, GL_REPLACE);

        // GL_LINE = wireframe, GL_FILL = not wireframe
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        int frameCount = 0;

        // Set Shader lights uniforms for all shaders
        scene.loadLights();


        // Render Loop
        while (!window.windowShouldClose())
        {
            logger::logInfoFrame("Starting frame: " + std::to_string(frameCount));

            // Calculate deltatime
            float currentFrame = static_cast<float>(glfwGetTime()); // TODO:　get time from window class function
            deltaTime = currentFrame - lastFrame;
            lastFrame = currentFrame;

            // Start ImGui frame
            GUI::newFrame();
            GUI::createGuiElements();

            // Render
            glClearColor(scene.skyColor.x, scene.skyColor.y, scene.skyColor.z, scene.skyColor.w);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);
            glClear(GL_STENCIL_BUFFER_BIT);

            // Stencil buffer bit to 1
            glStencilMask(0xFF);

            // create transformations
            glm::mat4 modelMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            //modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)); // TODO:　get time from window class function
            // view matrix
            glm::mat4 viewMatrix = camera.GetViewMatrix();
            //viewMatrix  = glm::translate(viewMatrix, glm::vec3(1.7f, -1.5f, -3.0f));
            // perspective matrix
            const float fov = camera.GetFOV(); //fov = glm::radians(45.0f);
            glm::mat4 perspectiveProjectionMatrix = glm::perspective(fov, float(width) / float(height), 0.1f, 100.0f);

            // TODO: assign all LIGHTS from SCENE into uniforms for OpenGL context

            // Set Shader Matrices for all shaders
            for (auto& [name, shader] : scene.shaders)
            {
                scene.getShader(name)->setMat4("model", modelMatrix);
                scene.getShader(name)->setMat4("view",  viewMatrix);
                scene.getShader(name)->setMat4("projection", perspectiveProjectionMatrix);
            }

            // --- FIRST RENDER PASS ---
            // Draw meshes
            for (auto& [name, renderObject] : scene.renderObjects)
            {
                // Stencil buffers needed for outlines in 2nd render pass
                if (renderObject->outline)
                {
                    glStencilFunc(GL_ALWAYS, 1, 0xFF);
                    glStencilMask(0xFF);
                }
                else glStencilMask(0x00);

                // Reset model matrix
                modelMatrix = glm::mat4(1.0f);
                // get RenderObject transforms and put them into the model matrix
                modelMatrix = glm::translate(modelMatrix, renderObject->transform.position);
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
                modelMatrix = glm::scale    (modelMatrix, renderObject->transform.scale);

                // Update the OpenGL context uniform for the correct shader.
                // RIGHT NOW THIS IS SIMPLY ALL SHADERS
                for (auto& [name, shader] : scene.shaders)
                {
                    scene.getShader(name)->setMat4("model", modelMatrix);
                    scene.getShader(name)->setVec3("view.position", camera.Position);
                }

                // TODO: Remove or implement this comment
                // Idea... what if I make a temporary vector of all renderObjects where stencilMask != 0x00?
                // Then I must only pass this vector to the 2nd render pass, saving on memory lookup time. :o

                // Draw
                if (renderObject->outline) glStencilFunc(GL_ALWAYS, 1, 0xFF);

                renderObject->draw();
            }

            // --- SECOND RENDER PASS ---
            // Draw outlines
            for (auto& [name, renderObject] : scene.renderObjects)
            {
                // Exit early if we don't need to do anything anyway.
                if (!renderObject->outline) continue;

                logger::logInfoFrame("OUTLINES FOR: " + renderObject->name);

                // Reset stencil buffer mask
                glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
                glStencilMask(0x00);
                // No depth for outlines
                glDisable(GL_DEPTH_TEST);

                // Reset model matrix
                modelMatrix = glm::mat4(1.0f);
                // get RenderObject transforms and put them into the model matrix
                modelMatrix = glm::translate(modelMatrix, renderObject->transform.position);
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.z, glm::vec3(0.0f, 0.0f, 1.0f));
                modelMatrix = glm::scale    (modelMatrix, renderObject->transform.scale);
                // Update the OpenGL context uniform for the outline shader.
                outlineShader->setMat4("model", modelMatrix);
                outlineShader->setMat4("projection", perspectiveProjectionMatrix);
                outlineShader->setMat4("view",  viewMatrix);

                // Draw the outline
                renderObject->draw(*outlineShader);

                // Clean up for next pass
                // Reset stencil buffer mask
                glStencilMask(0xFF);
                glStencilFunc(GL_ALWAYS, 1, 0xFF);
                // Enable depth again for next render loop
                glEnable(GL_DEPTH_TEST);
            }

            // Render ImGui
            GUI::draw();

            window.swapBuffers();
            window.pollEvents(deltaTime);

            frameCount++;
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