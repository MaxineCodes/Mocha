//
// Created by maxin on 02/12/2025.
//

#include "rendering.h"

#include <glad/glad.h>

#include "Window.h"
#include "Shader.h"
#include "../interface/gui.h"

namespace Mocha
{
    bool render(Scene scene)
    {
        // Create window through a GLFW wrapper
        Window window(1280, 720, "Mocha :: OpenGL Realtime Rendering");
        // Setup gui
        GUI::setup(window.getWindow());

        const Shader simpleShader = Shader(
            "D:/Dev/2026/Mocha/res/shaders/basicVertexShader.glsl",
            "D:/Dev/2026/Mocha/res/shaders/basicFragmentShader.glsl"
            );

        // VAO, VBO
        // Triangle vertices (position + color)
        float vertices[] = {
            // positions        // colors
            0.0f,  0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // top (red)
           -0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left (green)
            0.5f, -0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // bottom right (blue)
       };

        // Create VAO, VBO
        unsigned int VBO, VAO;
        glGenVertexArrays(1, &VAO);
        glGenBuffers(1, &VBO);

        glBindVertexArray(VAO);

        glBindBuffer(GL_ARRAY_BUFFER, VBO);
        glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

        // Position attribute
        glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
        glEnableVertexAttribArray(0);

        // Color attribute
        glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
        glEnableVertexAttribArray(1);

        glBindBuffer(GL_ARRAY_BUFFER, 0);
        glBindVertexArray(0);




        // Render Loop
        while (!window.windowShouldClose())
        {
            window.pollEvents();

            // Start ImGui frame
            GUI::newFrame();

            // Show ImGui demo window
            GUI::createGuiElements();

            // Render
            glClearColor(0.1f, 0.1f, 0.1f, 1.0f);
            glClear(GL_COLOR_BUFFER_BIT);

            // Draw triangle
            simpleShader.use();
            simpleShader.setFloat("someUniform", 1.0f);

            glBindVertexArray(VAO);
            glDrawArrays(GL_TRIANGLES, 0, 3);

            // Render ImGui
            GUI::draw();

            window.swapBuffers();
        }

        // Cleanup
        glDeleteVertexArrays(1, &VAO);
        glDeleteBuffers(1, &VBO);

        GUI::cleanup();
        window.cleanup();

        return false;
    }

} // Mocha