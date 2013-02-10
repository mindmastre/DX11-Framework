#pragma once
#include <D3D11.h>
#include <D3DX10math.h>
#include "DXEffect.h"
#include <vector>
#include <fstream>
#include "DX11Camera.h"
#include "Texture.h"
#include "Common/GeometryGenerator.h"

///////////////////////////////////////
//             Model Data
///////////////////////////////////////

//struct MD5Vertex
//{
//	D3DXVECTOR3 position;
//	D3DXVECTOR3 normal;
//	D3DXVECTOR2 texture;
//	int StartWeight;
//	int WeightCount;
//};

struct Joint
{
	std::wstring name;
	int parentID;

	D3DXVECTOR3 position;
	D3DXVECTOR4 orientation;
};

struct Weight
{
	int jointID;
	float bias;
	D3DXVECTOR3 position;
	D3DXVECTOR3 normal;
};

struct ModelSubset
{
	int texArrayIndex;
	int numTriangles;

	std::vector<Vertex::Basic32> vertices;
	std::vector<XMFLOAT3> jointSpaceNormals;
	std::vector<UINT> indices;
	std::vector<Weight> weights;

	std::vector<XMFLOAT3> positions;
	std::vector<GeometryGenerator> geometries;
	ID3D11Buffer* vertexBuffer;
	ID3D11Buffer* indexBuffer;
};

///////////////////////////////////////
//          Animation Data
///////////////////////////////////////

struct BoundingBox
{
	D3DXVECTOR3 min;
	D3DXVECTOR3 max;
};

struct FrameData
{
	int frameID;
	std::vector<float> frameData;
};

struct AnimJointInfo
{
	std::wstring name;
	int parentID;

	int flags;
	int startIndex;
};

struct ModelAnimation
{
	int numFrames;
	int numJoints;
	int frameRate;
	int numAnimatedComponents;

	float frameTime;
	float totalAnimTime;
	float currAnimTime;

	std::vector<AnimJointInfo> jointInfo;
	std::vector<BoundingBox> frameBounds;
	std::vector<Joint> baseFrameJoints;
	std::vector<FrameData> frameData;
	std::vector<std::vector<Joint>> frameSkeleton;
};

///////////////////////////////////////
//           D3DModel Class
///////////////////////////////////////

class D3DModel
{
public:
	D3DModel();
	D3DModel(unsigned int);
	~D3DModel();
	std::vector<UINT> m_vIndices;
	std::vector<XMFLOAT3> m_vPositions;
	std::vector<XMFLOAT3> m_vNormals;
	std::vector<XMFLOAT2> m_vUV;
	void LoadTexture(Texture*);
	bool LoadModel(ID3D11Device*, std::wstring);
	bool LoadAnimation(std::wstring);
	void Shutdown();
	void Update(ID3D11DeviceContext*, float, int = 0);
	unsigned int GetID();

	int GetNumSubsets();
	std::vector<ModelSubset> GetSubsets();
	ID3D11ShaderResourceView* GetTexture();
	void RenderModel(ID3D11DeviceContext* deviceContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam);
	XMFLOAT4X4 mSphereWorld;
	Vector3 mPosition;
	Vector3 mScale;
	Vector3 mRotation;
	XMFLOAT4X4 mTexTransform;
	Material mBoxMat;
	ID3D11ShaderResourceView* normalTexture;

	void ToggleScattering();
	void ToggleSobel();
	void ToggleFog();
	void ToggleCelShading();
	void ToggleGlitter();
	void ToggleGlass();
private:
	bool InitializeBuffers(ID3D11Device*, ModelSubset&);
	void ShutdownBuffers();

	void ReleaseTexture();

	int numSubsets;
	int numJoints;

	std::vector<Joint> joints;
	std::vector<ModelSubset> subsets;

	std::vector<ModelAnimation> animations;

	Texture* texture;

	bool staticMesh;
	unsigned int ID;

	bool ScatteringFlag;
	bool SobelFlag;
	bool CelShadingFlag;
	bool FogFlag;
	bool GlitterFlag;
	bool GlassFlag;
};
