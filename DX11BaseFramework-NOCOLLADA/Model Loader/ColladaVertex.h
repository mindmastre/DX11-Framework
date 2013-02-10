#pragma once
#include "../Common/DX11App.h"

//VERTEX STRUCTURE 
//Resource for this code was from Celal Cansin Kayi www.thecansin.com
class ColladaVertex
{
public:
	//Vertex Data
 	XMFLOAT3 m_vPosition;
	XMFLOAT3 m_vNormal;
	XMFLOAT2 m_vUV;
	XMFLOAT4 m_vTangent;
	XMFLOAT4 m_vBinormals;

	//Constructor
	ColladaVertex(XMFLOAT3 Position, XMFLOAT2 UV, XMFLOAT3 Normal,XMFLOAT4 Tangent, XMFLOAT4 Binormals)
	{
		m_vPosition = Position;
		m_vNormal = Normal;
		m_vUV = UV;
		m_vTangent = Tangent;
		m_vBinormals = Binormals;
	}

	//static IDirect3DVertexDeclaration9* Decl;
	static ID3D11InputLayout* PosNormalTexTanSkinned;
};

class ColladaInputDesc
{
public:
	static const D3D11_INPUT_ELEMENT_DESC PosNormalTexTanSkinned[6];
};

struct VertexData
{
	XMFLOAT3 m_vPosition;
	XMFLOAT3 m_vNormal;
	XMFLOAT2 m_vUV;
	XMFLOAT4 m_vTangent;
	XMFLOAT4 m_vBinormals;
	int StartWeight;
	int WeightCount;
};

class ColladaInputLayouts
{
public:
	static void InitAll(ID3D11Device* device);
	static void DestroyAll();

	static ID3D11InputLayout* PosNormalTexTanSkinned;
};
