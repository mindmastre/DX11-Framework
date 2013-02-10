//#pragma once
//#include <dae.h>
//#include <dom.h>
//#include <dom/domCOLLADA.h>
//
//#include "../Common/DX11App.h"
////#include "CameraManager.h"
//#include "ColladaMeshManager.h"
//#define CMODELLOADER ColladaModelLoader::getInstance()
//#include "../AnimatedMesh.h"
//
//class ColladaModelLoader
//{
//private:
//	//Dae file
//	DAE* dae;
//	//Root node
//	daeElement* root;
//	//<library_visual_scenes> node
//	daeElement* library_visual_scenes;
//	//<library_animations> node
//	daeElement* library_animations;
//	//<libary_geometries> node
//	daeElement* library_geometries;
//	//<library_materials> node
//	daeElement* library_materials;
//	//<library_effects> node
//	daeElement* library_effects;
//	//<library_lights> node
//	daeElement* library_lights;
//	//<library_images> node
//	daeElement* library_images;
//	//List of Models
//	std::vector<std::string> m_vModelList;
//	//Constructor
//	ColladaModelLoader();
//	ID3D11Device* device;
//public:
//	//Destructor
//	~ColladaModelLoader();
//	static ColladaModelLoader* getInstance();
//	XMFLOAT4X4 processMatrix(daeElement* matrix);
//	void ObtainSkeletonData(daeElement *visualElement);
//	//void processAnimation(Joint* joint, int jointIndex, daeElement* animation);
//	///ALL OF THESE FUNCTIONS NEED TO HAVE A POINTER OF A MESH PASSED AS AN ARGUMENT ex. function(Mesh* mesh)
//	//Function that reads data from a Dae file and saves to text file
//	int ReadDaeFile(std::string fileName, ID3D11Device* device);
//	//Obtains data within the <visual_scene> element that contains data like the 
//	void ObtainVisualSceneData(daeElement *visualElement);
//	//Obtains data within the <library_geometries> element that consists of mesh data(position,normals, binormals, UV, tangent) 
//	void ObtainGeometriesData(daeElement *geometryElement);
//	//Obtains data within the <library_effects> element that consists of effects data for shaders
//	void ObtainEffectsData(daeElement *effectElement);
//	//Obtains data within the <library_material> element 
//	void ObtainMaterialData(daeElement *materialElement);
//	//Obtains data within the <library_lights> element 
//	void ObtainLightsData(daeElement *lightsElement);
//	//Obtains the texture data from the <library_images> element
//	std::string ObtainImageData(daeElement *imageElement);
//	//Function that will convert raw matrix data to D3DXMATRIX friendly data 
//	XMMATRIX MatrixConversion(daeElement *matrix);
//	//Keeps track of the number of models being loaded through the model loader
//	int m_iModelCount;
//
//	bool IsDuplicate(std::string fileName);
//
//	
//
//};
//
////extern ColladaModelLoader *g_ModelLoader;
