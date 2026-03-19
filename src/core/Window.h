//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_WINDOW_H
#define MOCHA_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "camera/Camera.h"

/*
 *  Window.h
 *
 *  Window.h offers an abstraction for GLFWwindow, and some helper functions to make the rest of the codebase cleaner and simpler.
 *  Will also handle input in the future.
 *
 *  Functions:
 *  Window::windowShouldClose
 *  ...
 *
 */

namespace Mocha
{

    class Window
    {
    public:
        GLFWwindow* window;
        int width, height;
        Camera* camera;
        bool firstMouse = true;
        float lastX = width / 2.0f, lastY = height / 2.0f;


        Window(int width, int height, const char* title, Camera* camera);
        GLFWwindow* getWindow() const { return window; }

        void processInput(float deltaTime) const;
        void processMouseInput() const;

        bool windowShouldClose() const;
        void pollEvents(float deltaTime) const ;
        void swapBuffers() const;
        void cleanup() const;

        ~Window() { cleanup(); }

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

        static void mouseCallback(GLFWwindow *window, double xposIn, double yposIn);
        static void mouseScrollCallback(GLFWwindow *window, double xposIn, double yposIn);
    };

}

#endif //MOCHA_WINDOW_H