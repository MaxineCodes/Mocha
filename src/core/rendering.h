//
// Created by maxin on 02/12/2025.
//

#ifndef MOCHA_RENDERING_H
#define MOCHA_RENDERING_H

#include "scene.h"

namespace Mocha
{
    inline const char* vertexShaderSource = R"(
    #version 330 core
    layout (location = 0) in vec3 aPos;
    layout (location = 1) in vec3 aColor;

    out vec3 fragColor;

    void main()
    {
        gl_Position = vec4(aPos, 1.0);
        fragColor = aColor;
    }
    )";

    inline const char* fragmentShaderSource = R"(
    #version 330 core
    in vec3 fragColor;
    out vec4 FragColor;

    void main()
    {
        FragColor = vec4(fragColor, 1.0);
    }
    )";

    bool render(Scene scene);

    class rendering {
    };
} // Mocha

#endif //MOCHA_RENDERING_H