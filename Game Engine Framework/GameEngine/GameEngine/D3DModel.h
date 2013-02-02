#ifndef D3DMODEL_H
#define D3DMODEL_H

#include <D3D11.h>
#include <D3DX10math.h>

#include <vector>
#include <fstream>

#include "D3DTexture.h"

///////////////////////////////////////
//             Model Data
///////////////////////////////////////

struct Vertex
{
	D3DXVECTOR3 position;
	D3DXVECTOR2 texture;
	D3DXVECTOR3 normal;

	int StartWeight;
	int WeightCount;
};

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

	std::vector<Vertex> vertices;
	std::vector<D3DXVECTOR3> jointSpaceNormals;
	std::vector<DWORD> indices;
	std::vector<Weight> weights;

	std::vector<D3DXVECTOR3> positions;

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

	void LoadTexture(D3DTexture*);
	bool LoadModel(ID3D11Device*, std::wstring);
	bool LoadAnimation(std::wstring);
	void Shutdown();
	void Update(ID3D11DeviceContext*, float, int = 0);
	unsigned int GetID();

	int GetNumSubsets();
	std::vector<ModelSubset> GetSubsets();
	ID3D11ShaderResourceView* GetTexture();

private:
	bool InitializeBuffers(ID3D11Device*, ModelSubset&);
	void ShutdownBuffers();

	void ReleaseTexture();

	int numSubsets;
	int numJoints;

	std::vector<Joint> joints;
	std::vector<ModelSubset> subsets;

	std::vector<ModelAnimation> animations;

	D3DTexture* texture;

	bool staticMesh;
	unsigned int ID;
};

#endif