#include "DXPyramid.h"

DXPyramid::DXPyramid(ID3D11Device* md3dDevice, LPCWSTR texturePath)
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mPyramidWorld, I);
	XMStoreFloat4x4(&mTexTransform, I);
	SetScale(Vector3(1,1,-1));
	SetPosition(Vector3(0,0,0));
	SetRotation(Vector3(0,0,0));
	mPyramidMat.Ambient  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mPyramidMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPyramidMat.Specular = XMFLOAT4(0.6f, 0.6f, 0.6f, 16.0f);

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, 
	texturePath, 0, 0, &pyramidDiffuseTexture, 0 ));
	BuildBuffers(md3dDevice);
}

DXPyramid::~DXPyramid()
{
	ReleaseCOM(mPyramidVB);
	ReleaseCOM(mPyramidIB);
	ReleaseCOM(pyramidDiffuseTexture);
}

void DXPyramid::BuildBuffers(ID3D11Device* md3dDevice)
{
	GeometryGenerator::MeshData pyramid;

	GeometryGenerator geoGen;
	geoGen.CreatePyramid(2.0f, 2.0f, 2.0f, pyramid);

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	mPyramidVertexOffset      = 0;

	// Cache the index count of each object.
	mPyramidIndexCount      = pyramid.Indices.size();

	// Cache the starting index for each object in the concatenated index buffer.
	mPyramidIndexOffset      = 0;
	
	UINT totalVertexCount = pyramid.Vertices.size();

	UINT totalIndexCount = mPyramidIndexCount;

	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	std::vector<Vertex::Basic32> vertices(totalVertexCount);

	UINT k = 0;
	for(size_t i = 0; i < pyramid.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos    = pyramid.Vertices[i].Position;
		vertices[k].Normal = pyramid.Vertices[i].Normal;
		vertices[k].Tex    = pyramid.Vertices[i].TexC;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::Basic32) * totalVertexCount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mPyramidVB));

	// Pack the indices of all the meshes into one index buffer.
	std::vector<UINT> indices;
	indices.insert(indices.end(), pyramid.Indices.begin(), pyramid.Indices.end());

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * totalIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mPyramidIB));
}

void DXPyramid::DrawPyramid(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam)
{
	//Perform matrix operations for stored scale and position
	XMMATRIX mPyramidRotation = XMMatrixRotationRollPitchYaw(mRotation.GetZ(), mRotation.GetY(), mRotation.GetX());
	XMMATRIX mPyramidScale = XMMatrixScaling(mScale.GetX(), mScale.GetY(), mScale.GetZ());
	XMMATRIX mPyramidPosition = XMMatrixTranslation(mPosition.GetX(), mPosition.GetY(), mPosition.GetZ());
	XMStoreFloat4x4(&mPyramidWorld, XMMatrixMultiply(XMMatrixMultiply(mPyramidRotation,mPyramidScale), mPyramidPosition));

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mPyramidVB, &stride, &offset);
	md3dImmediateContext->IASetIndexBuffer(mPyramidIB, DXGI_FORMAT_R32_UINT, 0);

	// Draw the pyramid.
	XMMATRIX world = XMLoadFloat4x4(&mPyramidWorld);
	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
	XMMATRIX worldViewProj = world * mCam.View() * mCam.Proj();
	Effects::BillboardFX->SetWorld(world);
	Effects::BillboardFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BillboardFX->SetWorldViewProj(worldViewProj);
	Effects::BillboardFX->SetTexTransform(XMLoadFloat4x4(&mTexTransform));
	Effects::BillboardFX->SetMaterial(mPyramidMat);
	Effects::BillboardFX->SetDiffuseMap(pyramidDiffuseTexture);

	activeTech->GetPassByIndex(0)->Apply(0, md3dImmediateContext);
	md3dImmediateContext->DrawIndexed(mPyramidIndexCount, mPyramidIndexOffset, mPyramidVertexOffset);
}

void DXPyramid::SetPosition(Vector3 pos)
{
	mPosition = pos;
}

void DXPyramid::SetScale(Vector3 scale)
{
	mScale = scale;
}

Vector3 DXPyramid::GetPosition()
{
	return mPosition;
}

Vector3 DXPyramid::GetScale()
{
	return mScale;
}

void DXPyramid::SetRotation(Vector3 rot)
{
	mRotation = rot;
}

Vector3 DXPyramid::GetRotation()
{
	return mRotation;
}
