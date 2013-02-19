#include "Simulation.h"

using namespace std;


SimulationSpace::SimulationSpace()
{
	memset( this, 0, sizeof( SimulationSpace ) );
}


SimulationSpace::~SimulationSpace()
{
	Cleanup();
}


bool SimulationSpace::Setup( UINT uLength, UINT uWidth, UINT uHigh )
{
	m_iLength = uLength;
	m_iWidth = uWidth; 
	m_iHeight = uHigh;
	int size = uLength * uWidth * uHigh;
	m_uLastPhaseIndex = 0;
	m_uNextPhaseIndex = 1;
	m_iElapsedSteps = 0;

	if(		NewByteSpace( size, &m_apHumSpace[0] )
		&& 	NewByteSpace( size, &m_apHumSpace[1] )
		&& 	NewByteSpace( size, &m_apCldSpace[0] )
		&& 	NewByteSpace( size, &m_apCldSpace[1] )
		&& 	NewByteSpace( size, &m_apActSpace[0] )
		&& 	NewByteSpace( size, &m_apActSpace[1] )
		&&	NewByteSpace( size, &m_pActFactorSpace )
		&& 	NewFloatSpace( size, &m_apDensitySpace[0] )
		&& 	NewFloatSpace( size, &m_apDensitySpace[1] )

		&& 	NewByteSpace( size, &m_pShapeSpace )
		&& 	NewFloatSpace( size, &m_pHumProbSpace )
		&& 	NewFloatSpace( size, &m_pExtProbSpace )
		&& 	NewFloatSpace( size, &m_pActProbSpace )
		&& 	NewFloatSpace( size, &m_pMidDensitySpace )
		)
	{
		m_uTotalNumCells = size;
		InitProbSpace();
		ShapeVolume();
		CelluarAutomate( m_uNextPhaseIndex );
		CalculateDensity( m_uNextPhaseIndex );
		return true;
	}
	else
		return false;
}

bool SimulationSpace::NewByteSpace( int size, PBYTE *ppBitSpace )
{
	*ppBitSpace = new BYTE[size];
	if( *ppBitSpace )
	{
		memset( *ppBitSpace, 0, size*sizeof(BYTE) );
		return true;
	}
	else
		return false;
}

bool SimulationSpace::NewFloatSpace( int size, PFLOAT *ppFloatSpace )
{
	*ppFloatSpace = new float[size];
	if( *ppFloatSpace )
	{
		memset( *ppFloatSpace, 0, size*sizeof(float) );
		return true;
	}
	else
		return false;
}


void SimulationSpace::Cleanup()
{
	SafeDeleteArray( m_pShapeSpace );
	SafeDeleteArray( m_pHumProbSpace );
	SafeDeleteArray( m_pExtProbSpace );
	SafeDeleteArray( m_pActProbSpace );
	SafeDeleteArray( m_apHumSpace[0] );
	SafeDeleteArray( m_apHumSpace[1] );
	SafeDeleteArray( m_apCldSpace[0] );
	SafeDeleteArray( m_apCldSpace[1] );
	SafeDeleteArray( m_apActSpace[0] );
	SafeDeleteArray( m_apActSpace[1] );
	SafeDeleteArray( m_pActFactorSpace );
	SafeDeleteArray( m_apDensitySpace[0] );
	SafeDeleteArray( m_apDensitySpace[1] );
	SafeDeleteArray( m_pMidDensitySpace );
}


//-----------------------------------------------------------------------------
// Name: SimulationSpace::InterpolateDensitySpace( float fAlpha )
// Desc: calculate the current density space by interpolating the density spaces of the last phase and the next phase
//-----------------------------------------------------------------------------
void SimulationSpace::InterpolateDensitySpace( float fAlpha)
{
	if( fAlpha <= 0.0 ) // fAlpha is the interpolation factor
	{
		m_pCurrentDensitySpace = m_apDensitySpace[m_uLastPhaseIndex];
	}
	else if( fAlpha >= 1.0 ) 
	{       
		// exchange the indexes of the last phase and the next phase;
		m_uLastPhaseIndex = m_uNextPhaseIndex;
		m_uNextPhaseIndex = !m_uLastPhaseIndex;

		// point current DensitySpace to the DensitySpace of last phase
		m_pCurrentDensitySpace = m_apDensitySpace[m_uLastPhaseIndex];

		// Create the next DensitySpace of the next phase
		CelluarAutomate( m_uNextPhaseIndex );
        CalculateDensity( m_uNextPhaseIndex );
	}
 	else
 	{
 		int index;
 
 		for( int i = 0; i < m_iLength; ++i )
 		{
 			for( int j = 0; j < m_iHeight; ++j)
 			{
 				for( int k = 0; k < m_iWidth; ++k )
 				{
 					if( ! IsCellInVolume(i,j,k,&index) ) continue;
 					m_pMidDensitySpace[index] = (float)(( 1.0 - fAlpha ) * m_apDensitySpace[m_uLastPhaseIndex][index] 
 												+ fAlpha * m_apDensitySpace[m_uNextPhaseIndex][index]);
 				}
 			}
 		}
 
 		m_pCurrentDensitySpace = m_pMidDensitySpace;	
 	}
}


float SimulationSpace::GetPointDensity( Vector3 *pvPoint )
{
	int i = (int)pvPoint->x;
	int j = (int)pvPoint->y;
	int k = (int)pvPoint->z;
	float r = pvPoint->x - i;
	float s = pvPoint->y - j;
	float uPhaseIndex = pvPoint->z - k;
	
	// get the densities of 8 points around the point.
	float d0 = GetCellDensity( i,  j,  k  );
	float d1 = GetCellDensity( i,  j,  k+1);
	float d2 = GetCellDensity( i,  j+1,k  );
	float d3 = GetCellDensity( i,  j+1,k+1);
	float d4 = GetCellDensity( i+1,j,  k  );
	float d5 = GetCellDensity( i+1,j,  k+1);
	float d6 = GetCellDensity( i+1,j+1,k  );
	float d7 = GetCellDensity( i+1,j+1,k+1);

	// interpolate densities
	float z01 = (d1 - d0)*uPhaseIndex + d0;
	float z23 = (d3 - d2)*uPhaseIndex + d2;
	float z45 = (d5 - d4)*uPhaseIndex + d4;
	float z67 = (d7 - d6)*uPhaseIndex + d6;
	float x0145 = (z45 - z01)*r + z01;
	float x2367 = (z67 - z23)*r + z23;
	float result = ((x2367 - x0145)*s + x0145);
	return result;
}


bool SimulationSpace::IsPointInSpace( Vector3 *pvPoint )
{
	if( ( pvPoint->x < 0 )|| ( pvPoint->x >= m_iLength )
		|| ( pvPoint->y < 0 ) || ( pvPoint->y >= m_iHeight )
		|| ( pvPoint->z < 0 ) || ( pvPoint->z >= m_iWidth ) )
		return false;
	else
		return true;
}

bool SimulationSpace::IsCellInSpace(int i, int j, int k )
{
	if( ( i < 0 )|| ( i >= m_iLength )
		|| ( j < 0 ) || ( j >= m_iHeight )
		|| ( k < 0 ) || ( k >= m_iWidth ) )
		return false;
	else
		return true;
}


bool SimulationSpace::IsCellInVolume(int i, int j, int k, int* pIndex )
{
	if( !IsCellInSpace(i,j,k) )
		return false;
	else
	{
		int index = INDEX(i,j,k);
		if( m_pShapeSpace[index] )
		{
			if( pIndex )
				*pIndex = index;
			return true;
		}
		else		
			return false;
	}
}


float SimulationSpace::GetCellDensity( int i, int j, int k )
{
	int index = INDEX( i, j, k );
	if( ( index < 0 )||( index >= (int)m_uTotalNumCells ) ) return 0;
	return m_pCurrentDensitySpace[index];
}


void SimulationSpace::CalculateDensity( UINT uPhaseIndex )
{
	int	index;
	for( int i = 0; i < m_iLength; ++i )
	{
		for( int j = 0; j < m_iHeight; ++j)
		{
			for( int k = 0; k < m_iWidth; ++k )
			{
				if( !IsCellInVolume(i,j,k,&index) ) continue;
				m_apDensitySpace[uPhaseIndex][index] = 0;

				// accumulate the binary Fog values of the cells surrouding the current cell(i,j,k) and itself.
				for(int p = i-1; p<=i+1; ++p)
					for(int q = j-1; q<=j+1; ++q)
						for(int r = k-1; r<=k+1; ++r)
								m_apDensitySpace[uPhaseIndex][index] += GetByteCell( m_apCldSpace[uPhaseIndex], p, q, r);
				m_apDensitySpace[uPhaseIndex][index] /= 27.0f; // 27 is the number of all iterations of above nesting loop.
			}
		}
	}
}


//-----------------------------------------------------------------------------
// Name: SimulationSpace::CelluarAutomate(UINT uPhaseIndex)
// Desc: update the simulation space.
//-----------------------------------------------------------------------------
void SimulationSpace::CelluarAutomate(UINT uPhaseIndex)
{
	ExtinctFog(!uPhaseIndex);

	GrowFog(uPhaseIndex);

	if( m_iElapsedSteps == 0 )
	{
		SupplyVapor(uPhaseIndex);
		m_iElapsedSteps = SUPPLY_INTERVAL;
	}
	else
		m_iElapsedSteps--;
}

void SimulationSpace::GrowFog(UINT uPhaseIndex)
{
	int index;

	UpdateActFactorSpace(!uPhaseIndex);

	for( int i = 0; i < m_iLength; i++ )
	{
		for( int j = 0; j < m_iHeight; j++)
		{
			for( int k = 0; k < m_iWidth; k++ )
			{
				if( !IsCellInVolume(i,j,k,&index) ) continue;
				m_apActSpace[uPhaseIndex][index] = ( ! m_apActSpace[!uPhaseIndex][index] ) && ( m_apHumSpace[!uPhaseIndex][index] ) && ( m_pActFactorSpace[index] );
				m_apHumSpace[uPhaseIndex][index] = m_apHumSpace[!uPhaseIndex][index] && ( ! m_apActSpace[!uPhaseIndex][index] );
				m_apCldSpace[uPhaseIndex][index] = m_apCldSpace[!uPhaseIndex][index] || m_apActSpace[!uPhaseIndex][index];
			}
		}
	}
}


void SimulationSpace::ExtinctFog( UINT uPhaseIndex )
{
	int index;

	for( int i = 0; i < m_iLength; i++ )
	{
		for( int j = 0; j < m_iHeight; j++)
		{
			for( int k = 0; k < m_iWidth; k++ )
			{
				if( !IsCellInVolume(i,j,k,&index) ) continue;
				m_apCldSpace[uPhaseIndex][index] = m_apCldSpace[uPhaseIndex][index] && ( fRANDOM > m_pExtProbSpace[index] );
			}
		}
	}
}

void SimulationSpace::SupplyVapor( UINT uPhaseIndex )
{
	int index;

	for( int i = 0; i < m_iLength; i++ )
	{
		for( int j = 0; j < m_iHeight; j++)
		{
			for( int k = 0; k < m_iWidth; k++ )
			{
				if( !IsCellInVolume(i,j,k,&index) ) continue;
				m_apHumSpace[uPhaseIndex][index] = m_apHumSpace[uPhaseIndex][index] || ( fRANDOM < m_pHumProbSpace[index] );
				m_apActSpace[uPhaseIndex][index] = m_apHumSpace[uPhaseIndex][index] && ( m_apActSpace[uPhaseIndex][index] || ( fRANDOM < m_pActProbSpace[index] ) );
				
			}
		}
	}
}

void SimulationSpace::UpdateActFactorSpace(UINT uPhaseIndex)
{
	for( int i = 0; i < m_iLength; i++ )
	{
		for( int j = 0; j < m_iHeight; j++)
		{
			for( int k = 0; k < m_iWidth; k++ )
			{
				if( !IsCellInVolume(i,j,k) ) continue;
				BYTE FAct =   GetByteCell( m_apActSpace[uPhaseIndex],i+1,j,k )	
							||GetByteCell( m_apActSpace[uPhaseIndex],i,j+1,k )
							||GetByteCell( m_apActSpace[uPhaseIndex],i,j,k+1 )
							||GetByteCell( m_apActSpace[uPhaseIndex],i-1,j,k )
							||GetByteCell( m_apActSpace[uPhaseIndex],i,j-1,k )
							||GetByteCell( m_apActSpace[uPhaseIndex],i,j,k-1 )
							||GetByteCell( m_apActSpace[uPhaseIndex],i-2,j,k )
							||GetByteCell( m_apActSpace[uPhaseIndex],i+2,j,k )
							||GetByteCell( m_apActSpace[uPhaseIndex],i,j-2,k )
							||GetByteCell( m_apActSpace[uPhaseIndex],i,j+2,k )
							||GetByteCell( m_apActSpace[uPhaseIndex],i,j,k-2 );
				
				SetByteCell( m_pActFactorSpace,i,j,k,FAct);
			}
		}
	}
}


void SimulationSpace::SetByteCell( PBYTE pByteSpace, int i, int j, int k, BYTE value )
{
	if( !IsCellInSpace( i,j,k ) ) return;
	pByteSpace[ INDEX(i,j,k)] = value;
}


BYTE SimulationSpace::GetByteCell( PBYTE pByteSpace, int i, int j, int k )
{
	if( !IsCellInSpace( i,j,k ) ) return 0;
	return pByteSpace[INDEX( i, j, k )];
}

void SimulationSpace::ShapeVolume()
{
	double cenX = m_iLength/2.0;
	double cenY = m_iHeight/2.0;
	double cenZ = m_iWidth/2.0;
	double distance;

	m_uNumCellInVolume = 0;
	float fProbSeed;
	for( int i = 0; i < m_iLength; i++ )
	{
		for( int j = 0; j < m_iHeight; j++)
		{
			for( int k = 0; k < m_iWidth; k++ )
			{
					distance = SQUARE(i-cenX) / SQUARE(cenX) 
							 + SQUARE(j-cenY) / SQUARE(cenY) 
							 + SQUARE(k-cenZ) / SQUARE(cenZ);
					if( distance < 1.0 )
					{
						fProbSeed = (float)exp( - distance );
						InitCellInVolume( i, j, k, fProbSeed );
					}
			}
		}
	}
}


void SimulationSpace::InitProbSpace()
{
	int fHigh = m_iHeight-1;
	for( int i = 0; i < m_iLength; i++ )
	{
		for( int j = 0; j < m_iHeight; j++)
		{
			for( int k = 0; k < m_iWidth; k++ )
			{
				m_pExtProbSpace[INDEX(i,j,k)] = (float)exp( -( fHigh-j )*EXTINCT_FACTOR );
			}
		}
	}
}


//-----------------------------------------------------------------------------
// Name: SimulationSpace::InitCellInVolume( int i, int j, int k, float fProbSeed )
// Desc: set the probablities of every cell.
//-----------------------------------------------------------------------------
void SimulationSpace::InitCellInVolume( int i, int j, int k, float fProbSeed )
{
	if( !IsCellInSpace( i,j,k ) ) return;
	int index = INDEX(i,j,k);
	if( m_pShapeSpace[index] == false )
	{
		m_pShapeSpace[index] = true;
		m_uNumCellInVolume++;
	}
	float fCurExtProb =  (float)0.2 * ( 1 - fProbSeed );
	float fCurHumProb =  (float)0.1 * fProbSeed;
	float fCurActProb =	 (float)0.001 * fProbSeed;

	m_pExtProbSpace[index] *= fCurExtProb;
	m_pHumProbSpace[index] = m_pHumProbSpace[index]*(1-fCurHumProb)+fCurHumProb;
	m_pActProbSpace[index] = m_pActProbSpace[index]*(1-fCurActProb)+fCurActProb;
}

