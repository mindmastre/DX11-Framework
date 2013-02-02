#include "D3DTexture.h"

D3DTexture::D3DTexture()
{
	texture = 0;
}

D3DTexture::~D3DTexture()
{
}

bool D3DTexture::Initialize(ID3D11Device* device, WCHAR* fileName)
{
	HRESULT result;

	result = D3DX11CreateShaderResourceViewFromFile(device, fileName, NULL, NULL, &texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}

void D3DTexture::Shutdown()
{
	if(texture)
	{
		texture->Release();
		texture = 0;
	}
}

ID3D11ShaderResourceView* D3DTexture::GetTexture()
{
	return texture;
}