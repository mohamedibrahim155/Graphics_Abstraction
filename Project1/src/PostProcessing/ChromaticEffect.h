#pragma once
#include "BaseEffect.h"
#include "../Shader.h"
#include "../Quad.h"


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
private:

	Quad quad;
	float aberrationValue = 10;
	float time = 0;

};

