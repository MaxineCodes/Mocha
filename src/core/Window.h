//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_WINDOW_H
#define MOCHA_WINDOW_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

/*
 *  window.h
 *
 *  window.h offers an abstraction for GLFWwindow, and some helper functions to make the rest of the codebase cleaner and simpler.
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
        Window(int width, int height, const char* title);
        GLFWwindow* getWindow() const { return window; }

        void processInput() const;

        bool windowShouldClose() const;
        void pollEvents() const ;
        void swapBuffers() const;
        void cleanup() const;

        ~Window() { cleanup(); }

        static void framebuffer_size_callback(GLFWwindow* window, int width, int height);

    };

}

#endif //MOCHA_WINDOW_H