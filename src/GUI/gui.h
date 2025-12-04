//
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_GUI_H
#define MOCHA_GUI_H

#include <GLFW/glfw3.h>

namespace Mocha
{
    namespace GUI
    {
        // Setup prerequisites for getting gui to render.
        // Only needs to be called once before the render loop.
        void setup(GLFWwindow* window);

        // Start a new frame to draw to. Must be called start of every frame.
        void newFrame();

        // Draw the GUI.
        void createGuiElements();

        void draw();

        // Cleanup at the end of the frame.
        void cleanup();
    }
}


#endif //MOCHA_GUI_H