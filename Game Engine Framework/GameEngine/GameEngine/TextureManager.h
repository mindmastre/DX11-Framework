#ifndef TEXTUREMANAGER_H
#define TEXTUREMANAGER_H

//The purpose of the texture manager is to prevent multiple copies of textures being loaded
//this is for memory efficiency purposes

#include "D3DTexture.h"
#include <map>
#include <vector>
#include <string>

class TextureManager
{
public:
	TextureManager();
	~TextureManager();

	void Shutdown();
	bool LoadTexture(ID3D11Device*, WCHAR*, std::string);
	void ReleaseTexture(std::string);
	D3DTexture* GetTexture(std::string);

private:
	std::vector<D3DTexture*> textures;
	std::map<std::string, D3DTexture*> textureMap;
};

extern TextureManager* textureManager;

#endif