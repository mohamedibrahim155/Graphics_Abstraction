#include "Heirachy.h"
#include "../EntityManager/EntityManager.h"
Heirachy::Heirachy()
{
    entityManager = &EntityManager::GetInstance();
}

void Heirachy::OnRender(float windowWidth, float windowHeight)
{

    
    if (!isPanelOpen)
    {
        return;
    }

    if  (!ImGui::Begin("Hierarchy",&isPanelOpen) || !isEnable)
    {
        ImGui::End();
        return;
    }

    ShowAllEntities();

    ImGui::End();

    

}

void Heirachy::ShowAllEntities()
{
    if (!ImGui::CollapsingHeader("Entities", ImGuiTreeNodeFlags_DefaultOpen))
    {
        return;
    }

    std::unordered_map<std::string, Entity*>::iterator it;

    for (it = entityManager->listOfEntities.begin(); it != entityManager->listOfEntities.end(); ++it)
    {
        it->second->SceneDraw();
    }
}
