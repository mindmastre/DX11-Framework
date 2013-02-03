#ifndef GRAPHICSINTERFACE_H
#define GRAPHICSINTERFACE_H

#include "WinIncludes.h"
#include "D3DApp.h"
#include "D3DCamera.h"
#include "ModelManager.h"

#include "LightShader.h"
#include "D3DLight.h"

class GraphicsInterface
{
public:
	GraphicsInterface();
	~GraphicsInterface();

	bool Initialize(HWND);
	void Shutdown();
	void Update(float);
	void CheckKeyInputs(float deltaTime);
private:
	bool Render();

	HWND hwnd;

	D3DApp* D3D;
	D3DCamera* camera;
	ModelManager* modelManager;

	LightShader* lightShader;
	D3DLight* light;
	D3DModel* testModel;
	D3DTexture* testTexture;
};

#endif