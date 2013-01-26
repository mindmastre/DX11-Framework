#include "DXCylinder.h"

DXCylinder::DXCylinder(ID3D11Device* md3dDevice, LPCWSTR texturePath)
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mCylinderWorld, I);
	XMStoreFloat4x4(&mTexTransform, I);
	SetScale(Vector3(1,1,1));
	SetPosition(Vector3(0,0,0));
	SetRotation(Vector3(0,0,0));
	mCylinderMat.Ambient  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mCylinderMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mCylinderMat.Specular = XMFLOAT4(0.6f, 0.6f, 0.6f, 16.0f);

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, 
	texturePath, 0, 0, &cylinderDiffuseTexture, 0 ));
	BuildBuffers(md3dDevice);
}

DXCylinder::~DXCylinder()
{
	ReleaseCOM(mCylinderVB);
	ReleaseCOM(mCylinderIB);
	ReleaseCOM(cylinderDiffuseTexture);
}

void DXCylinder::BuildBuffers(ID3D11Device* md3dDevice)
{
	GeometryGenerator::MeshData cylinder;

	GeometryGenerator geoGen;
	geoGen.CreateCylinder(0.5f, 0.3f, 3.0f, 20, 20, cylinder);

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	mCylinderVertexOffset      = 0;

	// Cache the index count of each object.
	mCylinderIndexCount      = cylinder.Indices.size();

	// Cache the starting index for each object in the concatenated index buffer.
	mCylinderIndexOffset      = 0;
	
	UINT totalVertexCount = cylinder.Vertices.size();

	UINT totalIndexCount = mCylinderIndexCount;

	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	std::vector<Vertex::Basic32> vertices(totalVertexCount);

	UINT k = 0;
	for(size_t i = 0; i < cylinder.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos    = cylinder.Vertices[i].Position;
		vertices[k].Normal = cylinder.Vertices[i].Normal;
		vertices[k].Tex    = cylinder.Vertices[i].TexC;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::Basic32) * totalVertexCount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mCylinderVB));

	// Pack the indices of all the meshes into one index buffer.
	std::vector<UINT> indices;
	indices.insert(indices.end(), cylinder.Indices.begin(), cylinder.Indices.end());

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * totalIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mCylinderIB));
}

void DXCylinder::DrawCylinder(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam)
{
	//Perform matrix operations for stored scale and position
	XMMATRIX mCylinderRotation = XMMatrixRotationRollPitchYaw(mRotation.GetZ(), mRotation.GetY(), mRotation.GetX());
	XMMATRIX mCylinderScale = XMMatrixScaling(mScale.GetX(), mScale.GetY(), mScale.GetZ());
	XMMATRIX mCylinderPosition = XMMatrixTranslation(mPosition.GetX(), mPosition.GetY(), mPosition.GetZ());
	XMStoreFloat4x4(&mCylinderWorld, XMMatrixMultiply(XMMatrixMultiply(mCylinderRotation,mCylinderScale), mCylinderPosition));

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mCylinderVB, &stride, &offset);
	md3dImmediateContext->IASetIndexBuffer(mCylinderIB, DXGI_FORMAT_R32_UINT, 0);

	// Draw the Cylinder.
	XMMATRIX world = XMLoadFloat4x4(&mCylinderWorld);
	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
	XMMATRIX worldViewProj = world * mCam.View() * mCam.Proj();
	Effects::BillboardFX->SetWorld(world);
	Effects::BillboardFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BillboardFX->SetWorldViewProj(worldViewProj);
	Effects::BillboardFX->SetTexTransform(XMLoadFloat4x4(&mTexTransform));
	Effects::BillboardFX->SetMaterial(mCylinderMat);
	Effects::BillboardFX->SetDiffuseMap(cylinderDiffuseTexture);

	activeTech->GetPassByIndex(0)->Apply(0, md3dImmediateContext);
	md3dImmediateContext->DrawIndexed(mCylinderIndexCount, mCylinderIndexOffset, mCylinderVertexOffset);
}

void DXCylinder::SetPosition(Vector3 pos)
{
	mPosition = pos;
}

void DXCylinder::SetScale(Vector3 scale)
{
	mScale = scale;
}

Vector3 DXCylinder::GetPosition()
{
	return mPosition;
}

Vector3 DXCylinder::GetScale()
{
	return mScale;
}

void DXCylinder::SetRotation(Vector3 rot)
{
	mRotation = rot;
}

Vector3 DXCylinder::GetRotation()
{
	return mRotation;
}
