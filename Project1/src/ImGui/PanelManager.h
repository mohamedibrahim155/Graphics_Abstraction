#pragma once
#include "BasePanel.h"
#include "Hierarchy.h"
#include "Inspector.h"
#include <iostream>
#include <vector>



class PanelManager
{

public:

	static PanelManager& GetInstance();


	void DrawDockSpace();

	void AddPanel(BasePanel* panel);
	void RemovePanel(BasePanel* panel);
	void EnablePanel(BasePanel* panel);
	void DisablePanel(BasePanel* panel);

	void Update();

	void EditorsInitializate();


private:

	BasePanel* hierarchyPanel;
	BasePanel* InspectorPanel;

	bool dockOpen = true;


	std::vector<BasePanel*> listOfPanels;
};

