#ifndef BASEENTITY_H
#define BASEENTITY_H

#include "Vector3D.h"

class BaseEntity
{
public:
	BaseEntity();
	BaseEntity(unsigned int);
	~BaseEntity();

	void SetPosition(Vector3D<float>);
	Vector3D<float> GetPosition();

	void SetOrientation(Vector3D<float>);
	Vector3D<float> GetOrientation();

	unsigned int GetID();
	unsigned int GetLastID();

private:
	Vector3D<float> position;
	Vector3D<float> orientation;
	unsigned int ID;
};

#endif