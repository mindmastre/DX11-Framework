#pragma once

#include <d3d9.h>
#include "Simulation.h"
#include "FogShader.h"
#include "FogParticle.h"
#include "../DX11Camera.h"

#define SAMPLE_LENGTH			0.5f 
#define OPTICAL_LENGTH_FACTOR	1.5f // determine the white and black contrast.more big more contrast.
#define SCATTER_FACTOR			0.6f // According to the scattering model used, to have the intensity of scattering color less than the incident color,
                                     // the maximum of SCATTER_FACTOR should be 2/3.
#define MIN_DENSITY				0.05f
#define SQUARE(r)		((r)*(r))

struct Environment
{
    Vector3			windVelocity;
    Vector3			sunlightDir;
    XMCOLOR			sunColor;
    float               sunColorIntensity;
};

struct FogProperties
{
	Vector3 size;
    float		particleSize;
    float		evolvingSpeed;
    Vector3 fogPos;
    LPCSTR		textureFile;
};


class VolumetricFog
{
public:
    Vector3 fogSize;// actual size of Fog in world space
    float				cellSize; // size of cell in world space.
    int 				length, width,high;
    Vector3			fogPos; // the coordinates of the left-down corner 
    Vector3			windVelocity;
    Vector3			viewpoint;
    Vector3			sunlightDir;
    XMCOLOR			sunColor;
    LPCSTR				textureFile;
    LPDIRECT3DTEXTURE9	texture;
    double				timeA;
	double				totalTime;
    float				evolvingSpeed;
    ID3D11Device*	device;
    ParticlePool		particlePool;
    float               sunColorIntensity;
    int                 colorUpdateInterval[2];

    float			 	viewDistances;
    double              time;

protected:
    SimulationSpace	simulator;
    FogShader		fogShader;
    
public:
    VolumetricFog();
    ~VolumetricFog();
    bool Setup( ID3D11Device* pDevice, Environment *Env, FogProperties *Fog, Vector3 g_pvViewpoint  );
    void Cleanup();
    void AdvanceTime(double fTime, int interval, DX11Camera* gCamera);
    void Render(DX11Camera* gCamera);

    bool GenerateFogParticles();
    void CleanupFogParticles();
    void UpdateFogParticleColors();
    void SortFogParticles(Vector3 &vLookDir);
    void UpdateFogPosition(double fTime);

    void SetEvolvingSpeed(float speed);
    void SetSunColor(float r, float g, float b,float i);
    void SetSunColorIntensity(float i);
	void SetSunDirection(Vector3 dir) { sunlightDir = dir; }
    void SetWindVelocity(float v);

    float	GetViewDistance(){return viewDistances;};
    void	UpdateViewDistance();

protected:
    XMCOLOR	CalculateParticleIncidentColor( FogParticle* pFogParticle );
    XMCOLOR	CalculateParticleScatteringColor( FogParticle* pFogParticle );
};

