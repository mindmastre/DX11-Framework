#pragma once
#include "Common\DX11App.h"
#include "Common\GeometryGenerator.h"
#include "Vertex.h"
#include "DXEffect.h"
#include "DX11Camera.h"

class DXPyramid
{
	ID3D11Buffer* mPyramidVB;
	ID3D11Buffer* mPyramidIB;

	Material mPyramidMat;

	XMFLOAT4X4 mTexTransform;
	XMFLOAT4X4 mPyramidWorld;
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 mRotation;
	ID3D11ShaderResourceView* pyramidDiffuseTexture;

	int mPyramidVertexOffset;
	UINT mPyramidIndexOffset;
	UINT mPyramidIndexCount;
public:
	DXPyramid(ID3D11Device* md3dDevice, LPCWSTR texturePath);
	~DXPyramid();
	void BuildBuffers(ID3D11Device* md3dDevice);
	void DrawPyramid(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam);
	void SetScale(Vector3 scale);
	void SetPosition(Vector3 pos);
	void SetRotation(Vector3 rot);
	Vector3 GetScale();
	Vector3 GetPosition();
	Vector3 GetRotation();
};