#pragma once
#include "BaseEffect.h"
#include "../Shader.h"
#include "../Quad.h"
class PixelizationEffect : public BaseEffect
{
public:
	PixelizationEffect();

	void InitializeEffect();
	// Inherited via BaseEffect
	void ApplyEffect(FrameBuffer* frameBuffer) override;
	void DrawProperties() override;
	void SceneDraw() override;

	Shader* pixelShader;

private :

	float time = 0;
	Quad quad;
};

