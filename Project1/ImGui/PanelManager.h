#pragma once
#include "../ImGui/BasePanel.h"
#include "../ImGui/Hierarchy.h"
#include "../ImGui/Inspector.h"
#include <iostream>



class PanelManager
{

public:

	void StartImGuiPanels(GLFWwindow* window);
	void DrawImGuiPanels();
	void RenderImguiPanels();
	void EndImGuiPanels();

	void DrawDockSpace();

private:

	BasePanel* hierarchyPanel = new Hierarchy();
	BasePanel* InspectorPanel = new Inspector();

	bool dockOpen = true;

};

