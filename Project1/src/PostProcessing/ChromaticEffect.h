#pragma once
#include "BaseEffect.h"
#include "../Shader.h"
#include "../Quad.h"

class PostProcessing;
class ChromaticEffect : public BaseEffect
{
public :

	ChromaticEffect();
	~ChromaticEffect();
	void InitializeChromaticEffect();
	// Inherited via BaseEffect
	void ApplyEffect(FrameBuffer* frameBuffer) override;
	void DrawProperties() override;
	void SceneDraw() override;

	Shader* chromaticShader = nullptr;
	FrameBuffer* chromaticFramebuffer = nullptr;
	PostProcessing* postProcessing;
private:

	Quad quad;
	float aberrationValue = 0;

	float time = 0;

};

