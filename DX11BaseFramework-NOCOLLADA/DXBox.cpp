#include "DXBox.h"

DXBox::DXBox(ID3D11Device* md3dDevice, LPCWSTR texturePath)
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mBoxWorld, I);
	XMStoreFloat4x4(&mTexTransform, I);
	SetScale(Vector3(1,1,1));
	SetPosition(Vector3(0,0,0));
	SetRotation(Vector3(0,0,0));
	mBoxMat.Ambient  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mBoxMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mBoxMat.Specular = XMFLOAT4(0.6f, 0.6f, 0.6f, 16.0f);

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, 
	texturePath, 0, 0, &boxDiffuseTexture, 0 ));
	BuildBuffers(md3dDevice);
}

DXBox::~DXBox()
{
	ReleaseCOM(mBoxVB);
	ReleaseCOM(mBoxIB);
	ReleaseCOM(boxDiffuseTexture);
}

void DXBox::BuildBuffers(ID3D11Device* md3dDevice)
{
	GeometryGenerator::MeshData box;

	GeometryGenerator geoGen;
	geoGen.CreateBox(1.0f, 1.0f, 1.0f, box);

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	mBoxVertexOffset      = 0;

	// Cache the index count of each object.
	mBoxIndexCount      = box.Indices.size();

	// Cache the starting index for each object in the concatenated index buffer.
	mBoxIndexOffset      = 0;
	
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
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mBoxVB));

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
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mBoxIB));
}

void DXBox::DrawBox(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam)
{
	//Perform matrix operations for stored scale and position
	XMMATRIX mBoxRotation = XMMatrixRotationRollPitchYaw(mRotation.GetZ(), mRotation.GetY(), mRotation.GetX());
	XMMATRIX mBoxScale = XMMatrixScaling(mScale.GetX(), mScale.GetY(), mScale.GetZ());
	XMMATRIX mBoxPosition = XMMatrixTranslation(mPosition.GetX(), mPosition.GetY(), mPosition.GetZ());
	XMStoreFloat4x4(&mBoxWorld, XMMatrixMultiply(XMMatrixMultiply(mBoxRotation,mBoxScale), mBoxPosition));

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mBoxVB, &stride, &offset);
	md3dImmediateContext->IASetIndexBuffer(mBoxIB, DXGI_FORMAT_R32_UINT, 0);

	// Draw the box.
	XMMATRIX world = XMLoadFloat4x4(&mBoxWorld);
	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
	XMMATRIX worldViewProj = world * mCam.View() * mCam.Proj();
	Effects::BillboardFX->SetWorld(world);
	Effects::BillboardFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BillboardFX->SetWorldViewProj(worldViewProj);
	Effects::BillboardFX->SetTexTransform(XMLoadFloat4x4(&mTexTransform));
	Effects::BillboardFX->SetMaterial(mBoxMat);
	Effects::BillboardFX->SetDiffuseMap(boxDiffuseTexture);

	activeTech->GetPassByIndex(0)->Apply(0, md3dImmediateContext);
	md3dImmediateContext->DrawIndexed(mBoxIndexCount, mBoxIndexOffset, mBoxVertexOffset);
}

void DXBox::SetPosition(Vector3 pos)
{
	mPosition = pos;
}

void DXBox::SetScale(Vector3 scale)
{
	mScale = scale;
}

Vector3 DXBox::GetPosition()
{
	return mPosition;
}

Vector3 DXBox::GetScale()
{
	return mScale;
}

void DXBox::SetRotation(Vector3 rot)
{
	mRotation = rot;
}

Vector3 DXBox::GetRotation()
{
	return mRotation;
}
