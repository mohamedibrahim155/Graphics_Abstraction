#pragma once

#include "../Object.h"

#include "Heirachy.h"
#include "Inspector.h"
#include "WindowDockingPanel.h"

class EditorLayout
{
public :
	static EditorLayout& GetInstance();

	Object* GetCurrentSelectedObject();

	void SetSelectedObject(Object* object);

	void InitializeEditors();


private:

	Heirachy* hierarchyPanel;
	Inspector* inspectorPanel;
	WindowDockingPanel* windowDockingPanel;

	Object* currentSelectedObject = nullptr;

};

