#pragma once
#include "BaseEffect.h"
#include "../Quad.h"
class SinglePassEffect : public BaseEffect
{
public:
	SinglePassEffect();

	virtual ~SinglePassEffect() {  };

	
	virtual void InitializeEffect(const std::string& vertex, const std::string& fragment) = 0;
	// Inherited via BaseEffect
	virtual void ApplyEffect(FrameBuffer* frameBuffer);
	virtual void DrawProperties();
	virtual void SceneDraw();

	virtual void SetShaderUniforms() = 0;

	Shader* shader;

	float time;
};

