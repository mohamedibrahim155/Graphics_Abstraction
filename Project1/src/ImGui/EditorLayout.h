#pragma once

#include "../Object.h"
#include <vector>
#include "Heirachy.h"
#include "Inspector.h"
#include "WindowDockingPanel.h"

class EditorLayout
{
public :
	static EditorLayout& GetInstance();

	Object* GetCurrentSelectedObject();


	void InitializeEditors();

	void SetSelectedObjects(std::vector<Object*> objects);
	void SetSelectedObjectsEnable(bool isEnable);

	std::vector<Object*> GetSelectedObjects();
	


private:

	Heirachy* hierarchyPanel;
	Inspector* inspectorPanel;
	WindowDockingPanel* windowDockingPanel;

	Object* currentSelectedObject = nullptr;

	std::vector<Object*> selectedObjectsList;

};

