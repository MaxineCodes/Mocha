//
// Created by maxin on 02/12/2025.
//

#include "rendering.h"

#include <glad/glad.h>

#include "Window.h"
#include "Shader.h"
#include "Texture.h"
#include "../interface/gui.h"

namespace Mocha
{
    bool render(Scene scene)
    {
        // Create window through a GLFW wrapper
        Window window(1400, 1400, "Mocha :: OpenGL Realtime Rendering");
        // Setup gui
        GUI::setup(window.getWindow());

        const Shader simpleShader = Shader(
            "../../res/shaders/basicVertexShader.glsl",
            "../../res/shaders/basicFragmentShader.glsl"
            );

        // VAO, VBO
        // Triangle vertices (position + color + texcoord)
        float vertices[] = {
            // positions          // colors           // texture coords
            0.5f,  0.5f, 0.0f,   1.0f, 0.0f, 0.0f,   1.0f, 1.0f,   // top right
            0.5f, -0.5f, 0.0f,   0.0f, 1.0f, 0.0f,   1.0f, 0.0f,   // bottom right
           -0.5f, -0.5f, 0.0f,   0.0f, 0.0f, 1.0f,   0.0f, 0.0f,   // bottom left
           -0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 0.0f,   0.0f, 1.0f    // top left
       };
        unsigned int indices[] = {
            0, 1, 3, // first triangle
            1, 2, 3  // second triangle
        };

        // Create VAO, VBO
        unsigned int VBO, VAO, EBO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);
        glGenBuffers(1, &EBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, EBO);
        glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW);

        // position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);
        // color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);
        // texture coord attribute
        glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 8 * sizeof(float), (void*)(6 * sizeof(float)));
        glEnableVertexAttribArray(2);

        Texture brickTexture = Texture("../../res/textures/stylized_bricks_basecolour.png");
        Texture cobblestoneTexture = Texture("../../res/textures/cobblestone_basecolour.png");

        // Render Loop
        while (!window.windowShouldClose())
        {
            window.pollEvents();

            // Start ImGui frame
            GUI::newFrame();

            // Show ImGui demo window
            GUI::createGuiElements();

            // Render
            glClearColor(0.6f, 0.7f, 0.8f, 1.0f); // gentle blue like the sky
            glClear(GL_COLOR_BUFFER_BIT);

            simpleShader.setInt("texture1", 0);
            simpleShader.setInt("texture2", 1);

            glActiveTexture(GL_TEXTURE0);
            brickTexture.use();
            glActiveTexture(GL_TEXTURE1);
            cobblestoneTexture.use();

            simpleShader.use();

            // Draw triangle
            glBindVertexArray(VAO);
            glDrawElements(GL_TRIANGLES, 6, GL_UNSIGNED_INT, 0);
            //glDrawArrays(GL_TRIANGLES, 0, 3);

            // Render ImGui
            GUI::draw();

            window.swapBuffers();
        }

        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);
        glDeleteBuffers(1, &EBO);

        GUI::cleanup();
        window.cleanup();

        return false;
    }

} // Mocha