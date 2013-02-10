#pragma once

#include "Common\VectorTypes.h"
#include "Common\dx11Util.h"

struct PARTICLE_VERTEX
{
    VECTOR3 vPos;
    VECTOR2 vUV;
    float fLife;
    float fRot;
    DWORD Color;
};

struct PARTICLE
{
    VECTOR3 vPos;
    VECTOR3 vDir;
    VECTOR3 vMass;
    DWORD Color;
    float fRadius;
    float fLife;
    float fFade;
    float fRot;
    float fRotRate;
    bool bVisible;
};

enum PARTICLE_SYSTEM_TYPE
{
    PST_DEFAULT = 0,
    PST_MUSHROOM,
    PST_STALK,
    PST_GROUNDEXP,
    PST_LANDMIND,
};

HRESULT CreateParticleArray( UINT MaxParticles );
void DestroyParticleArray();
void CopyParticlesToVertexBuffer( PARTICLE_VERTEX* pVB, VECTOR3 vEye, VECTOR3 vRight, VECTOR3 vUp );
float RPercent();
void InitParticleArray( UINT NumParticles );
UINT GetNumActiveParticles();

//-----------------------------------------------------------------------
class SuperParticleSystem
{
protected:
    UINT m_NumParticles;
    PARTICLE* m_pParticles;

    float m_fSpread;
    float m_fLifeSpan;
    float m_fStartSize;
    float m_fEndSize;
    float m_fSizeExponent;
    float m_fStartSpeed;
    float m_fEndSpeed;
    float m_fSpeedExponent;
    float m_fFadeExponent;
    float m_fRollAmount;
    float m_fWindFalloff;

    UINT m_NumStreamers;
    float m_fSpeedVariance;
    VECTOR3 m_vDirection;
    VECTOR3 m_vDirVariance;

    VECTOR4 m_vColor0;
    VECTOR4 m_vColor1;

    VECTOR3 m_vPosMul;
    VECTOR3 m_vDirMul;

    float m_fCurrentTime;
    VECTOR3 m_vCenter;
    float m_fStartTime;

    VECTOR4 m_vFlashColor;

    bool m_bStarted;

    PARTICLE_SYSTEM_TYPE m_PST;

public:
                    SuperParticleSystem();
    virtual         ~SuperParticleSystem();

    HRESULT         CreateParticleSystem( UINT NumParticles );
    void            SetSystemAttributes( VECTOR3 vCenter,
                                         float fSpread, float fLifeSpan, float fFadeExponent,
                                         float fStartSize, float fEndSize, float fSizeExponent,
                                         float fStartSpeed, float fEndSpeed, float fSpeedExponent,
                                         float fRollAmount, float fWindFalloff,
                                         UINT NumStreamers, float fSpeedVariance,
                                         VECTOR3 vDirection, VECTOR3 vDirVariance,
                                         VECTOR4 vColor0, VECTOR4 vColor1,
                                         VECTOR3 vPosMul, VECTOR3 vDirMul );

    void            SetCenter( VECTOR3 vCenter );
    void            SetStartTime( float fStartTime );
    void            SetStartSpeed( float fStartSpeed );
    void            SetFlashColor( VECTOR4 vFlashColor );
    VECTOR4     GetFlashColor();
    float           GetCurrentTime();
    float           GetLifeSpan();
    UINT            GetNumParticles();
    VECTOR3     GetCenter();

    virtual void    Init();
    virtual void    Update( float fTime, float fElapsedTime, VECTOR3 vRight, VECTOR3 vUp,
                                   VECTOR3 vWindVel, VECTOR3 vGravity );
};

//-----------------------------------------------------------------------
class CMushroomParticleSystem : public SuperParticleSystem
{
public:
                    CMushroomParticleSystem();
    virtual         ~CMushroomParticleSystem();

    virtual void    Init();
    virtual void    Update( float fTime, float fElapsedTime, VECTOR3 vRight, VECTOR3 vUp,
                                   VECTOR3 vWindVel, VECTOR3 vGravity );
};

//-----------------------------------------------------------------------
class CStalkParticleSystem : public SuperParticleSystem
{
public:
                    CStalkParticleSystem();
    virtual         ~CStalkParticleSystem();

    virtual void    Init();
    virtual void    Update( float fTime, float fElapsedTime, VECTOR3 vRight, VECTOR3 vUp,
                                   VECTOR3 vWindVel, VECTOR3 vGravity );
};

//-----------------------------------------------------------------------
class CGroundBurstParticleSystem : public SuperParticleSystem
{
public:
                    CGroundBurstParticleSystem();
    virtual         ~CGroundBurstParticleSystem();

    virtual void    Init();
    virtual void    Update( float fTime, float fElapsedTime, VECTOR3 vRight, VECTOR3 vUp,
                                   VECTOR3 vWindVel, VECTOR3 vGravity );
};

//-----------------------------------------------------------------------
class CLandMineParticleSystem : public SuperParticleSystem
{
public:
                    CLandMineParticleSystem();
    virtual         ~CLandMineParticleSystem();

    virtual void    Init();
    virtual void    Update( float fTime, float fElapsedTime, VECTOR3 vRight, VECTOR3 vUp,
                                   VECTOR3 vWindVel, VECTOR3 vGravity );
};

