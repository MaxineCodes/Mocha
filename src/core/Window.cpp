//
// Created by maxin on 04/12/2025.
//

#include "Window.h"
#include "../interface/logger.h"

#include <glad/glad.h>

namespace Mocha
{
    Window::Window(int width, int height, const char *title)
    {
        if (!glfwInit())
        {
            logger::logError("Failed to initialise GLFW");
            return;
        }

        // Configure GLFW for OpenGL 3.3 core
        glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
        glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
        glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

        // Create window
        window = glfwCreateWindow(width, height, title, nullptr, nullptr);
        if (!window)
        {
            logger::logError("Failed to create GLFW window");
            glfwTerminate();
        }
        glfwMakeContextCurrent(window);
        glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);
        glfwSwapInterval(1); // Enable vsync

        // Load glad
        // Load OpenGL functions using GLAD (v0.1.x)
        if (!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
        {
            logger::logError("Failed to initialize GLAD");
            glfwDestroyWindow(window);
            glfwTerminate();
        }

        logger::logInfo("OpenGL loaded");
        logger::logInfo(("OpenGL version: " + std::string((const char*)glGetString(GL_VERSION))).c_str());
    }

    void Window::processInput() const
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }
    }

    bool Window::windowShouldClose() const
    {
        return glfwWindowShouldClose(window);
    }
    void Window::pollEvents() const
    {
        glfwPollEvents();
        processInput();
    }
    void Window::swapBuffers() const
    {
        glfwSwapBuffers(window);
    }

    void Window::cleanup() const
    {
        glfwDestroyWindow(window);
        glfwTerminate();
    }

    void Window::framebuffer_size_callback(GLFWwindow *window, int width, int height)
    {
        glViewport(0, 0, width, height);
    }

}
