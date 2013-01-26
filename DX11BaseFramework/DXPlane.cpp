#include "DXPlane.h"

DXPlane::DXPlane(ID3D11Device* md3dDevice, LPCWSTR texturePath)
{
	XMMATRIX I = XMMatrixIdentity();
	XMStoreFloat4x4(&mPlaneWorld, I);
	XMStoreFloat4x4(&mTexTransform, I);
	SetScale(Vector3(1,1,1));
	SetPosition(Vector3(0,0,0));
	SetRotation(Vector3(0,0,0));
	mPlaneMat.Ambient  = XMFLOAT4(0.5f, 0.5f, 0.5f, 1.0f);
	mPlaneMat.Diffuse  = XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
	mPlaneMat.Specular = XMFLOAT4(0.6f, 0.6f, 0.6f, 16.0f);

	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, 
	texturePath, 0, 0, &planeDiffuseTexture, 0 ));
	BuildBuffers(md3dDevice);
}

DXPlane::~DXPlane()
{
	ReleaseCOM(mPlaneVB);
	ReleaseCOM(mPlaneIB);
	ReleaseCOM(planeDiffuseTexture);
}

void DXPlane::BuildBuffers(ID3D11Device* md3dDevice)
{
	GeometryGenerator::MeshData plane;

	GeometryGenerator geoGen;
	geoGen.CreateGrid(1.0f, 1.0f, 60, 40, plane);

	// Cache the vertex offsets to each object in the concatenated vertex buffer.
	mPlaneVertexOffset      = 0;

	// Cache the index count of each object.
	mPlaneIndexCount      = plane.Indices.size();

	// Cache the starting index for each object in the concatenated index buffer.
	mPlaneIndexOffset      = 0;
	
	UINT totalVertexCount = plane.Vertices.size();

	UINT totalIndexCount = mPlaneIndexCount;

	// Extract the vertex elements we are interested in and pack the
	// vertices of all the meshes into one vertex buffer.
	std::vector<Vertex::Basic32> vertices(totalVertexCount);

	UINT k = 0;
	for(size_t i = 0; i < plane.Vertices.size(); ++i, ++k)
	{
		vertices[k].Pos    = plane.Vertices[i].Position;
		vertices[k].Normal = plane.Vertices[i].Normal;
		vertices[k].Tex    = plane.Vertices[i].TexC;
	}

	D3D11_BUFFER_DESC vbd;
	vbd.Usage = D3D11_USAGE_IMMUTABLE;
	vbd.ByteWidth = sizeof(Vertex::Basic32) * totalVertexCount;
	vbd.BindFlags = D3D11_BIND_VERTEX_BUFFER;
	vbd.CPUAccessFlags = 0;
	vbd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA vinitData;
	vinitData.pSysMem = &vertices[0];
	HR(md3dDevice->CreateBuffer(&vbd, &vinitData, &mPlaneVB));

	// Pack the indices of all the meshes into one index buffer.
	std::vector<UINT> indices;
	indices.insert(indices.end(), plane.Indices.begin(), plane.Indices.end());

	D3D11_BUFFER_DESC ibd;
	ibd.Usage = D3D11_USAGE_IMMUTABLE;
	ibd.ByteWidth = sizeof(UINT) * totalIndexCount;
	ibd.BindFlags = D3D11_BIND_INDEX_BUFFER;
	ibd.CPUAccessFlags = 0;
	ibd.MiscFlags = 0;
	D3D11_SUBRESOURCE_DATA iinitData;
	iinitData.pSysMem = &indices[0];
	HR(md3dDevice->CreateBuffer(&ibd, &iinitData, &mPlaneIB));
}

void DXPlane::DrawPlane(ID3D11DeviceContext* md3dImmediateContext, ID3DX11EffectTechnique* activeTech, DX11Camera mCam)
{
	//Perform matrix operations for stored scale and position
	XMMATRIX mPlaneRotation = XMMatrixRotationRollPitchYaw(mRotation.GetZ(), mRotation.GetY(), mRotation.GetX());
	XMMATRIX mPlaneScale = XMMatrixScaling(mScale.GetX(), mScale.GetY(), mScale.GetZ());
	XMMATRIX mPlanePosition = XMMatrixTranslation(mPosition.GetX(), mPosition.GetY(), mPosition.GetZ());
	XMStoreFloat4x4(&mPlaneWorld, XMMatrixMultiply(XMMatrixMultiply(mPlaneRotation,mPlaneScale), mPlanePosition));

	UINT stride = sizeof(Vertex::Basic32);
	UINT offset = 0;
	md3dImmediateContext->IASetVertexBuffers(0, 1, &mPlaneVB, &stride, &offset);
	md3dImmediateContext->IASetIndexBuffer(mPlaneIB, DXGI_FORMAT_R32_UINT, 0);

	// Draw the Plane.
	XMMATRIX world = XMLoadFloat4x4(&mPlaneWorld);
	XMMATRIX worldInvTranspose = MathHelper::InverseTranspose(world);
	XMMATRIX worldViewProj = world * mCam.View() * mCam.Proj();
	Effects::BillboardFX->SetWorld(world);
	Effects::BillboardFX->SetWorldInvTranspose(worldInvTranspose);
	Effects::BillboardFX->SetWorldViewProj(worldViewProj);
	Effects::BillboardFX->SetTexTransform(XMLoadFloat4x4(&mTexTransform));
	Effects::BillboardFX->SetMaterial(mPlaneMat);
	Effects::BillboardFX->SetDiffuseMap(planeDiffuseTexture);

	activeTech->GetPassByIndex(0)->Apply(0, md3dImmediateContext);
	md3dImmediateContext->DrawIndexed(mPlaneIndexCount, mPlaneIndexOffset, mPlaneVertexOffset);
}

void DXPlane::SetPosition(Vector3 pos)
{
	mPosition = pos;
}

void DXPlane::SetScale(Vector3 scale)
{
	mScale = scale;
}

Vector3 DXPlane::GetPosition()
{
	return mPosition;
}

Vector3 DXPlane::GetScale()
{
	return mScale;
}

void DXPlane::SetRotation(Vector3 rot)
{
	mRotation = rot;
}

Vector3 DXPlane::GetRotation()
{
	return mRotation;
}
