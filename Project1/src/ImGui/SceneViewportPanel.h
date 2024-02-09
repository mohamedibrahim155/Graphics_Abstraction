#pragma once
#include "../FrameBuffer.h"
#include "BasePanel.h"
#include "../Camera.h"
class SceneViewportPanel : public BasePanel
{
public:
	// Inherited via BasePanel
	void OnRender(float windowWidth, float windowHeight) override;

	FrameBuffer* frameBuffer = nullptr;

	ImVec2 viewportSize;

	Camera* sceneViewportCamera;
};

