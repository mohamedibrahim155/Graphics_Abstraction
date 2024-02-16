#include "ChromaticEffect.h"
#include "../Renderer.h"
#include"../Time.h"
ChromaticEffect::ChromaticEffect()
{
	name = "Chromatic";
	InitializeChromaticEffect();
}

void ChromaticEffect::InitializeChromaticEffect()
{

	chromaticShader = new Shader("Shaders/PostProcessing/Chromatic.vert", "Shaders/PostProcessing/Chromatic.frag");
}



void ChromaticEffect::ApplyEffect(FrameBuffer* frameBuffer)
{
	time += Time::GetInstance().deltaTime;
	frameBuffer->Bind();

	chromaticShader->Bind();

	GLCALL(glActiveTexture(GL_TEXTURE0));
	chromaticShader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	chromaticShader->setFloat("aberration", aberrationValue);   // abreation
	chromaticShader->setFloat("time", time);   // abreation
	GLCALL(glBindTexture(GL_TEXTURE_2D, frameBuffer->GetColorAttachmentID()));

	Quad::GetInstance().RenderQuad();
	chromaticShader->Unbind();

	frameBuffer->Unbind();

}

void ChromaticEffect::DrawProperties()
{
	ImGui::Text(name.c_str());
	ImGui::SameLine();
	ImGui::Checkbox("###Chromatic", &isEnabled);
	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}
		ImGui::Text("Aberration Amount");
		ImGui::SameLine();
		ImGui::InputFloat("###amount", &aberrationValue);
		ImGui::TreePop();
	}
	
}

void ChromaticEffect::SceneDraw()
{
}
