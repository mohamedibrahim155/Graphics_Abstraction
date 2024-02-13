#pragma once
#include "BaseTexture.h"
#include "FrameBuffer.h"
class RenderTexture : public BaseTexture
{
public:

	RenderTexture() = default;

	// Inherited via BaseTexture
	void Bind() override;
	void Unbind() override;
	void SetTextureSlot(int place = 0) override;
	void DrawProperties() override;
	void SceneDraw() override;

	FrameBuffer* framebuffer = nullptr;
};

