#include "BaseMaterial.h"
#include "material.h"
#include "SkyboxMaterial.h"


Material* BaseMaterial::material()
{
	return (Material*)this;
}

SkyboxMaterial* BaseMaterial::skyboxMaterial()
{
	return (SkyboxMaterial*)this;
}
