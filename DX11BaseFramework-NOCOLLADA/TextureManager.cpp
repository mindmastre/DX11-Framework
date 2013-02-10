#include "TextureManager.h"

TextureManager* textureManager = 0;

TextureManager::TextureManager()
{
}

TextureManager::~TextureManager()
{
}

void TextureManager::Shutdown()
{
	for(unsigned int i = 0; i < textures.size(); i++)
	{
		textures[i]->Cleanup();
		delete textures[i];
		textures[i] = 0;
	}
	textures.clear();
	textureMap.clear();
}

bool TextureManager::LoadTexture(ID3D11Device* device, WCHAR* fileName, std::string referenceName)
{
	bool result;

	Texture* texture = new Texture();

	if(!texture)
	{
		return false;
	}

	result = texture->Initialize(device, fileName);
	if(!result)
	{
		return false;
	}

	textures.push_back(texture);
	textureMap.insert(std::pair<std::string, Texture*>(referenceName, texture));

	return true;
}

void TextureManager::ReleaseTexture(std::string referenceName)
{
	Texture* temp = textureMap[referenceName];

	for(unsigned int i = 0; i < textures.size(); i++)
	{
		if(temp == textures[i])
		{
			textures.erase(textures.begin() + i);
			break;
		}
	}

	temp->Cleanup();
	delete temp;
	temp = 0;

	textureMap.erase(referenceName);
}

Texture* TextureManager::GetTexture(std::string referenceName)
{
	return textureMap[referenceName];
}