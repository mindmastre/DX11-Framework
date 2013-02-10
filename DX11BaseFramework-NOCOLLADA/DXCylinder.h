#pragma once
#include "Common\DX11App.h"
#include "Common\GeometryGenerator.h"
#include "Vertex.h"
#include "DXEffect.h"
#include "DX11Camera.h"

class DXCylinder
{
	ID3D11Buffer* mCylinderVB;
	ID3D11Buffer* mCylinderIB;

	Material mCylinderMat;

	XMFLOAT4X4 mTexTransform;
	XMFLOAT4X4 mCylinderWorld;
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 mRotation;
	ID3D11ShaderResourceView* cylinderDiffuseTexture;

	int mCylinderVertexOffset;
	UINT mCylinderIndexOffset;
	UINT mCylinderIndexCount;
public:
	DXCylinder(ID3D11Device* md3dDevice, LPCWSTR texturePath);
	~DXCylinder();
	void BuildBuffers(ID3D11Device* md3dDevice);
	void DrawCylinder(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam);
	void SetScale(Vector3 scale);
	void SetPosition(Vector3 pos);
	void SetRotation(Vector3 rot);
	Vector3 GetScale();
	Vector3 GetPosition();
	Vector3 GetRotation();
};