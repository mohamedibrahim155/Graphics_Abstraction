#include "Entity.h"
#include "EntityManager.h"

void Entity::InitializeEntity(Entity* entity)
{
	EntityManager::GetInstance().AddEntity(entity);
}
