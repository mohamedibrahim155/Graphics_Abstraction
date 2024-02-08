#include "SceneViewportPanel.h"

void SceneViewportPanel::OnRender(float windowWidth, float windowHeight)
{
   // isEnable = false;
    if (!isPanelOpen)
    {
        return;
    }

    //windowWidth = 400;
  //  windowHeight = 400;

    if (!ImGui::Begin("SceneView", &isPanelOpen) || !isEnable)
    {

        ImGui::End();
        return;

    }

    ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();

    ImVec2 imageSize(windowWidth, windowHeight);

    //if (frameBuffer == nullptr);
    //{
    //    ImGui::End();
    //    return;
    //}
    ImGui::Image((void*)frameBuffer->GetRendererID(), imageSize, ImVec2{ 0,1 }, ImVec2{ 1,0 });

    ImGui::End();



}
