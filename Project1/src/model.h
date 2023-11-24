#pragma once
#ifndef MODEL_H
#define MODEL_H



#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>
#include <string>
#include <vector>

#include "mesh.h"
#include "Shader.h"
#include "Transform.h"





class Model
{
public:


    std::vector<Texture> textures_loaded;	
    std::vector<std::shared_ptr<Mesh>> meshes;
    std::string directory;
    std::string modelPath;


    int offset;
    std::string id; //if needed 
    float size;

    bool gammaCorrection;
    Transform transform;
    bool isWireFrame;
    bool isVisible =true;
    Model();
    Model(const Model& copyModel);
    Model( std::string const& path, bool isTextureFlip=false);
    
    void Draw(Shader& shader);
    

private:
    void loadModel(std::string const& path);    
    void processNode(aiNode* node, const aiScene* scene);   
    std::shared_ptr<Mesh> processMesh(aiMesh* mesh, const aiScene* scene);
    std::vector<Texture> loadMaterialTextures(aiMaterial* mat, aiTextureType type, std::string typeName);
   
    bool isTextureFlipped;
};




#endif