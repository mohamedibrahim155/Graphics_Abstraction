#include "GraphicsRender.h"

GraphicsRender::GraphicsRender()
{
}

GraphicsRender::~GraphicsRender()
{
	ClearData();	
}

void GraphicsRender::AddModelsAndShader(Model* model, Shader* Shader)
{
	m_Models.push_back(model);
	m_Shaders.push_back(Shader);
}

void GraphicsRender::AddModelsAndShader(Model& model, Shader& Shader)
{
	m_Models.push_back(&model);
	m_Shaders.push_back(&Shader);
}

void GraphicsRender::AssignStencilShader(Shader* Shader)
{
	this->m_StencilShader = Shader;


}

std::vector<Model*> GraphicsRender::GetModelList()
{

	return m_Models;
}




void GraphicsRender::Draw()
{

	glStencilMask(0x00);
	for (size_t i = 0; i < m_Models.size(); i++)
	{
		if (m_Models[i] == selectedModel)
		{

			continue;

		}
		m_Models[i]->Draw(*m_Shaders[i]);

	}

	if (selectedModel != nullptr)
	{
		glStencilFunc(GL_ALWAYS, 1, 0xFF);
		glStencilMask(0xFF);
		glm::vec3 tempScale;


		tempScale = selectedModel->transform.scale;
		selectedModel->Draw(*m_Shaders[0]);
		
		glStencilFunc(GL_NOTEQUAL, 1, 0xFF);
		glStencilMask(0x00);
		glDisable(GL_DEPTH_TEST);
	
		
		glm::vec3 scale = selectedModel->transform.scale;
		
		selectedModel->transform.SetScale(scale + 0.1f);
		selectedModel->Draw(*m_StencilShader);
		selectedModel->transform.SetScale(tempScale);
		
	}
	glStencilMask(0xFF);
	glStencilFunc(GL_ALWAYS, 0, 0xFF);
	glEnable(GL_DEPTH_TEST);
}

void GraphicsRender::ClearData()
{
   //Deleteing model pointers
	if (m_Models.size() > 0)
	{
		for (Model* model : m_Models)
		{
			delete model;

		}
		m_Models.clear();
	}

	//Deleteing shader pointers
	if (m_Shaders.size() > 0)
	{
		for (Shader* shader : m_Shaders)
		{
			delete shader;

		}
		m_Shaders.clear();
	}
}
