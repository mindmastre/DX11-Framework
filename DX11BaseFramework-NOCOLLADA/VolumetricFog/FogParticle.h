#pragma once

#include "../Common/dx11Util.h"

// Forward declarations
class VolumetricFog;
class ParticlePool;

class FogParticle
{
public:
    ParticlePool *m_pParticlePool;
    UINT		m_i,m_j,m_k;
    UINT		m_uIndex;
    XMCOLOR	m_cScatteringColor;
    bool		m_bVisible;
public:
    FogParticle();
    FogParticle(UINT i, UINT j, UINT k,ParticlePool *pParticlePool);
    ~FogParticle();
    Vector3* GetPosition();
    Vector3* GetPositionFromLastBuffer();
    double		 GetViewDistance();
};


class ParticlePool
{
    friend class ParticleEnumerator;
    friend class FogParticle;
public:
    ParticlePool();
    ~ParticlePool();
    void SortbyViewDistances(Vector3 &vLookDir);
    void UpdateParticlePositions( double fTime );
    bool AddParticle(UINT i, UINT j, UINT k);
    bool Setup( VolumetricFog *pVolumetricFog, UINT uNumParticles );
    void Cleanup();

protected:
    VolumetricFog *m_pVolumetricFog;
    std::vector< FogParticle* >	m_v_pFogParticles[2];
    UINT			m_uNumParticles;	
    Vector3		*m_pvPositions[2];
    double			*m_pfViewDistances;
    double          m_PreTime[2];
    
public:
    Vector3     m_vWindVelocity;
    UINT            m_iCurrentBuffer;

};


class ParticleEnumerator
{
public:
    ParticleEnumerator( ParticlePool *pParticlePool );
    ~ParticleEnumerator();
    FogParticle* NextParticle();
    FogParticle* NextParticleFromLastBuffer();
    void Reset();
private:
    ParticlePool *m_pParticlePool;
    UINT m_uIndex;
};


