#include "Inspector.h"
#include "EditorLayout.h"
void Inspector::OnRender(float windowWidth, float windowHeight)
{
    if (!isEnable)
    {
        return;
    }

    windowWidth = 400;
    windowHeight = 400;

    if (!ImGui::Begin("Inspector", &isEnable))
    {
       
        ImGui::End();
        return;

    }
   
    ImGui::SetWindowSize(ImVec2(windowWidth, windowHeight));
   
    DrawProperties();

    ImGui::End();
}

void Inspector::DrawProperties()
{
    std::vector<Object*> selectedObjects = EditorLayout::GetInstance().GetSelectedObjects();

    if (selectedObjects.size() == 0) return;

    for (Object* obj : selectedObjects)
    {
        obj->OnPropertyDraw();
    }
}
