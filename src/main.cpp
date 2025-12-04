#include <iostream>

#include "core/rendering.h"

int main()
{
    // First, create the scene you want to render
    // Planned: Load .USD scene, or a constructor which generates something for you
    Mocha::Scene myScene;


    if (!Mocha::render(myScene))
    {
        std::cout << "Rendering terminated." << std::endl;
    }
    return 0;
}
