#pragma once
#include "Common\dx11Util.h"
#include "Texture.h"

using namespace std;

class Billboard
{
private:
	struct BillboardVertex
	{
		Vector3 position;
	    Vector2 texture;
	};

	struct BillboardInfo
	{
		float x, y, z;
		float tu, tv;
		float nx, ny, nz;
	};

public:
	Billboard();
	Billboard(const Billboard&);
	~Billboard();

	bool Initialize(ID3D11Device*, char*, WCHAR*);
	void Cleanup();
	void Render(ID3D11DeviceContext*);

	int GetIndexCount();
	ID3D11ShaderResourceView* GetTexture();


private:
	bool InitializeBuffers(ID3D11Device*);
	void CleanupBuffers();
	void RenderBuffers(ID3D11DeviceContext*);

	bool LoadTexture(ID3D11Device*, WCHAR*);
	void ReleaseTexture();

	bool LoadModel(char*);
	void ReleaseModel();

private:
	ID3D11Buffer *vertexBuffer, *indexBuffer;
	int vertexCount, indexCount;
	Texture* texture;
	BillboardInfo* m_model;
};
