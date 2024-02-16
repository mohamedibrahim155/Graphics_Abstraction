#include "PixelizationEffect.h"
#include "../Time.h"
PixelizationEffect::PixelizationEffect()
{
	name = "Pixelization";
	
	InitializeEffect();
}

void PixelizationEffect::InitializeEffect()
{
	pixelShader = new Shader("Shaders/PostProcessing/Pixelization.vert", "Shaders/PostProcessing/Pixelization.frag");

}

void PixelizationEffect::ApplyEffect(FrameBuffer* frameBuffer)
{
	
	time += Time::GetInstance().deltaTime;
	frameBuffer->Bind();

	pixelShader->Bind();

	GLCALL(glActiveTexture(GL_TEXTURE0));
	pixelShader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	//pixelShader->setFloat("aberration", aberrationValue);   // abreation
	pixelShader->setFloat("time", time);  
	GLCALL(glBindTexture(GL_TEXTURE_2D, frameBuffer->GetColorAttachmentID(1)));

	Quad::GetInstance().RenderQuad();
	pixelShader->Unbind();

	frameBuffer->Unbind();
	
}

void PixelizationEffect::DrawProperties()
{
	ImGui::Text(name.c_str());
	ImGui::SameLine();
	ImGui::Checkbox("###pixelization", &isEnabled);
	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}
		//ImGui::Text("Aberration Amount");
		//ImGui::SameLine();
		//ImGui::InputFloat("###amount", &aberrationValue);
		ImGui::TreePop();
	}
}

void PixelizationEffect::SceneDraw()
{
}
