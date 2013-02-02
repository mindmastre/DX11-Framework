#include "ModelManager.h"
#include "TextureManager.h"

ModelManager::ModelManager()
{
}

ModelManager::~ModelManager()
{
}

void ModelManager::Shutdown()
{
	for(unsigned int i = 0; i < models.size(); i++)
	{
		models[i]->Shutdown();
		delete models[i];
		models[i] = 0;
	}
	models.clear();
	modelMap.clear();
}

int ModelManager::LoadModel(ID3D11Device* device, std::wstring fileName)
{
	bool result;

	D3DModel* model;

	if(unusedIDs.empty())
	{
		model = new D3DModel();
	}
	else
	{
		model = new D3DModel(unusedIDs[0]);
		unusedIDs.erase(unusedIDs.begin());
	}
	result = model->LoadModel(device, fileName);
	if(!result)
	{
		//wrong filename or bad model
		return -1;
	}

	models.push_back(model);
	modelMap.insert(std::pair<unsigned int, D3DModel*>(model->GetID(), model));
	return model->GetID();
}

bool ModelManager::LoadAnimation(unsigned int ID, std::wstring fileName)
{
	bool result;

	result = modelMap[ID]->LoadAnimation(fileName);
	if(!result)
	{
		return false;
	}

	return true;
}

void ModelManager::LoadTexture(unsigned int ID, std::string referenceName)
{
	modelMap[ID]->LoadTexture(textureManager->GetTexture(referenceName));
}

void ModelManager::ReleaseModel(unsigned int ID)
{
	for(unsigned int i = 0; i < models.size(); i++)
	{
		if(modelMap[ID] == models[i])
		{
			delete models[i];
			models[i] = 0;
			models.erase(models.begin() + i);
			modelMap.erase(ID);
			unusedIDs.push_back(ID);
		}
	}
}