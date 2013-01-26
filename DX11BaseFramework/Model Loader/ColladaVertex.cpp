#include "ColladaVertex.h"
#include "../DXEffect.h"

const D3D11_INPUT_ELEMENT_DESC ColladaInputDesc::PosNormalTexTanSkinned[6] = 
{
	{"POSITION",     0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 0,  D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"NORMAL",       0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 12, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TEXCOORD",     0, DXGI_FORMAT_R32G32_FLOAT,    0, 24, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"TANGENT",      0, DXGI_FORMAT_R32G32B32A32_FLOAT, 0, 32, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"WEIGHTS",      0, DXGI_FORMAT_R32G32B32_FLOAT, 0, 48, D3D11_INPUT_PER_VERTEX_DATA, 0},
	{"BONEINDICES",  0, DXGI_FORMAT_R8G8B8A8_UINT,   0, 60, D3D11_INPUT_PER_VERTEX_DATA, 0}
};

//IDirect3DVertexDeclaration9* Vertex::Decl = 0;
ID3D11InputLayout* ColladaInputLayouts::PosNormalTexTanSkinned = 0;

void ColladaInputLayouts::InitAll(ID3D11Device* device)
{
	D3DX11_PASS_DESC passDesc;
	////Static Mesh 
	//D3DVERTEXELEMENT9 staticMeshElements[] =
	//{
	//	{0, 0, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
	//	{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
	//	{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
	//	{0, 32, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TANGENT, 0},
	//	{0, 44, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_BINORMAL, 0},D3DDECL_END()
	//};	
	//HR(gd3dDevice->CreateVertexDeclaration(staticMeshElements, &Vertex::Decl));
	Effects::BillboardFX->Light1Tech->GetPassByIndex(0)->GetDesc(&passDesc);
	HR(device->CreateInputLayout(ColladaInputDesc::PosNormalTexTanSkinned, 6, passDesc.pIAInputSignature, 
		passDesc.IAInputSignatureSize, &PosNormalTexTanSkinned));
}

void ColladaInputLayouts::DestroyAll()
{
	//ReleaseCOM(Vertex::Decl);
	ReleaseCOM(PosNormalTexTanSkinned);
}