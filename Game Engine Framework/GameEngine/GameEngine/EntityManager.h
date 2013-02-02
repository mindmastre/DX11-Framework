#ifndef ENTITYMANAGER_H
#define ENTITYMANAGER_H

#include <map>
#include <vector>
#include "Vector3D.h"
#include "BaseEntity.h"

class EntityManager
{
public:
	EntityManager();
	~EntityManager();

	unsigned int CreateEntity();
	unsigned int CreateEntity(Vector3D<float>, Vector3D<float>);
	void DeleteEntity(unsigned int);
	void ClearEntityManager();

	void SetEntityPosition(unsigned int, Vector3D<float>);
	Vector3D<float> GetEntityPosition(unsigned int);

	void SetEntityOrientation(unsigned int, Vector3D<float>);
	Vector3D<float> GetEntityOrientation(unsigned int);

	BaseEntity* GetEntity(unsigned int);
	unsigned int GetLastID();

private:
	std::map<unsigned int, BaseEntity*> entityMap;
	std::vector<BaseEntity*> entities;
	std::vector<unsigned int> unusedIDs;
	unsigned int LastID;
};

extern EntityManager* entityManager;

#endif