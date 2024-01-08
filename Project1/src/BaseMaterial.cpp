#include "BaseMaterial.h"
#include "material.h"


Material* BaseMaterial::AsMaterial()
{
	return (Material*)this;
}
