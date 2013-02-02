#include "BaseEntity.h"

static unsigned int nextID = 0;

BaseEntity::BaseEntity()
{
	position = Vector3D<float>(0.0f);
	orientation = Vector3D<float>(0.0f);
	ID = nextID++;
}

BaseEntity::BaseEntity(unsigned int id)
{
	position = Vector3D<float>(0.0f);
	orientation = Vector3D<float>(0.0f);
	ID = id;
}

BaseEntity::~BaseEntity()
{
}

void BaseEntity::SetPosition(Vector3D<float> pos)
{
	position = pos;
}

Vector3D<float> BaseEntity::GetPosition()
{
	return position;
}

void BaseEntity::SetOrientation(Vector3D<float> orient)
{
	orientation = orient;
}

Vector3D<float> BaseEntity::GetOrientation()
{
	return orientation;
}

unsigned int BaseEntity::GetID()
{
	return ID;
}

unsigned int BaseEntity::GetLastID()
{
	return nextID - 1;
}