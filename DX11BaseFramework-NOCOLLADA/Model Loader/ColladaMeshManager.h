//#pragma once
//
//#include "../Common/dx11Util.h"
//#include "../DX11Camera.h"
//#include "ColladaMesh.h"
//#include "../AnimatedMesh.h"
//#define CMESHMANAGER ColladaMeshManager::getInstance()
//
//class ColladaMesh;
//class ColladaMeshManager
//{
//	ColladaMeshManager();
//	ID3D11Device* dxDevice;
//public:
//	//std::vector<SkinnedMesh*> SkinnedMeshes;
//
//	static ColladaMeshManager* getInstance();
//	~ColladaMeshManager();
//	void AddNewMesh(ColladaMesh *mesh);
//	void AddNewMesh(std::string fileName);
//	void RemoveMesh(int id);
//	void Update(float dt);
//	void Render(ID3D11DeviceContext* dc, ID3DX11EffectTechnique* activeTech, DX11Camera mCam);
//	void OnLostDevice();
//	void OnResetDevice();
//	void LoadTextures(ColladaMesh *m, std::string fileName);
//	int	  GetMeshId(int id);
//	ColladaMesh* GetMesh(int i) {return m_mMeshList[i];}
//	bool  IsDuplicate(std::string filename);
//	typedef std::map<int,ColladaMesh*> MeshMap;
//	//void GetMouseWorldPosition(D3DXVECTOR3& direction);
//	void SetDevice(ID3D11Device* md3dDevice){dxDevice = md3dDevice;}
//	ID3D11Device* getDevice() { return dxDevice;}
//private:		
//	MeshMap m_mMeshList;
//	int m_iNextID;
//
//};
//
////extern ColladaMeshManager* g_MeshMgr;
