#pragma once

#include "D3DModel.h"
#include "Common\dx11Util.h"
#include <fstream>
#include <string>
#include <map>

class ModelManager
{
public:
	ModelManager();
	~ModelManager();

	void Shutdown();

	int LoadModel(ID3D11Device*, std::wstring);
	bool LoadAnimation(unsigned int, std::wstring);
	void LoadTexture(unsigned int, std::string);
	void ReleaseModel(unsigned int);

	//use this function only to create a new instance of the model.
	//dont use this function to update this model, as it is
	//only a base for other instances. This will prevent performance loss
	//during load times when loading multiple objects of the same model type
	D3DModel* GetModel(unsigned int);

private:
	std::map<unsigned int, D3DModel*> modelMap;
	std::vector<D3DModel*> models;
	std::vector<unsigned int> unusedIDs;
};