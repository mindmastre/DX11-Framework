#pragma once
#include "../Common/dx11util.h"

#include "FogParticle.h"
#include "../DX11Camera.h"

class VolumetricFog;


struct PARTICLE_RENDERSTRUCT{
    Vector3 vecPos; // Coordinates of particle
    Vector2 vecOffset; // Vertex coordinate offsets
    float u, v; // Texture coordinates
    DWORD Diffuse; // Diffuse color of particle
};

class FogShader{
private:
    VolumetricFog 		*m_pVolumetricFog; 
    
    float					m_fParticleSize; // Size of particle
    ID3D11Buffer* m_pVB;      //Vertex buffer
    ID3D11Buffer*	m_pIB;
    ID3DX11Effect*            m_pEffect;  // D3DX effect interface
    ID3DX11EffectShaderResourceVariable*		m_pTexture; // the Fog texture
    
    //IDirect3DVertexDeclaration9* m_Decl;
    
    int						m_iNumParticlesPerBuffer;

public:
    FogShader();
    ~FogShader();
    bool Setup(ID3D11Device* dev, VolumetricFog* VolumetricFog, float fParticleSize, int iNumParticlesPerBuffer = 32);	
    void Cleanup();
    inline void SetParticleSize(float fSize){ m_fParticleSize = fSize;}	
    void SetParticleRS();
    void UnSetParticleRS();
    void Render(ID3D11Device* dev, DX11Camera* gCamera);
    static inline DWORD FToW(float f){return *((DWORD*)&f);}
};


