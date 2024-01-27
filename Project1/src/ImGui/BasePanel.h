#pragma once
#include <imgui.h>
#include <imgui_impl_glfw.h>
#include <imgui_impl_opengl3.h>

class BasePanel
{
public:

	bool isPanelActive = true;
	bool isPanelOpen = true;


	BasePanel();
	virtual void OnRender(float windowWidth, float windowHeight) =0;


};


