//
// Created by blinku on 10.02.19.
//

#pragma once

#include "mesh.h"
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <vector>

class Model {
public:
    Model() = default;
    Model(const char* modelPath);
    ~Model() = default;

    void Draw(Shader shader);
public:
    std::vector<Mesh> m_Meshes;
    std::string m_Directory;
    std::vector<Texture> m_TexturesLoaded;
private:
    void LoadModel(std::string modelPath);
    void ProcessNode(aiNode* node, const aiScene* scene);
    Mesh ProcessMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> LoadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
};
