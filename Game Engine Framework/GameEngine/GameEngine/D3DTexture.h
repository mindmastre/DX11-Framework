#ifndef D3DTEXTURE_H
#define D3DTEXTURE_H

#include <D3D11.h>
#include <D3DX11tex.h>

class D3DTexture
{
public:
	D3DTexture();
	~D3DTexture();

	bool Initialize(ID3D11Device*, WCHAR*);
	void Shutdown();

	ID3D11ShaderResourceView* GetTexture();

private:
	ID3D11ShaderResourceView* texture;
};

#endif