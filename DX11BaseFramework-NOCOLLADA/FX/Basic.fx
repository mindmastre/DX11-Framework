#include "LightHelper.fx"
 
cbuffer cbPerFrame
{
	DirectionalLight gDirLights[3];
	float3 gEyePosW;

	float  gFogStart;
	float  gFogRange;
	float4 gFogColor;
	bool SSFlag;
	bool SobelFlag;
	bool ToonFlag;
	bool FogFlag;
	float RandomNumber;
	bool GlitterFlag;
	bool GlassFlag;
};

cbuffer cbPerObject
{
	float4x4 gWorld;
	float4x4 gWorldInvTranspose;
	float4x4 gWorldViewProj;
	float4x4 gTexTransform;
	Material gMaterial;
}; 

 const float2 COLORS[9] = {
        float2(-0.00078125, 0.00078125), 
        float2( 0.00 ,     0.00708125),
        float2( 0.00078125, 0.00078125),
        float2(-0.00078125, 0.00 ),
        float2( 0.0,       0.0),
        float2( 0.00078125, 0.0007 ),
        float2(-0.00078125,-0.00078125),
        float2( 0.00 ,    -0.00078125),
        float2( 0.00078125,-0.00078125),};

// Nonnumeric values cannot be added to a cbuffer.
Texture2D gDiffuseMap;
TextureCube gCubeMap;
Texture2D gNormalMap;

SamplerState samAnisotropic
{
	Filter = ANISOTROPIC;
	MaxAnisotropy = 4;

	AddressU = WRAP;
	AddressV = WRAP;
};
 
struct VertexIn
{
	float3 PosL    : POSITION;
	float3 NormalL : NORMAL;
	float2 Tex     : TEXCOORD;
};

struct VertexOut
{
	float4 PosH    : SV_POSITION;
    float3 PosW    : POSITION;
    float3 NormalW : NORMAL;
	float2 Tex     : TEXCOORD;
	float3 Pos : TEXCOORD2;
	float4 View : TEXCOORD1;
};

//Calculated Gaussian Blur, performs the blur based on V and R
float Gaussian(float v, float r)
{
	return 1.0f / sqrt(2.0f*3.14*v) * exp(-(r*r) / (2*v));
}

//Scattering Algorithm, Hard-coded for Ideal skin rendering though it still looks good on other stuff!
float3 Scatter( float r )
{
	//Coefficients from GPU Gems 3 - "Advanced Skin Rendering"
	return Gaussian(.0064f * 1.414, r) * float3(.233f,.455f,.649f) +
		   Gaussian(.0484f * 1.414, r) * float3(.1f,.336f,.344f) +
		   Gaussian(.187f * 1.414, r) * float3(.118f,.198f,0.0f) +
		   Gaussian(.567f * 1.414, r) * float3(.113f,.007f,.007f) +
		   Gaussian(1.99f * 1.414, r) * float3(.358f,.004f,0.0f) +
		   Gaussian(7.41f * 1.414, r) * float3(.078f,0.0f,0.0f) ;
}

float3 SkinDiffuse(float curv, float3 NdotL)
{
	float3 lookup = NdotL * .5 + .5;
	float3 diffuse;
	diffuse.r =  gDiffuseMap.Sample( samAnisotropic, float2(lookup.r,curv) ).r;
	diffuse.g = gDiffuseMap.Sample( samAnisotropic, float2(lookup.g,curv) ).g;
	diffuse.b =  gDiffuseMap.Sample( samAnisotropic, float2(lookup.b,curv) ).b;

	return diffuse;
}

VertexOut VS(VertexIn vin)
{
	VertexOut vout;
	
	// Transform to world space space.
	vout.PosW    = mul(float4(vin.PosL, 1.0f), gWorld).xyz;
	vout.NormalW = mul(vin.NormalL, (float3x3)gWorldInvTranspose);
		
	// Transform to homogeneous clip space.
	vout.PosH = mul(float4(vin.PosL, 1.0f), gWorldViewProj);
	
	// Output vertex attributes for interpolation across triangle.
	vout.Tex = mul(float4(vin.Tex, 0.0f, 1.0f), gTexTransform).xy;

	vout.Pos = float4(vin.PosL, 1.0f);

	vout.View = mul(gWorldViewProj, float4(-vin.PosL, 1.0f));

	return vout;
}
 
float4 PS(VertexOut pin, 
          uniform int gLightCount, 
		  uniform bool gUseTexure, 
		  uniform bool gAlphaClip, 
		  uniform bool gFogEnabled, 
		  uniform bool gReflectionEnabled) : SV_Target
{
	// Interpolating normal can unnormalize it, so normalize it.
    pin.NormalW = normalize(pin.NormalW);

	// The toEye vector is used in lighting.
	float3 toEye = gEyePosW - pin.PosW;

	// Cache the distance to the eye from this surface point.
	float distToEye = length(toEye);

	// Normalize.
	toEye /= distToEye;
	
    // Default to multiplicative identity.
    float4 texColor = float4(1, 1, 1, 1);
    if(gUseTexure)
	{
		// Sample texture.
		texColor = gDiffuseMap.Sample( samAnisotropic, pin.Tex );

		if(gAlphaClip)
		{
			// Discard pixel if texture alpha < 0.1.  Note that we do this
			// test as soon as possible so that we can potentially exit the shader 
			// early, thereby skipping the rest of the shader code.
			clip(texColor.a - 0.1f);
		}
	}
	 
	//
	// Lighting.
	//

	float4 litColor = texColor;
	if( gLightCount > 0  )
	{  
		// Start with a sum of zero. 
		float4 ambient = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 diffuse = float4(0.0f, 0.0f, 0.0f, 0.0f);
		float4 spec    = float4(0.0f, 0.0f, 0.0f, 0.0f);

		// Sum the light contribution from each light source.  
		[unroll]
		for(int i = 0; i < gLightCount; ++i)
		{
			float4 A, D, S;
			ComputeDirectionalLight(gMaterial, gDirLights[i], pin.NormalW, toEye, 
				A, D, S);

			ambient += A;
			diffuse += D;
			spec    += S;
		}

		litColor = texColor*(ambient + diffuse) + spec;

		if( gReflectionEnabled )
		{
			float3 incident = -toEye;
			float3 reflectionVector = reflect(incident, pin.NormalW);
			float4 reflectionColor  = gCubeMap.Sample(samAnisotropic, reflectionVector);

			litColor += gMaterial.Reflect*reflectionColor;
		}
	}

	// Common to take alpha from diffuse material and texture.
	litColor.a = gMaterial.Diffuse.a * texColor.a;

	if(SSFlag == true)
	{
		float shininess = 40.0f;
		texColor *= 1.5f ;
		float4 light = litColor;
		light.r = Scatter(light.r);
		light.g = Scatter(light.g);
		light.b = Scatter(light.b);
		float lerpAmount = saturate((litColor.a));  //calculate the amount of blur needed
		float4 diffuseLight = lerp(light,texColor,lerpAmount); //blend the two light maps based on diffuse alpha and blur bias 
  		float4 normal = texColor * 2.0f - 1.0f;
		float curvature = saturate(length(fwidth(normal)) / length(fwidth(float4(pin.NormalW,1.0f))));
	
		float3 N_high = mul(normal.xyz,pin.NormalW);
		float3 N_low = mul(normal.xyz,pin.NormalW);
		float3 rS = N_high;
		float rN = lerp(N_high,N_low, light.r);
		float gN = lerp(N_high,N_low, light.g);
		float bN = lerp(N_high,N_low, light.b);
		float3 NdotL = float3(dot(rN,litColor.r), dot(gN,litColor.b), dot(bN,litColor.b) );
		float3 diffuseL = SkinDiffuse(curvature,NdotL); 
	
		//create lighting vectors - view vector and light vector
  		float3 N = normalize((pin.NormalW * normal.z) + (normal.x * pin.NormalW + normal.y * -pin.NormalW));
  		float3 V = normalize( float4(10.0f, 0.0f, 0.0f, 1.0f) );
  		float3 L = normalize( float4(5.0f, 5.0f, 5.0f, 1.0f) );

		////specular component
  		float3 H = normalize(V + L);
  		shininess = (shininess*diffuseLight.a) * 128.0f;
		float4 specularColor = float4( 0.094f, 0.114f, 0.173f, 1.0f );
		float4 specularLight = pow(max(dot(H,N),0.001f), shininess) * specularColor;

		diffuseLight = lerp(float4(diffuseLight.rgb,litColor.a),diffuseLight,lerpAmount);
		litColor = (diffuseLight*litColor)+specularLight;
	}

	if(SobelFlag == true)
	{
		float3 col[9];
		float tempAlpha = litColor.a;
				texColor = gDiffuseMap.Sample( samAnisotropic, pin.Tex );

		col[0] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[0]);
		col[1] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[1]);
		col[2] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[2]);
		col[3] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[3]);
		col[4] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[4]);
		col[5] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[5]);
		col[6] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[6]);
		col[7] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[7]);
		col[8] = gDiffuseMap.Sample( samAnisotropic, pin.Tex + COLORS[8]);

		float3 rgb2lum = float3(0.30, 0.59, 0.11);
		float lum[9];
		for(int i = 0; i < 9; i++) 
		{
		  lum[i] = dot(col[i].xyz, rgb2lum);
		}
		float x = lum[2]+  lum[8]+2*lum[5]-lum[0]-2*lum[3]-lum[6];
		float y = lum[6]+ 2*lum[7]+  lum[8]-lum[0]-2*lum[1]-lum[2];

		float edge =(x*x + y*y < .1f) ? 1.0:0.0;

		litColor.xyz *= edge.xxx;
		litColor.w = tempAlpha;
	}

	if(ToonFlag == 1)//if its not then just render the standard object with texture applied
	{
		// The direction of the diffuse light
		float3 DiffuseLightDirection = float3(1.0f, 0, 0);
 
		// The color of the diffuse light
		float4 DiffuseColor = litColor;
 
		float DiffuseIntensity = 1.0f;
		float intensity = dot(normalize(DiffuseLightDirection),pin.NormalW);
		if(intensity < 0)
			intensity = 0;
 
		// Calculate what would normally be the final color, including texturing and diffuse lighting
		float4 color = litColor * DiffuseColor * 30.0f;
		color.a = 1.0f;
 
		// Discretize the intensity, based on a few cutoff points
		if (intensity >= 0.9)
			color *= .9f;
		else if (intensity >= 0.75)
			color *= 0.75f;
		else if (intensity >= 0.5)
			color *= 0.5f;
		else
			color *= 0.25f;
 
		litColor.xyz = color.xyz/4;
	}

	

	if(GlitterFlag == true)
	{
		float3 viewFinal = pin.Pos + RandomNumber;
		float specBase = saturate(dot(reflect(-normalize(viewFinal), pin.NormalW), litColor.xyz));
		float noisy = gNormalMap.Sample( samAnisotropic, pin.Tex );
		float3 fp = frac(0.7 * viewFinal + 9 * noisy + 10.0f * viewFinal);
		fp *= (1 - fp);
		float glitter = saturate(1 - 7 * (fp.x + fp.y + fp.z));
		float specular = pow(specBase, 24);
		float glittering = glitter * pow(specBase, 1.5);

		// Get a little more interesting base color
		float4 base = (0.5f * noisy + 0.5f) * litColor;

		litColor = base * litColor * 2.0f + 0.5f * specular + 1000.0f * glittering;
	}

	if(GlassFlag == true)
	{
		float2 refractTexCoord;
		refractTexCoord.x = pin.View.x / pin.View.w / 2.0f + 0.5f;
		refractTexCoord.y = -pin.View.y / pin.View.w / 2.0f + 0.5f;
		float4 normalMap = gNormalMap.Sample( samAnisotropic, pin.Tex );
		float3 normal = (normalMap.xyz * 2.0f) - 1.0f;
		refractTexCoord = refractTexCoord + (normal.xy * .02)  + RandomNumber;
		float4 refractionColor = gNormalMap.Sample(samAnisotropic, refractTexCoord);
		litColor = lerp(refractionColor, litColor, 0.5f);
	}

	if(FogFlag == 1)
	{
		float posZ = pin.PosW.z;
		float fPercent = (gFogRange - posZ) / (gFogRange - gFogStart);
		litColor = float4((fPercent*litColor) + ((1.0f-fPercent)*gFogColor.xyz),litColor.a);
	}

    return litColor;
}

technique11 Light1
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, false, false, false, false) ) );
    }
}

technique11 Light2
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, false, false, false, false) ) );
    }
}

technique11 Light3
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, false, false, false, false) ) );
    }
}

technique11 Light0Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(0, true, false, false, false) ) );
    }
}

technique11 Light1Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(1, true, false, false, false) ) );
    }
}

technique11 Light2Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(2, true, false, false, false) ) );
    }
}

technique11 Light3Tex
{
    pass P0
    {
        SetVertexShader( CompileShader( vs_5_0, VS() ) );
		SetGeometryShader( NULL );
        SetPixelShader( CompileShader( ps_5_0, PS(3, true, false, false, false) ) );
    }
}
