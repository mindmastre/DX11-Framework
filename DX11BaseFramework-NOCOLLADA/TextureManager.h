#pragma once

//The purpose of the texture manager is to prevent multiple copies of textures being loaded
//this is for memory efficiency purposes

#include "Texture.h"
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
	Texture* GetTexture(std::string);

private:
	std::vector<Texture*> textures;
	std::map<std::string, Texture*> textureMap;
};

extern TextureManager* textureManager;