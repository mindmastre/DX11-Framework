#pragma once
#include "Common\DX11App.h"
#include "Common\GeometryGenerator.h"
#include "Vertex.h"
#include "DXEffect.h"
#include "DX11Camera.h"

class DXPlane
{
	ID3D11Buffer* mPlaneVB;
	ID3D11Buffer* mPlaneIB;

	Material mPlaneMat;

	XMFLOAT4X4 mTexTransform;
	XMFLOAT4X4 mPlaneWorld;
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 mRotation;
	ID3D11ShaderResourceView* planeDiffuseTexture;

	int mPlaneVertexOffset;
	UINT mPlaneIndexOffset;
	UINT mPlaneIndexCount;
public:
	DXPlane(ID3D11Device* md3dDevice, LPCWSTR texturePath);
	~DXPlane();
	void BuildBuffers(ID3D11Device* md3dDevice);
	void DrawPlane(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam);
	void SetScale(Vector3 scale);
	void SetPosition(Vector3 pos);
	void SetRotation(Vector3 rot);
	Vector3 GetScale();
	Vector3 GetPosition();
	Vector3 GetRotation();
};