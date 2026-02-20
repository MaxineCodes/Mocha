#include <iostream>
#include "core/rendering.h"

//////////////////////////////////////////////////////////////////////////////////////
//
//    MOCHA - Immediate-mode OpenGL 3.3 3D Rendering Engine
//
//////////////////////////////////////////////////////////////////////////////////////
/*
 *  Mocha is a simple cross-platform 3D OpenGL core-profile rendering engine to render 3D objects in real-time,
 *  supporting physically based rendering algorithms and scene loading.
 *  If you're familiar with 3D viewing applications, a main point of inspiration for this project is Sketchfab and Marmoset Viewer.
 *  Performance is not a priority, but being GPU based and only handling small scenes, this should not be a major issue.
 *
 *  The general flow of the application:
 *      1; Set some options for the renderer, logger, or for debugging.
 *      2; Construct a scene to be rendered.
 *      3; Pass the scene to the Mocha::Render function.
 *
 *
 */

int main()  
{
    Mocha::logger::setUseCout(true);
    Mocha::logger::setPrintDebug(true);

    // First, create the scene you want to render
    // Planned: Load .USD scene, or a constructor which generates something for you
    Mocha::Scene myScene;


    if (!Mocha::Render(myScene))
    {
        std::cout << "Rendering terminated." << std::endl;
    }
    return 0;
}
