#pragma once

#include "Renderer.h"
#include"model.h"
#include "Shader.h"


struct ModelAndShader
{

};
class GraphicsRender
{
public:
	GraphicsRender();
	~GraphicsRender();

	void AddModelsAndShader(Model* model, Shader* Shader);
	void AddModelsAndShader(Model& model, Shader& Shader);
	
	void AssignStencilShader( Shader* Shader);

	std::vector<Model*> GetModelList();


	void Draw();

	Model* selectedModel;
	

private:
	Shader* m_StencilShader;

	void ClearData();

	std::vector<Model*> m_Models;
	std::vector<Shader*> m_Shaders;




};

