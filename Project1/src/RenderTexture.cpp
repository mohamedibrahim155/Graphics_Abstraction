#include "RenderTexture.h"

void RenderTexture::Bind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, framebuffer->GetRendererID()));
}

void RenderTexture::Unbind()
{
	GLCALL(glBindTexture(GL_TEXTURE_2D, 0));
}

void RenderTexture::SetTextureSlot(int place)
{	
	GLCALL(glActiveTexture(GL_TEXTURE0 + place));
}

void RenderTexture::DrawProperties()
{
}

void RenderTexture::SceneDraw()
{
}
