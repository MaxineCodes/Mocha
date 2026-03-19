//
// Created by maxine on 19/03/2026.
//

//#include "../Mesh.h"

#ifndef MOCHA_MODELIMPORTING_H
#define MOCHA_MODELIMPORTING_H

namespace Mocha
{
    void importModel(const char* path);
    void processNode(aiNode* node, const aiScene* scene);
    //Mesh processMesh(aiMesh* mesh, const aiScene* scene);
}

#endif //MOCHA_MODELIMPORTING_H