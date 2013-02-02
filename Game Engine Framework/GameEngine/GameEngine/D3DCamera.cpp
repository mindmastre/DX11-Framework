#include "D3DCamera.h"

D3DCamera::D3DCamera()
{
	positionX = 0.0f;
	positionY = 0.0f;
	positionZ = 0.0f;

	rotationX = 0.0f;
	rotationY = 0.0f;
	rotationZ = 0.0f;
}

D3DCamera::~D3DCamera()
{
}

void D3DCamera::SetPosition(float x, float y, float z)
{
	positionX = x;
	positionY = y;
	positionZ = z;
}

void D3DCamera::SetRotation(float x, float y, float z)
{
	rotationX = x;
	rotationY = y;
	rotationZ = z;
}

D3DXVECTOR3 D3DCamera::GetPosition()
{
	return D3DXVECTOR3(positionX, positionY, positionZ);
}

D3DXVECTOR3 D3DCamera::GetRotation()
{
	return D3DXVECTOR3(rotationX, rotationY, rotationZ);
}

void D3DCamera::Render()
{
	D3DXVECTOR3 up, position, lookAt;
	float yaw, pitch, roll;
	D3DXMATRIX rotationMatrix;

	up.x = 0.0f;
	up.y = 1.0f;
	up.z = 0.0f;

	position.x = positionX;
	position.y = positionY;
	position.z = positionZ;

	lookAt.x = 0.0f;
	lookAt.y = 0.0f;
	lookAt.z = 1.0f;

	pitch = rotationX * 0.0174532925f;
	yaw = rotationY * 0.0174532925f;
	roll = rotationZ * 0.0174532925f;

	D3DXMatrixRotationYawPitchRoll(&rotationMatrix, yaw, pitch, roll);

	D3DXVec3TransformCoord(&lookAt, &lookAt, &rotationMatrix);
	D3DXVec3TransformCoord(&up, &up, &rotationMatrix);

	lookAt = position + lookAt;

	D3DXMatrixLookAtLH(&viewMatrix, &position, &lookAt, &up);
}

void D3DCamera::GetViewMatrix(D3DXMATRIX& view)
{
	view = viewMatrix;
}