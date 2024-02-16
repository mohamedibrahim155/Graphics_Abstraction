#include "PostProcessing.h"

PostProcessing::PostProcessing()
{
}

PostProcessing::~PostProcessing()
{
}

void PostProcessing::InitializePostProcessing()
{
	isPostProccesingEnabled = true;

	chromatic = new ChromaticEffect();

	AddEffect(chromatic);
}

void PostProcessing::ApplyPostprocessing(FrameBuffer* framebuffer)
{
	if (!isPostProccesingEnabled) return;

	for (BaseEffect* effect :  listOfeffects)
	{
		if (!effect->isEnabled) continue;

		effect->ApplyEffect(framebuffer);
	}
}

void PostProcessing::AddEffect(BaseEffect* effect)
{
	listOfeffects.push_back(effect);
}

void PostProcessing::RemoveEffect(BaseEffect* effect)
{
	std::vector<BaseEffect*> ::iterator it = std::remove(listOfeffects.begin(), listOfeffects.end(), effect);

	listOfeffects.erase(it, listOfeffects.end());
}
