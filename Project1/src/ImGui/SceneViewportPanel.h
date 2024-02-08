#pragma once
#include "../FrameBuffer.h"
#include "BasePanel.h"
class SceneViewportPanel : public BasePanel
{
public:
	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;

	FrameBuffer* frameBuffer = nullptr;
};

