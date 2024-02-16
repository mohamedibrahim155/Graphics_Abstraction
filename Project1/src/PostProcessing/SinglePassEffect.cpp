#include "SinglePassEffect.h"
#include "../Time.h"
#include "../GraphicsRender.h"
SinglePassEffect::SinglePassEffect()
{
}



void SinglePassEffect::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());
}

void SinglePassEffect::ApplyEffect(FrameBuffer* frameBuffer)
{
	time += Time::GetInstance().deltaTime;

	frameBuffer->Bind();

	shader->Bind();

	GLCALL(glActiveTexture(GL_TEXTURE0));
	SetShaderUniforms();
	GLCALL(glBindTexture(GL_TEXTURE_2D, frameBuffer->GetColorAttachmentID()));
	Quad::GetInstance().RenderQuad();

	//shader->Unbind();
	//GraphicsRender::GetInstance().Clear();

	frameBuffer->Unbind();
}

void SinglePassEffect::DrawProperties()
{

	std::string title = "###" + name;
	ImGui::Checkbox(title.c_str(), &isEnabled);
	ImGui::SameLine();
	ImGui::Text(name.c_str());
}

void SinglePassEffect::SceneDraw()
{
}
