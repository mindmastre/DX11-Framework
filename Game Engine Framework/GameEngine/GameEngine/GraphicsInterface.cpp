#include "GraphicsInterface.h"

#include "GameOptions.h"
#include "TextureManager.h"

GraphicsInterface::GraphicsInterface()
{
	D3D = 0;
	camera = 0;
	modelManager = 0;

	lightShader = 0;
	light = 0;

	testModel = 0;
	testTexture = 0;
}

GraphicsInterface::~GraphicsInterface()
{
}

bool GraphicsInterface::Initialize(HWND wndHandle)
{
	bool result;

	hwnd = wndHandle;
	int width, height;

	if(options->FullScreen())
	{
		width = GetSystemMetrics(SM_CXSCREEN);
		height = GetSystemMetrics(SM_CYSCREEN);

		SetWindowLongPtr(hwnd, GWL_STYLE, WS_POPUP);
		SetWindowPos(hwnd, HWND_TOP, 0, 0, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
	}
	else
	{
		width = options->ResolutionX();
		height = options->ResolutionY();
		int posX = (GetSystemMetrics(SM_CXSCREEN) - width) / 2;
		int posY = (GetSystemMetrics(SM_CYSCREEN) - height) / 2;

		SetWindowLongPtr(hwnd, GWL_STYLE, WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU);
		SetWindowPos(hwnd, HWND_TOP, posX, posY, width, height, SWP_NOZORDER | SWP_SHOWWINDOW);
	}

	textureManager = new TextureManager;
	if(!textureManager)
	{
		return false;
	}

	D3D = new D3DApp;
	if(!D3D)
	{
		return false;
	}

	result = D3D->Initialize(hwnd, 1.0f, 5000.0f);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize DirectX", L"Error", MB_OK);
		return false;
	}

	camera = new D3DCamera;
	if(!camera)
	{
		return false;
	}

	camera->SetPosition(0.0f, 50.0f, -100.0f);

	modelManager = new ModelManager;
	if(!modelManager)
	{
		return false;
	}

	//load temp model
	testModel = new D3DModel();
	if(!testModel)
	{
		return false;
	}

	result = testModel->LoadModel(D3D->GetDevice(), L"../GameEngine/Assets/3DModels/soldierTest.md5mesh");
	if(!result)
	{
		return false;
	}

	testTexture = new D3DTexture;
	if(!testModel)
	{
		return false;
	}

	result = testTexture->Initialize(D3D->GetDevice(), L"../GameEngine/Assets/Textures/american_body.jpg");
	if(!result)
	{
		return false;
	}

	testModel->LoadTexture(testTexture);

	lightShader = new LightShader;
	if(!lightShader)
	{
		return false;
	}

	result = lightShader->Initialize(D3D->GetDevice(), hwnd);
	if(!result)
	{
		MessageBox(hwnd, L"Could not initialize the light shader", L"Error", MB_OK);
		return false;
	}

	light = new D3DLight;
	if(!light)
	{
		return false;
	}

	light->SetDiffuseColor(1.0f, 1.0f, 1.0f, 1.0f);
	light->SetDirection(0.0f, 0.0f, 1.0f);

	return true;
}

void GraphicsInterface::Shutdown()
{
	if(testTexture)
	{
		testTexture->Shutdown();
		delete testTexture;
		testTexture = 0;
	}

	if(testModel)
	{
		testModel->Shutdown();
		delete testModel;
		testModel = 0;
	}

	if(light)
	{
		delete light;
		light = 0;
	}

	if(lightShader)
	{
		lightShader->Shutdown();
		delete lightShader;
		lightShader = 0;
	}

	if(modelManager)
	{
		modelManager->Shutdown();
		delete modelManager;
		modelManager = 0;
	}

	if(camera)
	{
		delete camera;
		camera = 0;
	}

	if(textureManager)
	{
		textureManager->Shutdown();
		delete textureManager;
		textureManager = 0;
	}

	if(D3D)
	{
		D3D->Shutdown();
		delete D3D;
		D3D = 0;
	}
}

void GraphicsInterface::Update(float dt)
{
	bool result;
	//update models here

	result = Render();
	if(!result)
	{
		//something broke!
	}
}

bool GraphicsInterface::Render()
{
	D3DXMATRIX viewMatrix, projectionMatrix, worldMatrix;
	bool result;

	D3D->BeginScene(0.0f, 0.24f, 0.39f, 1.0f);

	camera->Render();

	camera->GetViewMatrix(viewMatrix);
	D3D->GetWorldMatrix(worldMatrix);
	D3D->GetProjectionMatrix(projectionMatrix);

	//loop through and render stuff here through the lightShader.
	//the result bool is for error handling with the lightShader->Render(...) function
	result = lightShader->Render(D3D->GetDeviceContext(), testModel, worldMatrix, viewMatrix, projectionMatrix, testModel->GetTexture(), light->GetDirection(), light->GetDiffuseColor());
	if(!result)
	{
		return false;
	}

	D3D->EndScene();

	return true;
}