//
// Created by maxin on 02/12/2025.
//

#ifndef MOCHA_RENDERING_H
#define MOCHA_RENDERING_H

#include "Scene.h"

#include "../interface/logger.h"

/*
 *  rendering.h
 *
 *  rendering.h contains the Mocha::Render() function and exposes the render loop.
 *  Render() loads the scene file, and prepares everything for OpenGL to render the graphics,
 *  as well as the GUI rendering through ImGUI.
 *
 */

namespace Mocha
{
    bool Render(Scene scene);

} // Mocha

#endif //MOCHA_RENDERING_H