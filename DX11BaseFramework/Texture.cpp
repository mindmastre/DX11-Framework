#include "texture.h"


Texture::Texture()
{
	texture = 0;
}


Texture::Texture(const Texture& other)
{
}


Texture::~Texture()
{
}


bool Texture::Initialize(ID3D11Device* device, WCHAR* filename)
{
	HRESULT result;


	// Load the texture in.
	result = D3DX11CreateShaderResourceViewFromFile(device, filename, NULL, NULL, &texture, NULL);
	if(FAILED(result))
	{
		return false;
	}

	return true;
}


void Texture::Cleanup()
{
	// Release the texture resource.
	if(texture)
	{
		texture->Release();
		texture = 0;
	}

	return;
}


ID3D11ShaderResourceView* Texture::GetTexture()
{
	return texture;
}