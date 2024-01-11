#ifndef SHADER_H
#define SHADER_H

#include <glad/glad.h>
#include <glm/glm.hpp>

#include <string>
#include <fstream>
#include <sstream>
#include <iostream>
#include <map>



enum BlendMode
{
    OPAQUE = 0,
    ALPHA_CUTOUT=1,
    ALPHA_BLEND=2,
    SOLID=3

};

class Shader
{
public:
    unsigned int ID;

    bool modelUniform = true;
    
    BlendMode blendMode = BlendMode::OPAQUE;

    Shader(const char* vertexPath, const char* fragmentPath, BlendMode type = BlendMode::OPAQUE);
   ~Shader();
       
     void Bind() const;
     void Unbind() const;
    
    void setBool(const std::string& name, bool value) ;
   
    void setInt(const std::string& name, int value) ;
   
    void setFloat(const std::string& name, float value) ;

    void setVec2(const std::string& name, const glm::vec2& value) ;
   
    void setVec2(const std::string& name, float x, float y) ;
  
    void setVec3(const std::string& name, const glm::vec3& value) ;
   
    void setVec3(const std::string& name, float x, float y, float z) ;
  
    void setVec4(const std::string& name, const glm::vec4& value) ;
    
    void setVec4(const std::string& name, float x, float y, float z, float w) ;
   
    void setMat2(const std::string& name, const glm::mat2& mat) ;
    
    void setMat3(const std::string& name, const glm::mat3& mat) ;
   
    void setMat4(const std::string& name, const glm::mat4& mat) ;

    unsigned  int FindUniformLocations(const std::string& name);
   


private:
  
    void checkCompileErrors(unsigned int shader, std::string type);

    std::map<std::string, int> m_LocationCache;
   
};
#endif