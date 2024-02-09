#include "GraphicsRender.h"

GraphicsRender::GraphicsRender()
{
}

GraphicsRender::~GraphicsRender()
{
	ClearData();	
}

GraphicsRender& GraphicsRender::GetInstance()
{
	static GraphicsRender instance;
	return instance;
}


void GraphicsRender::AddModelAndShader(Model* model, Shader* shader)
{
	if (shader->blendMode ==OPAQUE || shader->blendMode == ALPHA_CUTOUT || shader->blendMode==SOLID)
	{
		modelAndShaderList.push_back(new ModelAndShader(model, shader));
	}
	else if (shader->blendMode == ALPHA_BLEND)
	{
		transparentmodelAndShaderList.push_back(new ModelAndShader(model, shader));
	}
	
}

void GraphicsRender::RemoveModel(Model* _model)
{
	for (ModelAndShader* model :  modelAndShaderList)
	{
		if (model->model == _model)
		{
			//delete model->model;
			//delete model->shader;

			modelAndShaderList.erase(std::remove(modelAndShaderList.begin(), modelAndShaderList.end(), model), 
				modelAndShaderList.end());
			return;
		}
	}

	for (ModelAndShader* model : transparentmodelAndShaderList)
	{
		if (model->model == _model)
		{
			//delete model->model;
			//delete model->shader;

			transparentmodelAndShaderList.erase(std::remove(transparentmodelAndShaderList.begin(), transparentmodelAndShaderList.end(), model),
				transparentmodelAndShaderList.end());
			return;
		}
	}
}



void GraphicsRender::AssignStencilShader(Shader* Shader)
{
	this->stencilShader = Shader;


}

void GraphicsRender::AssignCamera(Camera* camera)
{

	this->camera = camera;
}

void GraphicsRender::SortObject()
{
	CompareDistances compareDistance(camera->transform.position);
	std::sort(transparentmodelAndShaderList.begin(), transparentmodelAndShaderList.end(), compareDistance);


}

std::vector<Model*> GraphicsRender::GetModelList()
{
	std::vector<ModelAndShader*> list = modelAndShaderList;
	std::vector<Model*> modelList;
	modelList.reserve(list.size());
	
	for (size_t i = 0; i < list.size(); i++)
	{
		modelList.push_back(list[i]->model);
	}

	return modelList;
}




void GraphicsRender::Draw()
{


	glStencilMask(0x00);

	for (ModelAndShader* modelAndShader : modelAndShaderList)
	{
		if (modelAndShader->model == selectedModel)  continue;

		modelAndShader->model->Draw(modelAndShader->shader);
	}

	if (selectedModel != nullptr)
	{
		GLCALL(glStencilFunc(GL_ALWAYS, 1, 0xFF));
		GLCALL(glStencilMask(0xFF));
		glm::vec3 tempScale;


		tempScale = selectedModel->transform.scale;
		selectedModel->Draw(*defaultShader);
		
		GLCALL(glStencilFunc(GL_NOTEQUAL, 1, 0xFF));
		GLCALL(glStencilMask(0x00));
		GLCALL(glDisable(GL_DEPTH_TEST));
	
		
		glm::vec3 scale = selectedModel->transform.scale;
		
		selectedModel->transform.SetScale(scale + 0.1f);
		selectedModel->Draw(*stencilShader);
		selectedModel->transform.SetScale(tempScale);
		
	}
	GLCALL(glStencilMask(0xFF));
	GLCALL(glStencilFunc(GL_ALWAYS, 0, 0xFF));
	GLCALL(glEnable(GL_DEPTH_TEST));


	SortObject();

	for (ModelAndShader* modelAndShader :  transparentmodelAndShaderList)
	{
		modelAndShader->model->Draw(modelAndShader->shader);
	}

}

void GraphicsRender::ClearData()
{

	for (ModelAndShader* modelAndShader : modelAndShaderList)
	{
		delete modelAndShader->model;
		delete modelAndShader->shader;
		delete modelAndShader;
	}

	modelAndShaderList.clear();

	for (ModelAndShader* modelAndShader : transparentmodelAndShaderList)
	{
		delete modelAndShader->model;
		delete modelAndShader->shader;
		delete modelAndShader;
	}

	transparentmodelAndShaderList.clear();

}
