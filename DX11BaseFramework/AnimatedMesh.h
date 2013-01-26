#pragma once
#include "Common\dx11Util.h"
#include "Model Loader\ColladaModelLoader.h"
#include "Model Loader\ColladaVertex.h"
#include "DX11MeshGeometry.h"
#include "DX11Camera.h"
#include "DXEffect.h"
#include "Joint.h"

class Weight
{
	public:
	float Weights[4];
	Weight(){	for(int i = 0; i < 4; i++){Weights[i] = 0;}}
};

class Index
{
	public:
	short Indices[4];
	Index(){	for(int i = 0; i < 4; i++){Indices[i] = 0;}}
};

class SkinnedVertex
{
public:
	//Components of a Vertex
	Vector3 Position;
	Vector2 UV;
	Vector3 Normal;
	Vector3 Tangent;
	Vector3 BiTangent;
	Index Indices;
	Weight Weights;

	//Constructor
	SkinnedVertex(Vector3 Position, Vector2 UV, Vector3 Normal, Vector3 Tangent, Vector3 BiTangent, Index Indices, Weight Weights)
	{
		this->Position = Position;
		this->UV = UV;
		this->Normal = Normal;
		this->Tangent = Tangent;
		this->BiTangent = BiTangent;
		this->Indices = Indices;
		this->Weights = Weights;
	}
};

class SkinnedMesh
{
	//emp before getting a setter
public:
	daeElement* controller;
	//<geometry>
	daeElement* geometry;

	//Root <node> for skeleton
	daeElement* rootJoint;
private:
	//<controller>

	
	
	//Component Vertex Data, to be compiled into Vertices later...
	std::vector<Vector3> Positions;
	std::vector<Vector2> UVs;
	std::vector<Vector3> Normals;
	std::vector<Vector3> Tangents;
	std::vector<Vector3> BiTangents;
	std::vector<Index> boneIndices;
	std::vector<Weight> Weights;

	//Set it so COLLADALoader can access privates
	friend class COLLADALoader;

	//Combine the component vertex data to Vertices array
	void combineComponents()
	{
		for(unsigned int i = 0; i < Positions.size(); i++)
		{
			Vertices.push_back(SkinnedVertex(Positions[i], UVs[i], Normals[i], Tangents[i], BiTangents[i], boneIndices[i], Weights[i]));
		}
	}

	//Make Animation list
	void combineJointAnimations()
	{
		//Put all the Animations together
		for(unsigned int i = 0; i < Joints.size(); i++)
		{
			for(unsigned int z = 0; z < Joints[i].Animations.size(); z++)
			{
				Animations.push_back(Joints[i].Animations[z]);
			}
		}

		//Do a simple Bubble Sort by Time
		for(unsigned int i = 0; i < Animations.size(); i++)
		{
			for(unsigned int j = 0; j < i; j++)
			{
				if(Animations[i].Time < Animations[j].Time)
				{
					AnimationKey temp = Animations[i];
					Animations[i] = Animations[j];
					Animations[j] = temp;
				}
			}
		}
	}

public:
	//Name
	std::string Name;

	//Root Transform Matrix
	XMFLOAT4X4 RootTransform;

	//BindShape Matrix
	XMFLOAT4X4 BindShape;

	//Joints
	std::vector<Joint> Joints;

	//Time sorted Animation Key list
	std::vector<AnimationKey> Animations;

	//Combined Vertex Data, ready for Vertex Buffer
	std::vector<SkinnedVertex> Vertices;

	//Index data, ready for Index Buffer
	std::vector<unsigned int> Indices;

	//Constructor
	SkinnedMesh(std::string Name, XMFLOAT4X4 RootTransform)
	{
		//Set pointer to NULL
		controller = NULL;

		//Set pointer to NULL
		geometry = NULL;

		//Set pointer to NULL
		rootJoint = NULL;
		
		//Initialize Component Vertex Data
		Positions = std::vector<Vector3>();
		UVs = std::vector<Vector2>();
		Normals = std::vector<Vector3>();
		Tangents = std::vector<Vector3>();
		BiTangents = std::vector<Vector3>();
		boneIndices = std::vector<Index>();
		Weights = std::vector<Weight>();
		
		//Set Name
		this->Name = Name;

		//Set Root Transform Matrix
		this->RootTransform = RootTransform;

		//Set BindShape Matrix
		//D3DXMatrixIdentity(&BindShape);
		XMMATRIX I = XMMatrixIdentity();
		XMStoreFloat4x4(&BindShape, I);

		//Initialize Joints
		Joints = std::vector<Joint>();

		//Initialize Time sorted Animation Key list
		Animations = std::vector<AnimationKey>();

		//Initialize Combined Vertex Data, ready for Vertex Buffer
		Vertices = std::vector<SkinnedVertex>();

		//Initialize Index data, ready for Index Buffer
		Indices = std::vector<unsigned int>();
	}
};
