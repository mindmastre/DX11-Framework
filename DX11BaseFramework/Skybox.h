#pragma once
#include "Common\dx11Util.h"

class DX11Camera;

class Skybox
{
public:
	Skybox(ID3D11Device* device, const std::wstring& cubemapFilename, float skySphereRadius);
	~Skybox();

	ID3D11ShaderResourceView* CubeMapSRV();

	void Draw(ID3D11DeviceContext* dc, const DX11Camera& camera);

private:
	Skybox(const Skybox& rhs);
	Skybox& operator=(const Skybox& rhs);

	ID3D11Buffer* mVB;
	ID3D11Buffer* mIB;

	ID3D11ShaderResourceView* mCubeMapSRV;

	UINT mIndexCount;
};
