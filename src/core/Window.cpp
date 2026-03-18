//
// Created by maxin on 04/12/2025.
//

#include "Window.h"
#include "../interface/logger.h"

namespace Mocha
{
    Window::Window(int width, int height, const char *title, Camera* camera)
    {
        Window::camera = camera;

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

    void Window::processInput(float deltaTime) const
    {
        if (glfwGetKey(window, GLFW_KEY_ESCAPE) == GLFW_PRESS)
        {
            glfwSetWindowShouldClose(window, true);
        }

        if (glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS)
        {
            //logger::logInfo("W pressed");
            Window::camera->ProcessKeyboard(FORWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS)
        {
            //logger::logInfo("A pressed");
            Window::camera->ProcessKeyboard(LEFT, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS)
        {
            //logger::logInfo("S pressed");
            Window::camera->ProcessKeyboard(BACKWARD, deltaTime);
        }
        if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS)
        {
            //logger::logInfo("D pressed");
            Window::camera->ProcessKeyboard(RIGHT, deltaTime);
        }
    }

    bool Window::windowShouldClose() const
    {
        return glfwWindowShouldClose(window);
    }
    void Window::pollEvents(float deltaTime = 1.0f) const
    {
        glfwPollEvents();
        processInput(deltaTime);
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
