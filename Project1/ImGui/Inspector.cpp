#include "Inspector.h"

void Inspector::Draw()
{

    {

        ImGui::Begin("Inspector");
        ImGui::SetWindowSize(ImVec2(400, 400));
        ImGui::Text("Add Something");
        ImGui::End();

    }
}
