//#include "ColladaMeshManager.h"
//
////ColladaMeshManager *g_MeshMgr = 0;
//
//ColladaMeshManager::ColladaMeshManager():m_iNextID(0)
//{
//}
//
//ColladaMeshManager* ColladaMeshManager::getInstance()
//{
//	static ColladaMeshManager cmm;
//
//	return &cmm;
//}
//
//ColladaMeshManager::~ColladaMeshManager()
//{
//	m_mMeshList.clear();
//}
//
//int ColladaMeshManager::GetMeshId(int id)
//{
//	return m_mMeshList.find(id)->second->GetId();
//}
//
//void ColladaMeshManager::RemoveMesh(int id)
//{
//	MeshMap::const_iterator entity = m_mMeshList.find(id);
//	ColladaMesh* data_pointer_is_pointing_to = (*entity).second;
//	//Finally delete the memory being pointed to.
//	delete data_pointer_is_pointing_to;
//	//And erase the entity from the map. Goodbye :(
//	m_mMeshList.erase(m_mMeshList.find(id));
//}
//
//void ColladaMeshManager::AddNewMesh(string fileName)
//{
//	IsDuplicate(fileName);
//}
//
//void ColladaMeshManager::AddNewMesh(ColladaMesh *mesh)
//{
//	m_mMeshList.insert(make_pair(m_iNextID,mesh));
//	m_iNextID++;
//}
//
//bool ColladaMeshManager::IsDuplicate(string name)
//{
//	for(MeshMap::const_iterator i = m_mMeshList.begin(); i != m_mMeshList.end();++i)
//	{
//		if(i->second->GetName() == name)
//		{
//			ColladaMesh* temp = new ColladaMesh(*i->second);
//			m_mMeshList.insert(make_pair(m_iNextID,temp));
//			m_iNextID++;
//			//break out of the for loop
//			i = m_mMeshList.end();
//			return true;			
//		}
//	}
//	return false;
//}
//
//void ColladaMeshManager::LoadTextures(ColladaMesh* m, string fileName)
//{
//	m->LoadTexture(fileName);
//	m->SetTexture(true);
//}
//
//
//void ColladaMeshManager::Update(float dt)
//{
//	//Update all of the meshes within the map 
//	for(MeshMap::const_iterator i = m_mMeshList.begin(); i != m_mMeshList.end();i++)
//	{
//		i->second->Update(dt);
//	}
//}
//
//void ColladaMeshManager::Render(ID3D11DeviceContext* dc, ID3DX11EffectTechnique* activeTech, DX11Camera mCam)
//{
//	//Render all of the meshes within the map 
//	for(MeshMap::const_iterator i = m_mMeshList.begin(); i != m_mMeshList.end();i++)
//	{
//		//If the alpha value of the current mesh isn't above 0.1f then don't render it
//		if(i->second->GetAlpha() >= 0.1f)
//		{
//			//Pass the DirectX device and effect 
//			i->second->Render(dc, activeTech, mCam);
//		}
//	}
//}
//
//void ColladaMeshManager::OnLostDevice()
//{
//	for(MeshMap::const_iterator i = m_mMeshList.begin(); i != m_mMeshList.end();i++)
//	{ 
//		i->second->OnLostDevice();
//	}
//}
//
//void ColladaMeshManager::OnResetDevice()
//{
//	for(MeshMap::const_iterator i = m_mMeshList.begin(); i != m_mMeshList.end();i++)
//	{ 
//		i->second->OnResetDevice();
//	}
//}
////void ColladaMeshManager::GetMouseWorldPosition( D3DXVECTOR3& direction)
////{
////	POINT p = {0, 0};
////	GetCursorPos(&p);
////	//ScreenToClient(gd3dApp->getMainWnd(), &p);
////
////	//// Compute the vector of the Pick ray in screen space
//// //   D3DXVECTOR3 v;
////	//v.x = (  2.0f * p.x  / gd3dApp->GetBackBufferWidth()  - 1 ) / g_camMgr->GetCamera(0)->GetProjectionMtx()._11;
//// //   v.y = ( -2.0f * p.y / gd3dApp->GetBackBufferHeight()  - 1 ) / g_camMgr->GetCamera(0)->GetProjectionMtx()._22;
//// //   v.z = 1.0f;
////
////    // Get the inverse view matrix
////	//const D3DXMATRIX matView = g_camMgr->GetCamera(0)->GetViewMtx();
////    D3DXMATRIX InvView;
////  //  D3DXMatrixInverse( &InvView, NULL, &matView );
////
////	// Transform the screen space Pick ray into 3D space
////	//D3DXVec3TransformNormal(&direction, &v, &InvView);
////	D3DXVec3Normalize(&direction, &direction);
////}
