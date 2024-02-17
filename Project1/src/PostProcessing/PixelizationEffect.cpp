#include "PixelizationEffect.h"
#include "../Time.h"
PixelizationEffect::PixelizationEffect()
{
	name = "Pixelization";
	
	InitializeEffect("Shaders/PostProcessing/Pixelization.vert", "Shaders/PostProcessing/Pixelization.frag");
}

PixelizationEffect::PixelizationEffect(float width, float height)
{
	name = "Pixelization";

	framebufferWidthAndHeight.x = width;
	framebufferWidthAndHeight.y = height;

	InitializeEffect("Shaders/PostProcessing/Pixelization.vert", "Shaders/PostProcessing/Pixelization.frag");
}

void PixelizationEffect::InitializeEffect(const std::string& vertex, const std::string& fragment)
{
	shader = new Shader(vertex.c_str(), fragment.c_str());

	FrameBufferSpecification specification;

	specification.width = 1920;
	specification.height = 1080;

	specification.attachments = { FramebufferTextureFormat::RGBA8, FramebufferTextureFormat::DEPTH };

	singlepassFramebuffer = new FrameBuffer(specification);
}

void PixelizationEffect::SetShaderUniforms()
{
	shader->setInt("sceneTexture", 0);  // Scene texture from framebuffer
	shader->setFloat("time", time);
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



