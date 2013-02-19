#pragma once
#include "../Common/dx11Util.h"

// SSE2 and SSE4.1
#include <emmintrin.h>
#include <smmintrin.h>

//-------Packing
inline void GetVarPacks_SSE(__m128 vPointXPack, __m128 vPointYPack, __m128 vPointZPack, __m128i* i_pack, __m128i* j_pack, __m128i* k_pack, 
							__m128* r_pack, __m128* s_pack, __m128* t_pack)
{	
	// _mm_cvttps_epi32(a): ret = [(int)a0, (int)a1, (int)a2, (int)a3]
	*i_pack =  _mm_cvttps_epi32(vPointXPack);
	*j_pack =  _mm_cvttps_epi32(vPointYPack);
	*k_pack =  _mm_cvttps_epi32(vPointZPack);
	
	// _mm_cvtepi32_ps(a): ret = [(float)a0, (float)a1, (float)a2, (float)a3]
	// _mm_sub_ps(a, b): ret = [a0-b0, a1-b1, a2-b2, a3-b3]
	__m128 tmp;

	tmp = _mm_cvtepi32_ps(*i_pack);

	*r_pack = _mm_sub_ps( vPointXPack, tmp);

	tmp = _mm_cvtepi32_ps(*j_pack);

	*s_pack = _mm_sub_ps( vPointYPack, tmp);

	tmp = _mm_cvtepi32_ps(*k_pack);

	*t_pack = _mm_sub_ps( vPointZPack, tmp);
}

// Pack version of linear interpolation 
inline __m128 lerp_SSE(__m128 a_pack, __m128 b_pack, __m128 t_pack)
{		
	__m128 tmp;

	// ret = (b - a)*t + a;
	// _mm_sub_ps(a, b): ret = [a0-b0, a1-b1, a2-b2, a3-b3]
	// _mm_mul_ps(a, b): ret = [a0*b0, a1*b1, a2*b2, a3*b3]
	// _mm_add_ps(a, b): ret = [a0+b0, a1+b1, a2+b2, a3+b3]
	tmp = _mm_sub_ps(b_pack, a_pack);
	tmp = _mm_mul_ps(tmp, t_pack);
	return _mm_add_ps(tmp, a_pack);
}

//-----------------------------------------------------------------------------
// Forward declarations
//-----------------------------------------------------------------------------
#define SUPPLY_INTERVAL 5	//the number of frames passed supply vapoar 
#define EXTINCT_FACTOR 0.1	
#define fRANDOM			(((float)rand())/RAND_MAX) //this is not thread safe and will not be as random as it could be
#define INDEX(i,j,k)	((i)*m_iHeight*m_iWidth+(j)*m_iWidth+(k))
#define SQUARE(r)		((r)*(r))

//-----------------------------------------------------------------------------
// Name: class SimulationSpace
// Desc: 
//-----------------------------------------------------------------------------
class SimulationSpace
{
	friend class Geometry;
public:
	int 		m_iLength, m_iWidth, m_iHeight;
	UINT		m_uNumCellInVolume;
	UINT		m_uTotalNumCells;
protected:
	PBYTE		m_pShapeSpace;
	PFLOAT		m_pHumProbSpace;
	PFLOAT		m_pExtProbSpace;
	PFLOAT		m_pActProbSpace;

	UINT		m_uLastPhaseIndex; 
	UINT		m_uNextPhaseIndex; 
	PBYTE		m_apHumSpace[2];
	PBYTE		m_apCldSpace[2];
	PBYTE		m_apActSpace[2];
	PBYTE		m_pActFactorSpace;

	PFLOAT		m_apDensitySpace[2];
	PFLOAT		m_pMidDensitySpace;
	PFLOAT		m_pCurrentDensitySpace;
	int			m_iElapsedSteps;


public:
	SimulationSpace();
	virtual ~SimulationSpace();
	bool	Setup( UINT uLength, UINT uWidth, UINT uHigh );
	void	Cleanup();
	void	ShapeVolume();
	void	InitProbSpace();

	void	GrowFog(UINT uPhaseIndex );
	void	ExtinctFog( UINT uPhaseIndex);
	void	SupplyVapor(UINT uPhaseIndex);

	void	InterpolateDensitySpace( float fAlpha);
	float	GetCellDensity( int i, int j, int k );
	float	GetPointDensity( Vector3 *pvPoint );

	bool	IsCellInVolume( int i, int j, int k, int* pIndex = NULL );
	bool	IsCellInSpace( int i, int j, int k );
	void	InitCellInVolume( int i, int j, int k, float fProbSeed );
	bool	IsPointInSpace( Vector3 *pvPoint );
	UINT	GetNumCellInVolume(){ return m_uNumCellInVolume; }
	
protected:
	void	SetByteCell( PBYTE pByteSpace, int i, int j, int k, BYTE value);
	BYTE	GetByteCell( PBYTE pByteSpace, int i, int j, int k );
	bool	NewByteSpace( int size, PBYTE *ppBitSpace );
	bool	NewFloatSpace( int size, PFLOAT *ppFloatSpace );
	void	UpdateActFactorSpace(UINT uPhaseIndex);
	void	CelluarAutomate(UINT uPhaseIndex);
	void	CalculateDensity( UINT uPhaseIndex );
};
