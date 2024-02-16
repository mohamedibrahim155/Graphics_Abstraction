#include "PixelizationEffect.h"
#include "../Time.h"
PixelizationEffect::PixelizationEffect()
{
	name = "Pixelization";
	
	InitializeEffect("Shaders/PostProcessing/Pixelization.vert", "Shaders/PostProcessing/Pixelization.frag");
}


void PixelizationEffect::DrawProperties()
{
	SinglePassEffect::DrawProperties();

	if (isEnabled)
	{
		if (!ImGui::TreeNodeEx("properties", ImGuiTreeNodeFlags_DefaultOpen))
		{
			return;
		}
		ImGui::TreePop();
	}
}

void PixelizationEffect::SceneDraw()
{
}

void PixelizationEffect::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());
}

void PixelizationEffect::SetShaderUniforms()
{
	shader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	shader->setFloat("time", time);
}
