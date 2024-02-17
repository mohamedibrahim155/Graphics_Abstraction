#include "SceneViewportPanel.h"
#include "../GraphicsRender.h"
#include "../Math.h"
void SceneViewportPanel::OnRender(float windowWidth, float windowHeight)
{
   // isEnable = false;
    if (!isPanelOpen)
    {
        return;
    }

    glm::mat4 cameraView = sceneViewportCamera->GetViewMatrix();
    glm::mat4 cameraProjection = sceneViewportCamera->GetProjectionMatrix();

    ImGuizmo::SetOrthographic(false);

    ImGui::PushStyleVar(ImGuiStyleVar_WindowPadding, ImVec2(0, 0));

    if (!ImGui::Begin("SceneView", &isPanelOpen) || !isEnable)
    {
        ImGui::End();
        ImGui::PopStyleVar();
        return;

    }

    ImVec2 viewPortPanelSize = ImGui::GetContentRegionAvail();

    isHovered = ImGui::IsWindowHovered();

    if (viewportSize.x!= viewPortPanelSize.x ||viewportSize.y !=viewPortPanelSize.y)
    {
        viewportSize = viewPortPanelSize;

        frameBuffer->Resize(viewportSize.x, viewportSize.y);
        sceneViewportCamera->Resize(viewportSize.x, viewportSize.y);
    }
   



    Model* selectedModel = GraphicsRender::GetInstance().GetSelectedModel();

    if (selectedModel != nullptr)
    {
       
        ImGuizmo::SetDrawlist();

        float windowWidth = (float)ImGui::GetWindowWidth();
        float windowHeight = (float)ImGui::GetWindowHeight();

        ImGuizmo::SetRect(ImGui::GetWindowPos().x, ImGui::GetWindowPos().y, windowWidth, windowHeight);


        glm::mat4 transform = selectedModel->transform.GetModelMatrix();

        ImGuizmo::Manipulate(glm::value_ptr(cameraView), glm::value_ptr(cameraProjection),
            ImGuizmo::OPERATION::TRANSLATE, ImGuizmo::LOCAL, glm::value_ptr(transform));

        if (ImGuizmo::IsUsing())
        {
            glm::vec3 position, rotation, scale;
            MathUtils::Math::DecomposeTransform(transform, position, rotation, scale);

            selectedModel->transform.SetPosition(position);
            selectedModel->transform.SetScale(scale);
        }

    }
  




    ImGui::Image((void*)frameBuffer->GetColorAttachmentID(), viewportSize, ImVec2(0, 1), ImVec2(1, 0));

    ImGui::End();

    ImGui::PopStyleVar();



}
