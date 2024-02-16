#pragma once
//#include "BaseEffect.h"
#include "ChromaticEffect.h"
class PostProcessing
{
public:

	PostProcessing();
	~PostProcessing();
	void InitializePostProcessing();

	void ApplyPostprocessing(FrameBuffer* framebuffer);

	 void AddEffect(BaseEffect* effect);
     void RemoveEffect(BaseEffect* effect);
	 bool isPostProccesingEnabled = false;

private:

	std::vector<BaseEffect*> listOfeffects;

	ChromaticEffect* chromatic;


	
};

