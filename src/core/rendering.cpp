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
        Camera camera(glm::vec3(0.0f, 0.0f, 3.0f)); // TODO: create camera from scene

        // Create window through a GLFW wrapper
        Window window(width, height, "Mocha :: OpenGL Realtime Rendering", &camera);
        // Setup gui
        GUI::setup(window.getWindow());

        // Creating the scene here for now
        scene = Scene::DebugScene(); // TODO: seperate definition and implementation of scene

        // Make sure depth test is enabled, otherwise
        // things will render ontop of each other,
        // without respecting the z-buffer.
        glEnable(GL_DEPTH_TEST);

        // GL_LINE = wireframe, GL_FILL = not wireframe
        //glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

        int frameCount = 0;

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

            // Show ImGui demo window
            GUI::createGuiElements();

            // Render
            glClearColor(scene.skyColor.x, scene.skyColor.y, scene.skyColor.z, scene.skyColor.w);
            glClear(GL_COLOR_BUFFER_BIT);
            glClear(GL_DEPTH_BUFFER_BIT);

            // create transformations
            glm::mat4 modelMatrix = glm::mat4(1.0f); // make sure to initialize matrix to identity matrix first
            glm::mat4 viewMatrix = camera.GetViewMatrix();
            //modelMatrix = glm::rotate(modelMatrix, (float)glfwGetTime(), glm::vec3(0.0f, 1.0f, 0.0f)); // TODO:　get time from window class function
            viewMatrix  = glm::translate(viewMatrix, glm::vec3(1.7f, -1.5f, -3.0f));
            // perspective matrix
            const float fov = camera.GetFOV(); //fov = glm::radians(45.0f);
            glm::mat4 perspectiveProjectionMatrix = glm::perspective(fov, float(width) / float(height), 0.1f, 100.0f);

            /*
            // retrieve the matrix uniform locations
            unsigned int modelLoc = glGetUniformLocation(simpleShader.shaderProgramID, "model");
            unsigned int viewLoc  = glGetUniformLocation(simpleShader.shaderProgramID, "view");
            // pass them to the shaders
            glUniformMatrix4fv(modelLoc, 1, GL_FALSE, glm::value_ptr(modelMatrix));
            glUniformMatrix4fv(viewLoc, 1, GL_FALSE, &viewMatrix[0][0]);
            */



            // Set Shader Matrices
            for (size_t i = 0; i < scene.shaders.size(); i++)
            {
                scene.shaders[i]->setMat4("model", modelMatrix);
                scene.shaders[i]->setMat4("view",  viewMatrix);
                scene.shaders[i]->setMat4("projection", perspectiveProjectionMatrix);
            }

            // Draw meshes
            for (RenderObject* renderObject : scene.renderObjects)
            {
                // Reset model matrix
                modelMatrix = glm::mat4(1.0f);
                // get RenderObject transforms and put them into the model matrix
                modelMatrix = glm::translate(modelMatrix, renderObject->transform.position);
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.x, glm::vec3(1.0f, 0.0f, 0.0f));
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.y, glm::vec3(0.0f, 1.0f, 0.0f));
                modelMatrix = glm::rotate   (modelMatrix, renderObject->transform.rotation.z, glm::vec3(1.0f, 0.0f, 1.0f));
                modelMatrix = glm::scale    (modelMatrix, renderObject->transform.scale);
                // Update the OpenGL context uniform for the correct shader.
                for (size_t i = 0; i < scene.shaders.size(); i++)
                {
                    scene.shaders[i]->setMat4("model", modelMatrix);
                }

                // draw
                renderObject->draw();
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