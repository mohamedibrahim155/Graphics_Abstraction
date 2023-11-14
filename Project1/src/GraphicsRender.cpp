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


void GraphicsRender::Draw()
{
	for (size_t i = 0; i < m_Models.size(); i++)
	{
		m_Models[i]->Draw(*m_Shaders[i]);
	}
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
