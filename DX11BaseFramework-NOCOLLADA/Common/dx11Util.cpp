#include "dx11Util.h"
#include "../Vertex.h"

//IDirect3DVertexDeclaration9* VertexPCTN::Decl = 0;

ID3D11ShaderResourceView* d3dHelper::CreateTexture2DArraySRV(
		ID3D11Device* device, ID3D11DeviceContext* context,
		std::vector<std::wstring>& filenames,
		DXGI_FORMAT format,
		UINT filter, 
		UINT mipFilter)
{
	//
	// Load the texture elements individually from file.  These textures
	// won't be used by the GPU (0 bind flags), they are just used to 
	// load the image data from file.  We use the STAGING usage so the
	// CPU can read the resource.
	//

	UINT size = filenames.size();

	std::vector<ID3D11Texture2D*> srcTex(size);
	for(UINT i = 0; i < size; ++i)
	{
		D3DX11_IMAGE_LOAD_INFO loadInfo;

        loadInfo.Width  = D3DX11_FROM_FILE;
        loadInfo.Height = D3DX11_FROM_FILE;
        loadInfo.Depth  = D3DX11_FROM_FILE;
        loadInfo.FirstMipLevel = 0;
        loadInfo.MipLevels = D3DX11_FROM_FILE;
        loadInfo.Usage = D3D11_USAGE_STAGING;
        loadInfo.BindFlags = 0;
        loadInfo.CpuAccessFlags = D3D11_CPU_ACCESS_WRITE | D3D11_CPU_ACCESS_READ;
        loadInfo.MiscFlags = 0;
        loadInfo.Format = format;
        loadInfo.Filter = filter;
        loadInfo.MipFilter = mipFilter;
		loadInfo.pSrcInfo  = 0;

        HR(D3DX11CreateTextureFromFile(device, filenames[i].c_str(), 
			&loadInfo, 0, (ID3D11Resource**)&srcTex[i], 0));
	}

	//
	// Create the texture array.  Each element in the texture 
	// array has the same format/dimensions.
	//

	D3D11_TEXTURE2D_DESC texElementDesc;
	srcTex[0]->GetDesc(&texElementDesc);

	D3D11_TEXTURE2D_DESC texArrayDesc;
	texArrayDesc.Width              = texElementDesc.Width;
	texArrayDesc.Height             = texElementDesc.Height;
	texArrayDesc.MipLevels          = texElementDesc.MipLevels;
	texArrayDesc.ArraySize          = size;
	texArrayDesc.Format             = texElementDesc.Format;
	texArrayDesc.SampleDesc.Count   = 1;
	texArrayDesc.SampleDesc.Quality = 0;
	texArrayDesc.Usage              = D3D11_USAGE_DEFAULT;
	texArrayDesc.BindFlags          = D3D11_BIND_SHADER_RESOURCE;
	texArrayDesc.CPUAccessFlags     = 0;
	texArrayDesc.MiscFlags          = 0;

	ID3D11Texture2D* texArray = 0;
	HR(device->CreateTexture2D( &texArrayDesc, 0, &texArray));

	//
	// Copy individual texture elements into texture array.
	//

	// for each texture element...
	for(UINT texElement = 0; texElement < size; ++texElement)
	{
		// for each mipmap level...
		for(UINT mipLevel = 0; mipLevel < texElementDesc.MipLevels; ++mipLevel)
		{
			D3D11_MAPPED_SUBRESOURCE mappedTex2D;
			HR(context->Map(srcTex[texElement], mipLevel, D3D11_MAP_READ, 0, &mappedTex2D));

			context->UpdateSubresource(texArray, 
				D3D11CalcSubresource(mipLevel, texElement, texElementDesc.MipLevels),
				0, mappedTex2D.pData, mappedTex2D.RowPitch, mappedTex2D.DepthPitch);

			context->Unmap(srcTex[texElement], mipLevel);
		}
	}	

	//
	// Create a resource view to the texture array.
	//
	
	D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = texArrayDesc.Format;
	viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE2DARRAY;
	viewDesc.Texture2DArray.MostDetailedMip = 0;
	viewDesc.Texture2DArray.MipLevels = texArrayDesc.MipLevels;
	viewDesc.Texture2DArray.FirstArraySlice = 0;
	viewDesc.Texture2DArray.ArraySize = size;

	ID3D11ShaderResourceView* texArraySRV = 0;
	HR(device->CreateShaderResourceView(texArray, &viewDesc, &texArraySRV));

	//
	// Cleanup--we only need the resource view.
	//

	ReleaseCOM(texArray);

	for(UINT i = 0; i < size; ++i)
		ReleaseCOM(srcTex[i]);

	return texArraySRV;
}

ID3D11ShaderResourceView* d3dHelper::CreateRandomTexture1DSRV(ID3D11Device* device)
{
	// 
	// Create the random data.
	//
	XMFLOAT4 randomValues[1024];

	for(int i = 0; i < 1024; ++i)
	{
		randomValues[i].x = MathHelper::RandF(-1.0f, 1.0f);
		randomValues[i].y = MathHelper::RandF(-1.0f, 1.0f);
		randomValues[i].z = MathHelper::RandF(-1.0f, 1.0f);
		randomValues[i].w = MathHelper::RandF(-1.0f, 1.0f);
	}

    D3D11_SUBRESOURCE_DATA initData;
    initData.pSysMem = randomValues;
	initData.SysMemPitch = 1024*sizeof(XMFLOAT4);
    initData.SysMemSlicePitch = 0;

	//
	// Create the texture.
	//
    D3D11_TEXTURE1D_DESC texDesc;
    texDesc.Width = 1024;
    texDesc.MipLevels = 1;
    texDesc.Format = DXGI_FORMAT_R32G32B32A32_FLOAT;
    texDesc.Usage = D3D11_USAGE_IMMUTABLE;
    texDesc.BindFlags = D3D11_BIND_SHADER_RESOURCE;
    texDesc.CPUAccessFlags = 0;
    texDesc.MiscFlags = 0;
    texDesc.ArraySize = 1;

	ID3D11Texture1D* randomTex = 0;
    HR(device->CreateTexture1D(&texDesc, &initData, &randomTex));

	//
	// Create the resource view.
	//
    D3D11_SHADER_RESOURCE_VIEW_DESC viewDesc;
	viewDesc.Format = texDesc.Format;
    viewDesc.ViewDimension = D3D11_SRV_DIMENSION_TEXTURE1D;
    viewDesc.Texture1D.MipLevels = texDesc.MipLevels;
	viewDesc.Texture1D.MostDetailedMip = 0;
	
	ID3D11ShaderResourceView* randomTexSRV = 0;
    HR(device->CreateShaderResourceView(randomTex, &viewDesc, &randomTexSRV));

	ReleaseCOM(randomTex);

	return randomTexSRV;
}

void ExtractFrustumPlanes(XMFLOAT4 planes[6], CXMMATRIX M)
{
	//
	// Left
	//
	planes[0].x = M(0,3) + M(0,0);
	planes[0].y = M(1,3) + M(1,0);
	planes[0].z = M(2,3) + M(2,0);
	planes[0].w = M(3,3) + M(3,0);

	//
	// Right
	//
	planes[1].x = M(0,3) - M(0,0);
	planes[1].y = M(1,3) - M(1,0);
	planes[1].z = M(2,3) - M(2,0);
	planes[1].w = M(3,3) - M(3,0);

	//
	// Bottom
	//
	planes[2].x = M(0,3) + M(0,1);
	planes[2].y = M(1,3) + M(1,1);
	planes[2].z = M(2,3) + M(2,1);
	planes[2].w = M(3,3) + M(3,1);

	//
	// Top
	//
	planes[3].x = M(0,3) - M(0,1);
	planes[3].y = M(1,3) - M(1,1);
	planes[3].z = M(2,3) - M(2,1);
	planes[3].w = M(3,3) - M(3,1);

	//
	// Near
	//
	planes[4].x = M(0,2);
	planes[4].y = M(1,2);
	planes[4].z = M(2,2);
	planes[4].w = M(3,2);

	//
	// Far
	//
	planes[5].x = M(0,3) - M(0,2);
	planes[5].y = M(1,3) - M(1,2);
	planes[5].z = M(2,3) - M(2,2);
	planes[5].w = M(3,3) - M(3,2);

	// Normalize the plane equations.
	for(int i = 0; i < 6; ++i)
	{
		XMVECTOR v = XMPlaneNormalize(XMLoadFloat4(&planes[i]));
		XMStoreFloat4(&planes[i], v);
	}
}
//
//void LoadXFile(const std::string& filename, ID3DXMesh** meshOut, std::vector<Mtrl>& mtrls, std::vector<IDirect3DTexture9*>& texs)
//{
//	// Step 1: Load the .x file from file into a system memory mesh.
//
//	ID3DXMesh* meshSys      = 0;
//	ID3DXBuffer* adjBuffer  = 0;
//	ID3DXBuffer* mtrlBuffer = 0;
//	DWORD numMtrls          = 0;
//	
//	HR(D3DXLoadMeshFromX((LPCWSTR)filename.c_str(), D3DXMESH_SYSTEMMEM, gd3d9Device,
//		&adjBuffer,	&mtrlBuffer, 0, &numMtrls, &meshSys));
//
//
//	// Step 2: Find out if the mesh already has normal info?
//
//	D3DVERTEXELEMENT9 elems[MAX_FVF_DECL_SIZE];
//	HR(meshSys->GetDeclaration(elems));
//	
//	bool hasNormals = false;
//	D3DVERTEXELEMENT9 term = D3DDECL_END();
//	for(int i = 0; i < MAX_FVF_DECL_SIZE; ++i)
//	{
//		// Did we reach D3DDECL_END() {0xFF,0,D3DDECLTYPE_UNUSED, 0,0,0}?
//		if(elems[i].Stream == 0xff )
//			break;
//
//		if( elems[i].Type == D3DDECLTYPE_FLOAT3 &&
//			elems[i].Usage == D3DDECLUSAGE_NORMAL &&
//			elems[i].UsageIndex == 0 )
//		{
//			hasNormals = true;
//			break;
//		}
//	}
//
//
//	// Step 3: Change vertex format to VertexPCTN.
//
//	D3DVERTEXELEMENT9 elements[64];
//	UINT numElements = 0;
//	VertexPCTN::Decl->GetDeclaration(elements, &numElements);
//
//	ID3DXMesh* temp = 0;
//	HR(meshSys->CloneMesh(D3DXMESH_SYSTEMMEM, 
//		elements, gd3d9Device, &temp));
//	ReleaseCOM(meshSys);
//	meshSys = temp;
//
//
//	// Step 4: If the mesh did not have normals, generate them.
//
//	if( hasNormals == false)
//		HR(D3DXComputeNormals(meshSys, 0));
//
//
//	// Step 5: Optimize the mesh.
//
//	HR(meshSys->Optimize(D3DXMESH_MANAGED | 
//		D3DXMESHOPT_COMPACT | D3DXMESHOPT_ATTRSORT | D3DXMESHOPT_VERTEXCACHE, 
//		(DWORD*)adjBuffer->GetBufferPointer(), 0, 0, 0, meshOut));
//	ReleaseCOM(meshSys); // Done w/ system mesh.
//	ReleaseCOM(adjBuffer); // Done with buffer.
//
//	// Step 6: Extract the materials and load the textures.
//
//	if( mtrlBuffer != 0 && numMtrls != 0 )
//	{
//		D3DXMATERIAL* d3dxmtrls = (D3DXMATERIAL*)mtrlBuffer->GetBufferPointer();
//
//		for(DWORD i = 0; i < numMtrls; ++i)
//		{
//			// Save the ith material.  Note that the MatD3D property does not have an ambient
//			// value set when its loaded, so just set it to the diffuse value.
//			Mtrl m;
//			m.ambient   = d3dxmtrls[i].MatD3D.Diffuse;
//			m.diffuse   = d3dxmtrls[i].MatD3D.Diffuse;
//			m.spec      = d3dxmtrls[i].MatD3D.Specular;
//			m.specPower = d3dxmtrls[i].MatD3D.Power;
//			mtrls.push_back( m );
//
//			// Check if the ith material has an associative texture
//			if( d3dxmtrls[i].pTextureFilename != 0 )
//			{
//				// Yes, load the texture for the ith subset
//				IDirect3DTexture9* tex = 0;
//				char* texFN = d3dxmtrls[i].pTextureFilename;
//				HR(D3DXCreateTextureFromFile(gd3d9Device, (LPCWSTR)texFN, &tex));
//
//				// Save the loaded texture
//				texs.push_back( tex );
//			}
//			else
//			{
//				// No texture for the ith subset
//				texs.push_back( 0 );
//			}
//		}
//	}
//	ReleaseCOM(mtrlBuffer); // done w/ buffer
//}
//
//void InitPCTNDeclaration()
//{
//	D3DVERTEXELEMENT9 VertexPCTNElements[] = 
//	{
//		{0, 0,  D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_POSITION, 0},
//		{0, 12, D3DDECLTYPE_FLOAT3, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_NORMAL, 0},
//		{0, 24, D3DDECLTYPE_FLOAT2, D3DDECLMETHOD_DEFAULT, D3DDECLUSAGE_TEXCOORD, 0},
//		D3DDECL_END()
//	};	
//	HR(gd3d9Device->CreateVertexDeclaration(VertexPCTNElements, &VertexPCTN::Decl));
//}
//
//void DestroyPCTNDeclaration()
//{
//	ReleaseCOM(VertexPCTN::Decl);
//}