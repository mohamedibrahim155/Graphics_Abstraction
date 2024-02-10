#include "EditorLayout.h"
#include "../ApplicationRenderer.h"

EditorLayout& EditorLayout::GetInstance()
{
    static EditorLayout editorInstance;

    return editorInstance;
}

Object* EditorLayout::GetCurrentSelectedObject()
{
    return currentSelectedObject;
}



void EditorLayout::InitializeEditors()
{
    windowDockingPanel = new WindowDockingPanel();
    hierarchyPanel = new Heirachy();
    inspectorPanel = new Inspector();
    sceneViewportPanel = new SceneViewportPanel();
  

    sceneViewportPanel->frameBuffer = applicationRenderer->frameBuffer;
    sceneViewportPanel->sceneViewportCamera = applicationRenderer->camera;

    toolPanel = new ToolPanel();
    toolPanel->isApplicationPlayMode = &applicationRenderer->isPlayMode;
}

void EditorLayout::SetSelectedObjects(std::vector<Object*> objects)
{
    if (!selectedObjectsList.empty())
    {
        SetSelectedObjectsEnable(false);
    }

    selectedObjectsList.clear();

    selectedObjectsList = objects;

    SetSelectedObjectsEnable(true);

}

void EditorLayout::SetSelectedObjectsEnable(bool isEnable)
{
    for (Object* object:  selectedObjectsList)
    {
        object->isEnabled = isEnable;
    }
}

std::vector<Object*> EditorLayout::GetSelectedObjects()
{
    return selectedObjectsList;
}
