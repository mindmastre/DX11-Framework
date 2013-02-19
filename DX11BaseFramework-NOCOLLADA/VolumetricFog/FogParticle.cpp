#include "FogParticle.h"
#include "VolumetricFog.h"

using namespace std;

FogParticle::FogParticle()
{
    memset( this,0,sizeof(FogParticle) );
}

FogParticle::FogParticle(UINT i, UINT j, UINT k, ParticlePool *pParticlePool):
    m_i(i),
    m_j(j),
    m_k(k),
    m_pParticlePool(pParticlePool),
    m_bVisible(false)
{
}

FogParticle::~FogParticle()
{
}


Vector3* FogParticle::GetPosition()
{
    //Update thread, get data from current buffer
    assert( m_pParticlePool && m_pParticlePool->m_pvPositions[m_pParticlePool->m_iCurrentBuffer] );
    return &( m_pParticlePool->m_pvPositions[m_pParticlePool->m_iCurrentBuffer][m_uIndex] );
}

Vector3* FogParticle::GetPositionFromLastBuffer()
{
    //Render thread, get data from last buffer
    assert( m_pParticlePool && m_pParticlePool->m_pvPositions[1-m_pParticlePool->m_iCurrentBuffer] );
    return &( m_pParticlePool->m_pvPositions[1-m_pParticlePool->m_iCurrentBuffer][m_uIndex] );
}

double FogParticle::GetViewDistance()
{
    assert( m_pParticlePool && m_pParticlePool->m_pfViewDistances );
    return m_pParticlePool->m_pfViewDistances[m_uIndex];
}

ParticlePool::ParticlePool():
    m_uNumParticles(0),
    m_pfViewDistances(NULL),
    m_pVolumetricFog(NULL),
    m_iCurrentBuffer(0)
{
    //these are for double buffer implementation
    m_pvPositions[0] = NULL;
    m_pvPositions[1] = NULL;
    m_PreTime[0] = 0.0;
    m_PreTime[1] = 0.0;
}
    
ParticlePool::~ParticlePool()
{
}



bool  CompareViewDistance( FogParticle* pElem1, FogParticle* pElem2)
{
    return ( pElem1->GetViewDistance() > pElem2->GetViewDistance() );
}


void ParticlePool::SortbyViewDistances(Vector3 &vLookDir)
{
    Vector3 vToParticle;
    
    for( UINT i = 0; i < m_uNumParticles; ++i )
    {
        vToParticle = m_pvPositions[m_iCurrentBuffer][i] - m_pVolumetricFog->fogPos;
        /*m_pfViewDistances[i] = D3DXVec3Dot(&vLookDir, &vToParticle);*/
		m_pfViewDistances[i] = vLookDir * vToParticle;
    }

    sort(m_v_pFogParticles[m_iCurrentBuffer].begin(), m_v_pFogParticles[m_iCurrentBuffer].end(), CompareViewDistance);

}

void ParticlePool::UpdateParticlePositions( double fTime )
{
    if ((m_PreTime[0] == 0.0) || (m_PreTime[1] == 0.0))
    {
        //The first frame, init two time members
        m_PreTime[0] = fTime;
        m_PreTime[1] = fTime;
    }
    float fElapsedTime = (float)(fTime - m_PreTime[m_iCurrentBuffer]);
    Vector3 vDisplacement = m_vWindVelocity * fElapsedTime;
    for( UINT i = 0; i < m_uNumParticles; ++i  )
    {
        m_pvPositions[m_iCurrentBuffer][i] += vDisplacement;
    }
    m_PreTime[m_iCurrentBuffer] = fTime;
}

bool ParticlePool::Setup( VolumetricFog *pVolumetricFog, UINT uNumParticles )
{
    m_pVolumetricFog = pVolumetricFog;

    m_pfViewDistances = new double[uNumParticles];
    if( !m_pfViewDistances ) return false;

    m_pvPositions[0] = new Vector3[uNumParticles];
    if( !m_pvPositions[0] ) return false;

    m_pvPositions[1] = new Vector3[uNumParticles];
    if( !m_pvPositions[1] ) return false;
    
    m_uNumParticles = uNumParticles;
    return true;
}

void ParticlePool::Cleanup()
{
    if( m_pfViewDistances )
        delete[] m_pfViewDistances;

    //cleanup double buffer data
    if( m_pvPositions[0] )
        delete[] m_pvPositions[0];
    if( m_pvPositions[1] )
        delete[] m_pvPositions[1];

    vector< FogParticle* >::iterator itCurCP, itEndCP = m_v_pFogParticles[0].end();
    for( itCurCP = m_v_pFogParticles[0].begin(); itCurCP != itEndCP; ++ itCurCP )
    {
        delete ( * itCurCP );
    }
    m_v_pFogParticles[0].clear();
    vector< FogParticle* >::iterator itCurCP2, itEndCP2 = m_v_pFogParticles[1].end();
    for( itCurCP2 = m_v_pFogParticles[1].begin(); itCurCP2 != itEndCP2; ++ itCurCP2 )
    {
        delete ( * itCurCP2 );
    }
    m_v_pFogParticles[1].clear();
}

bool ParticlePool::AddParticle(UINT i, UINT j, UINT k)
{
    UINT index = m_v_pFogParticles[0].size();
    if( index >= m_uNumParticles ) return false;

    FogParticle *pPreParticleBuffer = new FogParticle(i,j,k,this);
    if( pPreParticleBuffer == NULL ) return false;

    pPreParticleBuffer->m_uIndex = index;
    m_pvPositions[0][index] = m_pVolumetricFog->fogPos + Vector3( (float)i, (float)j, (float)k ) * m_pVolumetricFog->cellSize;

    //add to double buffer 1
    try
    {
        m_v_pFogParticles[0].push_back(pPreParticleBuffer);
    }
    catch( ... )
    {
        return false;
    }

    FogParticle *pCurrentParticleBuffer = new FogParticle(i,j,k,this);
    if( pCurrentParticleBuffer == NULL ) return false;

    pCurrentParticleBuffer->m_uIndex = index;
    m_pvPositions[1][index] = m_pVolumetricFog->fogPos + Vector3( (float)i, (float)j, (float)k ) * m_pVolumetricFog->cellSize;

    //add to double buffer 2
    try
    {
        m_v_pFogParticles[1].push_back(pCurrentParticleBuffer);
    }
    catch( ... )
    {
        return false;
    }
    return true;
}


ParticleEnumerator::ParticleEnumerator( ParticlePool *pParticlePool )
{
    m_pParticlePool = pParticlePool;
    m_uIndex = 0;
}

ParticleEnumerator::~ParticleEnumerator( )
{
}


FogParticle* ParticleEnumerator::NextParticle()
{
    //Update thread, get data from current buffer
    if( m_uIndex >= m_pParticlePool->m_uNumParticles )
        return NULL;
    else
        return m_pParticlePool->m_v_pFogParticles[m_pParticlePool->m_iCurrentBuffer][m_uIndex++];
}

FogParticle* ParticleEnumerator::NextParticleFromLastBuffer()
{
    //Render thread, get data from last buffer
    if( m_uIndex >= m_pParticlePool->m_uNumParticles )
        return NULL;
    else
        return m_pParticlePool->m_v_pFogParticles[1-m_pParticlePool->m_iCurrentBuffer][m_uIndex++];
}

void ParticleEnumerator::Reset()
{
    m_uIndex = 0;
}
