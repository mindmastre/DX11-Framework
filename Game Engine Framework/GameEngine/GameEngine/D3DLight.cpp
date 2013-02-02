#include "D3DLight.h"

D3DLight::D3DLight()
{
}

D3DLight::~D3DLight()
{
}

void D3DLight::SetDiffuseColor(float red, float green, float blue, float alpha)
{
	diffuseColor = D3DXVECTOR4(red, green, blue, alpha);
}

void D3DLight::SetDirection(float x, float y, float z)
{
	direction = D3DXVECTOR3(x, y, z);
}

D3DXVECTOR4 D3DLight::GetDiffuseColor()
{
	return diffuseColor;
}

D3DXVECTOR3 D3DLight::GetDirection()
{
	return direction;
}