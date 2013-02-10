//#pragma once
//#include "Common\dx11Util.h"
//#include "Model Loader\ColladaModelLoader.h"
//#include "Model Loader\ColladaVertex.h"
//#include "DX11MeshGeometry.h"
//#include "DX11Camera.h"
//#include "DXEffect.h"
//
//class AnimationKey
//{
//public:
//	float Time;
//	XMFLOAT4X4 Matrix;
//	int Bone;
//
//	AnimationKey()
//	{
//		Bone = 0;
//		Time = 0;
//		XMMATRIX I = XMMatrixIdentity();
//		XMStoreFloat4x4(&Matrix, I);
//	}
//
//	AnimationKey(float time, XMFLOAT4X4 matrix, int bone)
//	{
//		Time = time;
//		Bone = bone;
//		Matrix = matrix;
//	}
//};
//
//class Joint
//{
//private:
//	//SID
//	std::string SID;
//	//Node for this in the COLLADA file
//	daeElement* Node;
//	//Animation Keys for this Joint
//	std::vector<AnimationKey> Animations;
//	//COLLADALoader access rights
//	friend class COLLADALoader;
//	//SkinnedMesh access rights
//	friend class SkinnedMesh;
//	public:
//	//Name
//	std::string Name;
//
//	//Bind_Matrix
//	XMFLOAT4X4 bind_matrix;
//	//Inv_Bind_Matrix
//	XMFLOAT4X4 inv_bind_matrix;
//	//Parent Index
//	int parentIndex;
//	//Parent Joint*
//	Joint* parentJoint;
//	//Base Constructor
//	Joint()
//	{
//		//Initialize SID
//		//SID = string();
//
//		//Initialize Node
//		Node = NULL;
//
//		//Initialize Animations
//		Animations = std::vector<AnimationKey>();
//
//		//Initialize Name
//		//Name = string();
//
//		//Initialize bind_matrix
//		XMMATRIX I = XMMatrixIdentity();
//		XMStoreFloat4x4(&bind_matrix, I);
//
//		//Initialize inv_bind_matrix
//		XMStoreFloat4x4(&inv_bind_matrix, I);
//
//		//Initialize parentIndex
//		parentIndex = 0;
//
//		//Initialize parentJoint
//		parentJoint = NULL;
//	}
//
//	//Detailed Constructor
//	Joint(std::string Name, std::string SID, daeElement* Node)
//	{
//		//Initialize SID
//		this->SID = SID;
//
//		//Initialize Node
//		this->Node = Node;
//
//		//Initialize Animations
//		Animations = std::vector<AnimationKey>();
//
//		//Initialize Name
//		this->Name = Name;
//
//		//Initialize bind_matrix
//		XMMATRIX I = XMMatrixIdentity();
//		XMStoreFloat4x4(&bind_matrix, I);
//
//		//Initialize inv_bind_matrix
//		XMStoreFloat4x4(&inv_bind_matrix, I);
//
//		//Initialize parentIndex
//		parentIndex = 0;
//
//		//Initialize parentJoint
//		parentJoint = NULL;
//	}
//
//};