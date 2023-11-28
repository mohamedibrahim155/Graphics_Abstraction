#include "mesh.h"
#include <string>
#include "Renderer.h"

Mesh::Mesh( std::vector<Vertex> vertices, std::vector<unsigned int> indices, std::vector<Texture> textures)
{
    
    this->vertices = vertices;
    this->indices = indices;
    this->textures = textures;

    setupMesh();
}

void Mesh::meshDraw(Shader& shader)
{
    if (isTransparancy)
    {
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    }

    unsigned int diffuseNr = 0;
    unsigned int specularNr = 0;
    unsigned int alphaNr = 0;
    //unsigned int normalNr = 1;
    //unsigned int emissiveNr = 1;
   // unsigned int heightNr = 1;
    for (unsigned int i = 0; i < textures.size(); i++)
    {
       GLCALL(glActiveTexture(GL_TEXTURE0 + i));
        std::string number;
        std::string name = textures[i].type;
        if (name == "material.diffuse")
        {
            number = std::to_string(diffuseNr++);
        }
        else if (name == "material.specular")
        {
            number = std::to_string(specularNr++);
        }
        else if (name == "material.alphaMask")
        {
            number = std::to_string(alphaNr++);
        }


      
        shader.setFloat("material.shininess", 128);
        GLCALL(glUniform1i(glGetUniformLocation(shader.ID, (name + number).c_str()), i));
        if (isTransparancy)
        {
        GLCALL(shader.setFloat("material.alpha", 1.0f));
        GLCALL (shader.setBool("isMasking", true));
        }
        else
        {
        GLCALL(shader.setFloat("material.alpha", 1.0f));
        shader.setBool("isMasking", false);
        }
         //std::cout << shader.FindUniformLocations((name + number).c_str()) << std::endl;

        GLCALL(glBindTexture(GL_TEXTURE_2D, textures[i].id));
    }
    GLCALL(glActiveTexture(GL_TEXTURE0));


   VAO->Bind();
   IBO->Bind();

   if (isWireFrame)
   {
       GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_LINE));
   }
   else
   {
       GLCALL(glPolygonMode(GL_FRONT_AND_BACK, GL_FILL));
   }
   
   GLCALL( glDrawElements(GL_TRIANGLES, static_cast<unsigned int>(indices.size()), GL_UNSIGNED_INT, 0));
   VAO->Unbind();
   if (isTransparancy)
   {
       glDisable(GL_BLEND);
   }
  

}

void Mesh::SetTransparency(const bool& isTransparent)
{
    this->isTransparancy = isTransparent;
}

void Mesh::setupMesh()
{
    CalculateTriangles();
    VAO = new VertexArray();
    void* pVertices = static_cast<void*>(&vertices[0]);
    unsigned int size = vertices.size() * sizeof(Vertex);
    VBO = new VertexBuffer(pVertices, size);
    layout = new VertexBufferLayout();

    layout->Push<float>(3);
    layout->Push<float>(3);
    layout->Push<float>(2);
    layout->Push<float>(4);

    VAO->AddBuffer(*VBO, *layout);
    IBO = new IndexBufferObject(&indices[0], indices.size());

}

void Mesh::CalculateTriangles()
{
    for (size_t i = 0; i < indices.size(); i += 3)
    {
        Triangles tempTri;

        tempTri.v1 = vertices[indices[i]].Position;
        tempTri.v2 = vertices[indices[i + 1]].Position;
        tempTri.v3 = vertices[indices[i + 2]].Position;

        tempTri.normal = (vertices[indices[i]].Normal +
            vertices[indices[i + 1]].Normal +
            vertices[indices[i + 2]].Normal) / 3.0f;
        triangle.push_back(tempTri);
    }
}
