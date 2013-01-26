#include "ColladaMesh.h"
#include "ColladaMeshManager.h"
#include "../Common/GeometryGenerator.h"

static int m_iNextId = 0;
UINT mBoxIndexCount;

//Copy Constructor
ColladaMesh::ColladaMesh(ID3D11Device* md3dDevice, string name)// : BaseObject(D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(0.0f,0.0f,0.0f),D3DXVECTOR3(1.0f,1.0f,1.0f))
{
	device = md3dDevice;
	m_sName = name;
	m_Mesh = new DX11MeshGeometry();
	m_iMeshId = m_iNextId;
	m_iNextId++;
	m_fAlpha = 1.0f;
	mBoxMat.Ambient  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mBoxMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mBoxMat.Specular = XMFLOAT4(0.6f, 0.6f, 0.6f, 16.0f);

	HR(D3DX11CreateShaderResourceViewFromFile(device, 
		L"../Assets/Textures/stonenormals.jpg", 0, 0, &normalTexture, 0 ));
	HR(D3DX11CreateShaderResourceViewFromFile(device, 
		L"../Assets/Textures/stone2.jpg", 0, 0, &diffuseTexture, 0 ));	
	m_vScale = Vector3(1,1,1);
	m_vPosition = Vector3(0,0,0);
	m_vRotation = Vector3(0,0,-1.57f);
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&m_mWorld, I);
	XMStoreFloat4x4(&mTexTransform, I);
}

ColladaMesh::~ColladaMesh()
{
	m_vVertices.clear();
	m_vIndices.clear();
	m_vPositions.clear();
	m_vNormals.clear();
	m_vUV.clear();
	m_vTangents.clear();
	m_vBinormals.clear();
	ReleaseCOM(mBoxVB);
	ReleaseCOM(mBoxIB);
	ReleaseCOM(diffuseTexture);
	ReleaseCOM(normalTexture);
}

//Loads the Vertex and Index buffers
void ColladaMesh::LoadBuffers(daeElement *geometry)
{
	if(diffuseTexture == 0)
	{
	HR(D3DX11CreateShaderResourceViewFromFile(device, 
		L"../Assets/Textures/stone2.jpg", 0, 0, &diffuseTexture, 0 ));	
	}
	//Create the vertex buffer by passing the pointer to the mesh daeElement
	LoadVertexBuffer(geometry->getChild("mesh"));
	//Create the index buffer by passing the pointer to the mesh daeElement
	LoadIndexBuffer(geometry->getChild("mesh"));
}
//Load the Vertex Buffer from the <Geometry> Tag in the Dae file
void ColladaMesh::LoadVertexBuffer(daeElement *mesh)
{
	//Load all the vertex data for the current mesh
	daeTArray<daeElementRef> source = mesh->getChildren();
	if(source[0]->getAttribute("id").find("positions") != string::npos)
	{
		daeElement* float_array = source[0]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string positionArray = float_array->getCharData();
		std::stringstream stm(positionArray);
		for(int i = 0; i < count / 3; i++)
		{
			float x,y,z;
			stm >> x; stm >> y; stm >> z;
			m_vPositions.push_back(XMFLOAT3(x,y,z));
		}
		
	}
	else if(source[0]->getAttribute("id").find("POSITION") != string::npos)
	{
		daeElement* float_array = source[0]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string positionArray = float_array->getCharData();
		std::stringstream stm(positionArray);
		for(int i = 0; i < count / 3; i++)
		{
			float x,y,z;
			stm >> x; stm >> y; stm >> z;
			m_vPositions.push_back(XMFLOAT3(x,y,z));
		}
		
	}
	if(source[1]->getAttribute("id").find("normals") != string::npos)
	{
		daeElement* float_array = source[1]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string normalArray = float_array->getCharData();
		std::stringstream stm(normalArray);
		for(int i = 0; i < count / 3; i++)
		{
			float x,y,z;
			stm >> x; stm >> y; stm >> z;
			m_vNormals.push_back(XMFLOAT3(x,y,z));
		}
		//delete float_array;
	}
	else if(source[1]->getAttribute("id").find("Normal0") != string::npos)
	{
		daeElement* float_array = source[1]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string normalArray = float_array->getCharData();
		std::stringstream stm(normalArray);
		for(int i = 0; i < count / 3; i++)
		{
			float x,y,z;
			stm >> x; stm >> y; stm >> z;
			m_vNormals.push_back(XMFLOAT3(x,y,z));
		}
		//delete float_array;
	}
	//map1 = UV only contains two coordinates that range from 0 - 1 
	string stride = source[2]->getDescendant("technique_common")->getDescendant("accessor")->getAttribute("stride").data();
	int strideCount = 2;
	if(stride == "3")
	{
		strideCount = 3;
	}
	if(source[2]->getAttribute("id").find("map1") != string::npos)
	{
		daeElement* float_array = source[2]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string mapArray = float_array->getCharData();
		std::stringstream stm(mapArray);
		for(int i = 0; i < count / strideCount; i++)
		{
			float x,y,poop = 0;
			stm >> x; stm >> y; 
			if(strideCount == 3)
				stm >> poop;
			//Convert UV coordinate system from Collada format (Bottom-Left origin) to DirectX format (Top-Left origin) 12/7/2010
			m_vUV.push_back(XMFLOAT2(x,1-y));
		}
		//delete float_array;
	}
	else if(source[2]->getAttribute("id").find("UV0") != string::npos)
	{
		daeElement* float_array = source[2]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string mapArray = float_array->getCharData();
		std::stringstream stm(mapArray);
		for(int i = 0; i < count / strideCount; i++)
		{
			float x,y,poop = 0;
			stm >> x; stm >> y; 
			if(strideCount == 3)
				stm >> poop;
			//Convert UV coordinate system from Collada format (Bottom-Left origin) to DirectX format (Top-Left origin) 12/7/2010
			m_vUV.push_back(XMFLOAT2(x,1-y));
		}
		//delete float_array;
	}

	if(source[3]->getAttribute("id").find("textangents") != string::npos)
	{
		daeElement* float_array = source[3]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string tangentArray = float_array->getCharData();
		std::stringstream stm(tangentArray);
		for(int i = 0; i < count / 3; i++)
		{
			float x,y,z;
			stm >> x; stm >> y; stm >> z;
			m_vTangents.push_back(XMFLOAT4(x,y,z, 1));
		}
		//delete float_array;
	}
	if(source[4]->getAttribute("id").find("texbinormals") != string::npos)
	{
		daeElement* float_array = source[4]->getChild("float_array");
		int count = atoi(float_array->getAttribute("count").data());	
		string binormalArray = float_array->getCharData();
		std::stringstream stm(binormalArray);
		for(int i = 0; i < count / 3; i++)
		{
			float x,y,z;
			stm >> x; stm >> y; stm >> z;
			m_vBinormals.push_back(XMFLOAT4(x,y,z, 1));
		}
		//delete float_array;
	}
	//Load the vertices vector with the accumluted data from the vertex data
	for(unsigned int i = 0; i < m_vPositions.size();i++)
	{
		VertexData vert;
		vert.m_vNormal = m_vNormals[i];
		vert.m_vPosition = m_vPositions[i];
		vert.m_vUV = m_vUV[i];
		if(m_vBinormals.size() != 0 && m_vTangents.size() != 0)
		{
			vert.m_vBinormals = m_vBinormals[i];
			vert.m_vTangent = m_vTangents[i];
		}
		//m_vVertices.push_back(ColladaVertex(m_vPositions[i],m_vUV[i],m_vNormals[i],m_vTangents[i],m_vBinormals[i]));
		m_vVertices.push_back(vert);
	}
}
//Load the Index Buffer from the <Geometry> Tag and the <p> or triangles data
void ColladaMesh::LoadIndexBuffer(daeElement *mesh)
{
	daeTArray<daeElementRef> triList = mesh->getChildren();
	//g_dOutput->AddDataToFile("triangle tag number: ><<<<<<<<<<<<<<<<");
	//g_dOutput->AddDataToFile(mesh->findLastIndexOf("triangles"));
	//Loop through all of the indices located in <p> tag in the dae
	for(int i = 6; i < mesh->findLastIndexOf("triangles")+1; i++)
	{
		daeElement *p = triList[i]->getDescendant("p");
		std::stringstream stm(p->getCharData());
		int count = atoi(triList[i]->getAttribute("count").data())*3;
		
		int triangles = 0;
		//load the indices vector
		for(int it = 0; it < count; it++)
		{
			//pass the char data from the stm to the indices vector
			stm >> triangles;
			m_vIndices.push_back(triangles);
		}
		p = nullptr;
	}
	//Convert the world matrix and indices from OpenGl friendly format to Directx friendly format
	ConvertToDirectX11();
}

void ColladaMesh::ConvertToDirectX11()
{
	for(unsigned int i = 0; i < m_vIndices.size();i += 3)
	{
		//Load the indices into a temporary v0,v1,v2 variables
		int v0 = m_vIndices[i];
		int v1 = m_vIndices[i+1];
		int v2 = m_vIndices[i+2];
		//load the indices into the indices vector counter clockwise
		m_vIndices[i] = v0;
		m_vIndices[i+1] = v2;
		m_vIndices[i+2] = v1;
	}
	m_vScale = Vector3(1,1,-1);

	GeometryGenerator::MeshData box;

	GeometryGenerator geoGen;
	//geoGen.CreateBox(1.0f, 1.0f, 1.0f, box);
	geoGen.CreateColladaObject(m_vIndices,m_vVertices,box, false);
	// Cache the index count of each object.
	mBoxIndexCount      = box.Indices.size();

	UINT totalVertexCount = box.Vertices.size();

	UINT totalIndexCount = mBoxIndexCount;

	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	std::vector<Vertex::Basic32> vertices(totalVertexCount);

	UINT k = 0;
	for(size_t i = 0; i < box.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos    = box.Vertices[i].Position;
		vertices[k].Normal = box.Vertices[i].Normal;
		vertices[k].Tex    = box.Vertices[i].TexC;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::Basic32) * totalVertexCount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(device->CreateBuffer(&vbd, &vinitData, &mBoxVB));

	// Pack the indices of all the meshes into one index buffer.
	std::vector<UINT> indices;
	indices.insert(indices.end(), box.Indices.begin(), box.Indices.end());

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * totalIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	HR(device->CreateBuffer(&ibd, &iinitData, &mBoxIB));
	//HR(D3DX11CreateShaderResourceViewFromFile(device, 
	//	textureName, 0, 0, &diffuseTexture, 0 ));
}

void ColladaMesh::Update(float dt)
{
	
}

//Render the mesh to the scene
void ColladaMesh::Render(ID3D11DeviceContext *dc,  ID3DX11EffectTechnique* activeTech, DX11Camera mCam)
{	
	Vector3 mScale = m_vScale;
	Vector3 mPosition = m_vPosition;
	Vector3 mRotation = m_vRotation;
	XMMATRIX mBoxRotation = XMMatrixRotationRollPitchYaw(mRotation.GetZ(), mRotation.GetY(), mRotation.GetX());
	XMMATRIX mBoxScale = XMMatrixScaling(mScale.GetX(), mScale.GetY(), mScale.GetZ());
	XMMATRIX mBoxPosition = XMMatrixTranslation(mPosition.GetX(), mPosition.GetY(), mPosition.GetZ());
	XMStoreFloat4x4(&m_mWorld, XMMatrixMultiply(XMMatrixMultiply(mBoxRotation,mBoxScale), mBoxPosition));

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;
	DWORD numFaces = m_vIndices.size();
	DWORD numVertices = m_vVertices.size();
	dc->IASetVertexBuffers(0, 1, &mBoxVB, &stride, &offset);
	dc->IASetIndexBuffer(mBoxIB, DXGI_FORMAT_R32_UINT, 0);

	XMMATRIX world = XMLoadFloat4x4(&m_mWorld);
	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
	XMMATRIX worldViewProj = world * mCam.View() * mCam.Proj();
	Effects::BillboardFX->SetWorld(world);
	Effects::BillboardFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BillboardFX->SetWorldViewProj(worldViewProj);
	Effects::BillboardFX->SetTexTransform(XMLoadFloat4x4(&mTexTransform));
	Effects::BillboardFX->SetMaterial(mBoxMat);
	Effects::BillboardFX->SetDiffuseMap(diffuseTexture);
	Effects::BillboardFX->SetNormalMap(normalTexture);
	Effects::BillboardFX->SetSSFlag(false);
	Effects::BillboardFX->SetSobelFlag(false);
	Effects::BillboardFX->SetToonFlag(false);
	Effects::BillboardFX->SetFogFlag(false);
	Effects::BillboardFX->SetFogColor(Vector3(0,0,0));
	Effects::BillboardFX->SetFogStart(10.0f);
	Effects::BillboardFX->SetFogRange(100.0f);
	Effects::BillboardFX->SetGlitterFlag(false);
	Effects::BillboardFX->SetGlassFlag(false);
	float num = (float)(rand()%100)/1000;
	Effects::BillboardFX->SetRandomNumber(num);
	activeTech->GetPassByIndex(0)->Apply(0, dc);
	dc->DrawIndexed(mBoxIndexCount, 0, 0);
}

//Releases devices when the window/application is lost 
void ColladaMesh::OnLostDevice()
{
}

///Resource used from http://thecansin.com/Files/COLLADA.pdf
void ColladaMesh::OnResetDevice()
{
}

//Load the texture from file
void ColladaMesh::LoadTexture(string fileName)
{
	fileName = TEXTUREPATH + fileName;
	std::wstring stemp = std::wstring(fileName.begin(), fileName.end());
	textureName = stemp.c_str();
		HR(D3DX11CreateShaderResourceViewFromFile(device, 
		textureName, 0, 0, &diffuseTexture, 0 ));	
}

void ColladaMesh::Transform()
{
}

Vector3& ColladaMesh::GetPosition()
{
	return m_vPosition;
}