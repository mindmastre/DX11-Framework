#include "EntityManager.h"

EntityManager* entityManager = 0;

EntityManager::EntityManager()
{
	LastID = 0;
}

EntityManager::~EntityManager()
{
}

unsigned int EntityManager::CreateEntity()
{
	BaseEntity* temp;
	if(unusedIDs.empty())
	{
		temp = new BaseEntity();
	}
	else
	{
		temp = new BaseEntity(unusedIDs[0]);
		unusedIDs.erase(unusedIDs.begin());
	}
	entities.push_back(temp);
	entityMap.insert(std::pair<unsigned int, BaseEntity*>(temp->GetID(), temp));
	LastID = temp->GetLastID();
	return temp->GetID();
}

unsigned int EntityManager::CreateEntity(Vector3D<float> pos, Vector3D<float> orient)
{
	unsigned int temp = CreateEntity();
	SetEntityPosition(temp, pos);
	SetEntityOrientation(temp, orient);
	return temp;
}

void EntityManager::DeleteEntity(unsigned int ID)
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		if(entityMap[ID] == entities[i])
		{
			entities.erase(entities.begin() + i);
		}
	}
	delete entityMap[ID];
	entityMap[ID] = 0;
	entityMap.erase(ID);
	unusedIDs.push_back(ID);
}

void EntityManager::ClearEntityManager()
{
	for(unsigned int i = 0; i < entities.size(); i++)
	{
		delete entities[i];
		entities[i] = 0;
	}
	entities.clear();
	entityMap.clear();
	unusedIDs.clear();
}

void EntityManager::SetEntityPosition(unsigned int ID, Vector3D<float> pos)
{
	entities[ID]->SetPosition(pos);
}

Vector3D<float> EntityManager::GetEntityPosition(unsigned int ID)
{
	return entities[ID]->GetPosition();
}

void EntityManager::SetEntityOrientation(unsigned int ID, Vector3D<float> orient)
{
	entities[ID]->SetOrientation(orient);
}

Vector3D<float> EntityManager::GetEntityOrientation(unsigned int ID)
{
	return entities[ID]->GetOrientation();
}

BaseEntity* EntityManager::GetEntity(unsigned int ID)
{
	return entities[ID];
}

unsigned int EntityManager::GetLastID()
{
	return LastID;
}