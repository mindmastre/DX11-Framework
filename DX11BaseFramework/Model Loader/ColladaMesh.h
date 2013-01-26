#pragma once

//#include "BaseObject.h"
#include "../Common/dx11Util.h"
#include "ColladaModelLoader.h"
#include "ColladaVertex.h"
#include "../DX11MeshGeometry.h"
#include "../DX11Camera.h"
#include "../DXEffect.h"

using std::string;
using std::pair;
using std::make_pair;

//struct TweenInfo
//{
//	XMFLOAT3 m_vDestPos;
//	XMFLOAT3 m_vEndRotation;
//	XMFLOAT3 m_vEndScale;
//	float		m_fAlpha;
//	float		m_fAccumTime;
//	float		m_fAnimDuration;
//};

class ColladaMesh // : public BaseObject
{
	ID3D11Device* device;
	Material mBoxMat;
	Vector3 m_vPosition;
	Vector3 m_vRotation;
	/*Vector3 m_vScale;*/
	//this should not be this mesh type
	DX11MeshGeometry *m_Mesh;
	XMFLOAT4X4 mTexTransform;
	XMFLOAT4X4 m_mWorld;
public:
	Vector3 m_vScale;
	ColladaMesh(ID3D11Device* md3dDevice, string name);
	//ColladaMesh(const ColladaMesh& m);
	~ColladaMesh();
	void Update(float dt);
	void Render(ID3D11DeviceContext* dc,  ID3DX11EffectTechnique* activeTech, DX11Camera mCam);
	void LoadBuffers(daeElement *geometry);
	void LoadVertexBuffer(daeElement *mesh);
	void LoadIndexBuffer(daeElement *indices);
	void LoadTexture(string fileName);
	void ConvertToDirectX11();
	void OnResetDevice();
	void OnLostDevice();
	//void BuildFX();
	//void CalculateAABB();

	UINT SubsetCount;
	std::vector<DX11MeshGeometry::Subset> Subsets;
	//MUTATORS//
	//void SetTechnique(char* technique);
	void SetName(string name){m_sName = name;}
	//void SetFX(char* filename);
	void SetTexture(bool texture){m_bHasTexture = texture;}
	void SetAlpha(float alpha){m_fAlpha = alpha;}
	void SetPosition(Vector3& pos){m_vPosition = pos;}
	void SetScale(Vector3& scale) { m_vScale = scale; }
	void SetRotation(Vector3 rot) { m_vRotation = rot; }
	Vector3 GetScale() { return m_vScale; }
	Vector3 GetRotation() { return m_vRotation; }
	void RotateX(float x) { m_vRotation.SetX(x); }
	void RotateY(float y) { m_vRotation.SetX(y); }
	void RotateZ(float z) { m_vRotation.SetX(z); }
	void Transform();
	
	//ACCESSORS//
	DX11MeshGeometry* GetMesh(){return m_Mesh;}
	string			GetName(){return m_sName;}
	float			GetAlpha(){return m_fAlpha;}
	int				GetId(){return m_iMeshId;}	
	XMFLOAT4X4&		GetWorldMtx(){return m_mWorld;}
	Vector3&	GetPosition();
	//bool			IsTweening(){return m_bIsTweening;}
	
private:
	ID3D11ShaderResourceView* diffuseTexture;
	ID3D11ShaderResourceView* normalTexture;
	LPCWSTR textureName;
	//Mesh Name
	string m_sName;
	//Mesh Id
	int m_iMeshId;
	//Effect interface
	ID3D11ShaderResourceView* mhTex;
	//Technique Handle
	ID3D11ShaderResourceView* mhTech;
	bool m_bHasTexture;
	//AABB Box for collision detection
	//AABB m_AABB;
	//Alpha variable used to have transparency
	float m_fAlpha;

	//Effect Information
	//ID3DXEffect *m_fx;
	char* m_FxFile;
	char* m_FxTechnique;
	//World Space 
	//XMMATRIX m_mTranslation;
	//XMMATRIX m_mRotation;
	//XMMATRIX m_mScale;
	//Mesh Vertices 
	std::vector<VertexData> m_vVertices;
	//Mesh Indices
	std::vector<UINT> m_vIndices;
	//Vectors of Vertex Information
	std::vector<XMFLOAT3> m_vPositions;
	std::vector<XMFLOAT3> m_vNormals;
	std::vector<XMFLOAT2> m_vUV;
	std::vector<XMFLOAT4> m_vTangents;
	std::vector<XMFLOAT4> m_vBinormals;
	//Tweening boolean
	//bool m_bIsTweening;
	//Tweening Information
	//TweenInfo   m_TweenData;
	//std::vector<TweenInfo>  m_TweenList;
	ID3D11Buffer* mBoxVB;
	ID3D11Buffer* mBoxIB;
};
