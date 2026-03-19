//
// Created by maxine on 19/03/2026.
//

#ifndef MOCHA_MODELIMPORTING_H
#define MOCHA_MODELIMPORTING_H

#include <string>
#include "../renderobject/Mesh.h"

namespace Mocha
{
    std::vector<Mesh> importModel(std::string path);
}

#endif //MOCHA_MODELIMPORTING_H