 //
// Created by maxin on 04/12/2025.
//

#ifndef MOCHA_GUI_H
#define MOCHA_GUI_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>

#include "../core/Scene.h"


/*
 *  gui.h
 *
 *  gui.h contains everything handling GUI rendering.
 *  Mostly abstractions for ImGUI.
 *
 */
namespace Mocha
{
    namespace GUI
    {
        inline Scene* scene;

        // Setup prerequisites for getting gui to render.
        // Only needs to be called once before the render loop.
        void setup(GLFWwindow* window);
        // Start a new frame to draw to. Must be called start of every frame.
        void newFrame();
        // Draw the GUI.
        void createGuiElements();
        void draw();
        // Update the scene
        inline void updateScene(Scene* newScene) { scene = newScene; }
        // Cleanup at the end of the frame.
        void cleanup();

        ///////////////// Private functions
        void DrawLogWindow();
        void DrawFrameLogWindow();
        void DrawInputLogWindow();
        void DrawOutliner();
    }
}


#endif //MOCHA_GUI_H