#pragma once

#include "../Object.h"
#include <vector>
#include "Heirachy.h"
#include "Inspector.h"
#include "WindowDockingPanel.h"
#include "SceneViewportPanel.h"
#include "ToolPanel.h"
class ApplicationRenderer;
class EditorLayout
{
public :
	static EditorLayout& GetInstance();

	Object* GetCurrentSelectedObject();


	void InitializeEditors();

	void SetSelectedObjects(std::vector<Object*> objects);
	void SetSelectedObjectsEnable(bool isEnable);

	std::vector<Object*> GetSelectedObjects();
	

	ApplicationRenderer* applicationRenderer;
private:

	Heirachy* hierarchyPanel;
	Inspector* inspectorPanel;
	WindowDockingPanel* windowDockingPanel;
	SceneViewportPanel* sceneViewportPanel;
	ToolPanel* toolPanel;

	Object* currentSelectedObject = nullptr;

	std::vector<Object*> selectedObjectsList;

};

