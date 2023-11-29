#pragma once
#ifndef MESH_H
#define MESH_H


#include <glad/glad.h> 
#include <glm/glm.hpp>
#include <glm/gtc/matrix_transform.hpp>

#include "Shader.h"



#include <string>
#include <vector>

#include "VertexBuffer.h"
#include "IndexBuffer.h"
#include "VertexBufferLayout.h"
#include "VertexArray.h"
#include "Textures.h"
#include "Vertex.h"
#include "Triangle.h"

#define MAX_BONE_INFLUENCE 4




class Mesh
{
public:

   

    std::vector<Vertex>       vertices;
    std::vector<unsigned int> indices;
    std::vector<Texture*>      textures;
    //unsigned int VAO;
    std::vector<Triangles> triangle;

    Mesh(std::vector<Vertex>& vertices, std::vector<unsigned int>& indices, std::vector<Texture*>& textures);
    void meshDraw(Shader& shader);
    void SetTransparency(const bool& isTransparent);
    void SetCutOff(const bool& isCutOut);

    VertexBuffer* VBO;
    IndexBufferObject* IBO;
    VertexArray* VAO;
    VertexBufferLayout* layout;
    bool isWireFrame = false;

private:
    
    //unsigned int VBO, EBO;

    void setupMesh();
    void CalculateTriangles();
    bool isTransparancy = false;
    bool isCutOut = false;
};
#endif
