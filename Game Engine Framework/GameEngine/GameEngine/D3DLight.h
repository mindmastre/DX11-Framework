#ifndef D3DLIGHT_H
#define D3DLIGHT_H

#include <D3DX10math.h>

class D3DLight
{
public:
	D3DLight();
	~D3DLight();

	void SetDiffuseColor(float, float, float, float);
	void SetDirection(float, float, float);

	D3DXVECTOR4 GetDiffuseColor();
	D3DXVECTOR3 GetDirection();

private:
	D3DXVECTOR4 diffuseColor;
	D3DXVECTOR3 direction;
};

#endif