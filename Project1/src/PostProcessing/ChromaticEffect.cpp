#include "ChromaticEffect.h"
#include "../Renderer.h"
#include"../Time.h"
#include "../GraphicsRender.h"
ChromaticEffect::ChromaticEffect()
{
	name = "Chromatic";
	//InitializeChromaticEffect();

	InitializeEffect("Shaders/PostProcessing/Chromatic.vert", "Shaders/PostProcessing/Chromatic.frag");
}

void ChromaticEffect::DrawProperties()
{
	SinglePassEffect::DrawProperties();

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

void ChromaticEffect::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

}

void ChromaticEffect::SetShaderUniforms()
{

	shader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	shader->setFloat("aberration", aberrationValue);   // abreation
	shader->setFloat("time", time);   // abreation


}
