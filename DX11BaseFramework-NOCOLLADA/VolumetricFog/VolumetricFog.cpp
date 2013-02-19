#include "VolumetricFog.h"

using namespace std;

const int iMaxColorInterval = 1000;

inline float OpticalLength(float fLineDensity)
{
    return OPTICAL_LENGTH_FACTOR * fLineDensity;
}

float Phase( Vector3 vIn, Vector3 vOut )
{
	vIn = vIn.normalize();
    vOut = vOut.normalize();
	float dotP = vIn*vOut;
    return (float)(( 1.0 + SQUARE( dotP ) )* 3.0/4.0);
}

VolumetricFog::VolumetricFog():
	fogSize(Vector3()),
    cellSize( 0.f ),
    length( 0 ),
    width( 0 ),
    high( 0 ),
    timeA(0),
	totalTime(0)
{
    //for double buffer implementation
    colorUpdateInterval[0] = 0;
    colorUpdateInterval[1] = 1; 
}

bool VolumetricFog::Setup( ID3D11Device* pDevice, Environment *Env, FogProperties *Fog, Vector3 g_pvViewpoint )
{
    if (pDevice != NULL)
        device = pDevice;
    device->AddRef();

	fogSize = Fog->size;
    cellSize = Fog->particleSize;
    length = (int)( fogSize.x/cellSize+0.5 );
    high = (int)( fogSize.y/cellSize+0.5 );
    width = (int)( fogSize.z/cellSize+0.5 );
    evolvingSpeed = Fog->evolvingSpeed;
    fogPos = Fog->fogPos;
    
	textureFile = Fog->textureFile;

    windVelocity = Env->windVelocity;

    sunColorIntensity = Env->sunColorIntensity;
    sunColor.r = Env->sunColor.r*sunColorIntensity;
    sunColor.g = Env->sunColor.g*sunColorIntensity;
    sunColor.b = Env->sunColor.b*sunColorIntensity;
    
    sunlightDir = Env->sunlightDir;
    //D3DXVec3Normalize( &sunlightDir, &sunlightDir );
	sunlightDir = sunlightDir.normalize();

    viewpoint = g_pvViewpoint;

    simulator.Setup( length, width, high );
    GenerateFogParticles();
    fogShader.Setup(pDevice, this, 1.2f*cellSize, 2000 );

    particlePool.m_vWindVelocity = Env->windVelocity;


    return true;
}


void VolumetricFog::Cleanup()
{
    fogShader.Cleanup();

    particlePool.Cleanup();

    simulator.Cleanup();
    
    if( device )
    {
        device->Release();
        device = NULL;
    }
}


VolumetricFog::~VolumetricFog()
{
}


XMCOLOR	VolumetricFog::CalculateParticleIncidentColor( FogParticle* pFogParticle )
{
    float fDensity;
    float fOpticalDepth;
    float fTransparency;

    Vector3 vCurPt = Vector3((float)pFogParticle->m_i,(float)pFogParticle->m_j,(float)pFogParticle->m_k) 
                        + ( sunlightDir * -1.0f ) * SAMPLE_LENGTH;

    XMCOLOR cIncidentColor = sunColor;
    float fAlpha = 1.5 * SCATTER_FACTOR;
    while( simulator.IsPointInSpace(&vCurPt) )
    {
        fDensity = simulator.GetPointDensity( &vCurPt );
        fOpticalDepth = OpticalLength( fDensity * SAMPLE_LENGTH ); 		
        fTransparency = (float)exp( - fOpticalDepth );
        cIncidentColor.r *= ( ( 1 - fAlpha ) * fTransparency + fAlpha );
		cIncidentColor.g *= ( ( 1 - fAlpha ) * fTransparency + fAlpha );
		cIncidentColor.b *= ( ( 1 - fAlpha ) * fTransparency + fAlpha );
		cIncidentColor.a *= ( ( 1 - fAlpha ) * fTransparency + fAlpha );
        vCurPt += ( sunlightDir * -1.0f) * SAMPLE_LENGTH;
    }
    
    return cIncidentColor;
}

XMCOLOR	VolumetricFog::CalculateParticleScatteringColor( FogParticle* pFogParticle )
{
    UINT i = pFogParticle->m_i;
    UINT j = pFogParticle->m_j;
    UINT k = pFogParticle->m_k;
    XMCOLOR cScatteringColor;

    float fDensity = simulator.GetCellDensity( i,j,k );

    if( fDensity < MIN_DENSITY )
    {
        pFogParticle->m_bVisible = false;
        cScatteringColor = XMCOLOR(0,0,0,0);
        pFogParticle->m_cScatteringColor = cScatteringColor;
        return cScatteringColor;
    }
    else
    {
        pFogParticle->m_bVisible = true;

        XMCOLOR cIncidentColor;

       cIncidentColor = CalculateParticleIncidentColor( pFogParticle );

        float fOpticalDepth = OpticalLength( fDensity );
        float fTransparency = (float)exp( - fOpticalDepth );

        Vector3 vViewDir = *(pFogParticle->GetPosition()) - viewpoint;
        cScatteringColor = cIncidentColor
                           * ( (float)(( 1 - fTransparency ) * Phase( sunlightDir, vViewDir) * SCATTER_FACTOR) );

        cScatteringColor.a = 1 - fTransparency; //particle's alpha value = 1 - m_fAttenuation

        pFogParticle->m_cScatteringColor = cScatteringColor;

        return cScatteringColor;
    }
}


bool VolumetricFog::GenerateFogParticles()
{
    bool ret;
    ret = particlePool.Setup( this, simulator.GetNumCellInVolume() );
    if( !ret ) return false;
    for( int i = 0; i < length; ++i )
    {
        for( int j = 0; j < high; ++j)
        {
            for( int k = 0; k < width; ++k )
            {
                if( simulator.IsCellInVolume(i,j,k) )
                {
                    ret = particlePool.AddParticle(i,j,k);
                    if( !ret ) 
					{
						return false;
					}
                }
            }
        }
    }
    return true;
}

void VolumetricFog::UpdateFogParticleColors()
{
    ParticleEnumerator Enumerator( &particlePool );
    FogParticle *pCurParticle = Enumerator.NextParticle();
    while( pCurParticle )
    {
        CalculateParticleScatteringColor( pCurParticle );
        pCurParticle = Enumerator.NextParticle();
    }
}

void VolumetricFog::SortFogParticles(Vector3 &vLookDir)
{
    particlePool.SortbyViewDistances(vLookDir);
}


void VolumetricFog::UpdateFogPosition(double fTime)
{
	if(time == 0)
	{
		time = fTime;
	}

    Vector3 vDisplacement = windVelocity * (float)(fTime-time);
    fogPos += vDisplacement;
    particlePool.UpdateParticlePositions( fTime );

	time = fTime;

}

void VolumetricFog::Render(DX11Camera* gCamera)
{
     fogShader.Render(device, gCamera);
}


void VolumetricFog::AdvanceTime(double fTime, int interval, DX11Camera* gCamera)
{
	totalTime += fTime;
    //Double buffer: switch buffer index between 0 and 1. 
    particlePool.m_iCurrentBuffer = 1 - particlePool.m_iCurrentBuffer;

	XMFLOAT3 vp = gCamera->GetPosition();
	viewpoint = Vector3(vp.x, vp.y, vp.z);

    // change fog density
    if (evolvingSpeed != 1.0f) // if not pause evolving
    {
        float fAlpha = (float)( fTime - timeA ) / evolvingSpeed;
        simulator.InterpolateDensitySpace( fAlpha);
        if( ( fTime < timeA )|| ( fTime > (timeA + evolvingSpeed)))
        {
			if(totalTime > 500.0)
				timeA = fTime;
        }
    }

    UpdateFogPosition( fTime );
	SortFogParticles((Vector3 &)(gCamera->GetLook()));    

    if ((colorUpdateInterval[particlePool.m_iCurrentBuffer]%interval) == 0)
        UpdateFogParticleColors();
    ++colorUpdateInterval[particlePool.m_iCurrentBuffer];
    if (colorUpdateInterval[particlePool.m_iCurrentBuffer] == iMaxColorInterval)
	{
        colorUpdateInterval[particlePool.m_iCurrentBuffer] = 0;
	}
}

void VolumetricFog::SetEvolvingSpeed(float Speed)
{
    evolvingSpeed = Speed;
}

void VolumetricFog::SetSunColor(float r, float g, float b, float i)
{
    sunColor.r = r * i;
    sunColor.g = g * i;
    sunColor.b = b * i;
}

void VolumetricFog::SetWindVelocity(float v)
{
    windVelocity.z = v;
    particlePool.m_vWindVelocity.z = v;
}

void VolumetricFog::UpdateViewDistance()
{
    Vector3 relation_pos = fogPos+Vector3(fogSize/2.0f) - viewpoint;
    //viewDistances = sqrt( D3DXVec3Dot(&relation_pos, &relation_pos) );
	viewDistances = sqrt( relation_pos *relation_pos);
}
