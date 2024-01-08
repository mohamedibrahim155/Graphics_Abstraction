#pragma once
#include "Shader.h"

class Material;

class BaseMaterial
{
public:
	
	virtual void UpdateMaterial(Shader* shader) = 0;
	virtual void ResetMaterial(Shader* shader) = 0;
	virtual BaseMaterial* DuplicateMaterial() = 0;

	Material* AsMaterial();

private:

};
