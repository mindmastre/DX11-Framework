#ifndef D3DCONVERTUTIL_H
#define D3DCONVERTUTIL_H

#include "Vector2D.h"
#include "Vector3D.h"
#include "Quaternion.h"
#include "Matrix4D.h"
#include <D3DX10math.h>

struct D3DConverter
{
	D3DXVECTOR2 Convert(Vector2D<float> rhs)
	{
		return D3DXVECTOR2(rhs.x, rhs.y);
	}
	D3DXVECTOR3 Convert(Vector3D<float> rhs)
	{
		return D3DXVECTOR3(rhs.x, rhs.y, rhs.z);
	}
	D3DXQUATERNION Convert(Quaternion<float> rhs)
	{
		return D3DXQUATERNION(rhs.x, rhs.y, rhs.z, rhs.w);
	}
	D3DXMATRIX Convert(Matrix4D<float> rhs)
	{
		return D3DXMATRIX(rhs[0], rhs[1], rhs[2], rhs[3],
						  rhs[4], rhs[5], rhs[6], rhs[7],
						  rhs[8], rhs[9], rhs[10], rhs[11],
						  rhs[12], rhs[13], rhs[14], rhs[15]);
	}
};

#endif