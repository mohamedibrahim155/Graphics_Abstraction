#include "ChromaticEffect.h"
#include "../Renderer.h"
#include "PostProcessing.h"
#include"../Time.h"
ChromaticEffect::ChromaticEffect()
{
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

	quad.RenderQuad();
	//chromaticShader->Unbind();

	frameBuffer->Unbind();

}

void ChromaticEffect::DrawProperties()
{
}

void ChromaticEffect::SceneDraw()
{
}
