#ifndef DX11UTIL_H
#define DX11UTIL_H

#if defined(DEBUG) || defined(_DEBUG)
#define _CRTDBG_MAP_ALLOC
#include <crtdbg.h>
#endif

#include <d3dx11.h>
#include "d3dx11Effect.h"
#include <xnamath.h>
#include "xnacollision.h"
#include "../Vertex.h"
#include "../Model Loader/ColladaVertex.h"
#include <dxerr.h>
#include <cassert>
#include <ctime>
#include <algorithm>
#include <string>
#include <sstream>
#include <fstream>
#include <vector>
#include "MathHelper.h"
#include "LightHelper.h"
#include <Windows.h>
//#include <d3dx9.h>
//#include <d3d9.h>
#include <map>

#define TEXTUREPATH "../Assets/Textures/"

//Old DX9 declarations
//class D3D9App;
//extern D3D9App* gd3dApp;
//extern IDirect3DDevice9* gd3d9Device;
//---------------------------------------------------------------------------------------
// Simple d3d error checker
//---------------------------------------------------------------------------------------

#if defined(DEBUG) | defined(_DEBUG)
	#ifndef HR
	#define HR(x)                                              \
	{                                                          \
		HRESULT hr = (x);                                      \
		if(FAILED(hr))                                         \
		{                                                      \
			DXTrace(__FILE__, (DWORD)__LINE__, hr, L#x, true); \
		}                                                      \
	}
	#endif

#else
	#ifndef HR
	#define HR(x) (x)
	#endif
#endif 


//---------------------------------------------------------------------------------------
// Convenience macro for releasing COM objects.
//---------------------------------------------------------------------------------------

#define ReleaseCOM(x) { if(x){ x->Release(); x = 0; } }

//---------------------------------------------------------------------------------------
// Convenience macro for deleting objects.
//---------------------------------------------------------------------------------------

#define SafeDelete(x) { delete x; x = 0; }
#ifndef SafeDeleteArray
#define SafeDeleteArray(p) { if (p) { delete[] (p);   (p)=NULL; } }
#endif    
#ifndef SafeRelease
#define SafeRelease(p)      { if (p) { (p)->Release(); (p)=NULL; } }
#endif

//---------------------------------------------------------------------------------------
// Utility classes.
//---------------------------------------------------------------------------------------

class d3dHelper
{
public:
	///<summary>
	/// 
	/// Does not work with compressed formats.
	///</summary>
	static ID3D11ShaderResourceView* CreateTexture2DArraySRV(
		ID3D11Device* device, ID3D11DeviceContext* context,
		std::vector<std::wstring>& filenames,
		DXGI_FORMAT format = DXGI_FORMAT_FROM_FILE,
		UINT filter = D3DX11_FILTER_NONE, 
		UINT mipFilter = D3DX11_FILTER_LINEAR);

	static ID3D11ShaderResourceView* CreateRandomTexture1DSRV(ID3D11Device* device);
};

class TextHelper
{
public:

	template<typename T>
	static D3DX11INLINE std::wstring ToString(const T& s)
	{
		std::wostringstream oss;
		oss << s;

		return oss.str();
	}

	template<typename T>
	static D3DX11INLINE T FromString(const std::wstring& s)
	{
		T x;
		std::wistringstream iss(s);
		iss >> x;

		return x;
	}
};

// Order: left, right, bottom, top, near, far.
void ExtractFrustumPlanes(XMFLOAT4 planes[6], CXMMATRIX M);


// #define XMGLOBALCONST extern CONST __declspec(selectany)
//   1. extern so there is only one copy of the variable, and not a separate
//      private copy in each .obj.
//   2. __declspec(selectany) so that the compiler does not complain about
//      multiple definitions in a .cpp file (it can pick anyone and discard 
//      the rest because they are constant--all the same).

namespace Colors
{
	XMGLOBALCONST XMVECTORF32 White     = {1.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Black     = {0.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Red       = {1.0f, 0.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Green     = {0.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Blue      = {0.0f, 0.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Yellow    = {1.0f, 1.0f, 0.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Cyan      = {0.0f, 1.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Magenta   = {1.0f, 0.0f, 1.0f, 1.0f};
	XMGLOBALCONST XMVECTORF32 Silver    = {0.75f, 0.75f, 0.75f, 1.0f};
	XMGLOBALCONST XMVECTORF32 LightSteelBlue = {0.69f, 0.77f, 0.87f, 1.0f};
}
//
//struct Mtrl
//{
//	Mtrl()
//		:ambient(D3DXCOLOR()), diffuse(D3DXCOLOR()), spec(D3DXCOLOR()), specPower(8.0f){}
//	Mtrl(const D3DXCOLOR& a, const D3DXCOLOR& d, 
//		 const D3DXCOLOR& s, float power)
//		:ambient(a), diffuse(d), spec(s), specPower(power){}
//
//	D3DXCOLOR ambient;
//	D3DXCOLOR diffuse;
//	D3DXCOLOR spec;
//	D3DXCOLOR emis;
//	float specPower;
//};

//void LoadXFile(const std::string& filename, ID3DXMesh** meshOut, std::vector<Mtrl>& mtrls, std::vector<IDirect3DTexture9*>& texs);

///<summary>
/// Utility class for converting between types and formats.
///</summary>
class Convert
{
public:
	///<summary>
	/// Converts XMVECTOR to XMCOLOR, where XMVECTOR represents a color.
	///</summary>
	static D3DX11INLINE XMCOLOR ToXmColor(FXMVECTOR v)
	{
		XMCOLOR dest;
		XMStoreColor(&dest, v);
		return dest;
	}

	///<summary>
	/// Converts XMVECTOR to XMFLOAT4, where XMVECTOR represents a color.
	///</summary>
	static D3DX11INLINE XMFLOAT4 ToXmFloat4(FXMVECTOR v)
	{
		XMFLOAT4 dest;
		XMStoreFloat4(&dest, v);
		return dest;
	}

	static D3DX11INLINE UINT ArgbToAbgr(UINT argb)
	{
		BYTE A = (argb >> 24) & 0xff;
		BYTE R = (argb >> 16) & 0xff;
		BYTE G = (argb >>  8) & 0xff;
		BYTE B = (argb >>  0) & 0xff;

		return (A << 24) | (B << 16) | (G << 8) | (R << 0);
	}

};
//struct VertexPCTN
//{
//	VertexPCTN()
//		: pos(0.0f, 0.0f, 0.0f),
//		normal(0.0f, 0.0f, 0.0f),
//		tex0(0.0f, 0.0f), color(D3DCOLOR_XRGB(0,0,0)){}
//	VertexPCTN(float x, float y, float z, 
//		float nx, float ny, float nz,
//		float u, float v, D3DCOLOR col):pos(x,y,z), normal(nx,ny,nz), tex0(u,v), color(col){}
//	VertexPCTN(const D3DXVECTOR3& v, const D3DXVECTOR3& n, const D3DXVECTOR2& uv)
//		:pos(v),normal(n), tex0(uv){}
//
//	D3DXVECTOR3 pos;
//	D3DXVECTOR3 normal;
//	D3DXVECTOR2 tex0;
//	D3DCOLOR color;
//	static IDirect3DVertexDeclaration9* Decl;
//
//	enum FVF
//	{
//		FVF_Flags = D3DFVF_XYZ | D3DFVF_DIFFUSE
//	};
//
//};
//void InitPCTNDeclaration();
//void DestroyPCTNDeclaration();

#endif // dx11Util_H