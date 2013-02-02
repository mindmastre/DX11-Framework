#ifndef D3DCAMERA_H
#define D3DCAMERA_H

#include <D3DX10math.h>

class D3DCamera
{
public:
	D3DCamera();
	~D3DCamera();

	void SetPosition(float, float, float);
	void SetRotation(float, float, float);

	D3DXVECTOR3 GetPosition();
	D3DXVECTOR3 GetRotation();

	void Render();
	void GetViewMatrix(D3DXMATRIX&);

private:
	float positionX, positionY, positionZ;
	float rotationX, rotationY, rotationZ;
	D3DXMATRIX viewMatrix;
};

#endif