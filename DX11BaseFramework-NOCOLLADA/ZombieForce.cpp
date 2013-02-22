// Demonstrates the simple framework by initializing Direct3D, clearing 
// the screen, and displaying frame stats.
#include "Common\DX11App.h"
#include "Common\d3dx11Effect.h"
#include "Common\MathHelper.h"
#include "Common\GeometryGenerator.h"
#include "Common\LightHelper.h"
#include "Vertex.h"
#include "DXEffect.h"
#include "DX11Camera.h"
#include "Skybox.h"
#include "Primitives.h"
#include <vector>
#include "Billboard.h"
#include "SuperParticleSystem.h"
#include "Model Loader\ColladaMeshManager.h"
#include "ModelManager.h"
#include "TextureManager.h"

class ZombieForce : public DX11App
{
public:
	ZombieForce(HINSTANCE hInstance);
	~ZombieForce();
	
	bool Init();
	void OnResize();
	void UpdateScene(float dt);
	void DrawScene(); 
	void OnMouseDown(WPARAM btnState, int x, int y);
	void OnMouseUp(WPARAM btnState, int x, int y);
	void OnMouseMove(WPARAM btnState, int x, int y);
	void CreateSphere();
	void CreateBox();
	ModelManager* modelManager;
	TextureManager* textureManager;

	D3DModel* testModel;
	Texture* testTexture;
	//SuperParticleSystem**                   g_ppParticleSystem = NULL;
private:
	
	DirectionalLight mDirLights[3];

	float mTheta;
	float mPhi;
	float mRadius;

	POINT mLastMousePos;
	DX11Camera mCam;
	Skybox* mSky;
	DXBox *myFirstBox;
	DXSphere *myFirstSphere;
	DXPlane *myFirstPlane;
	DXPyramid* pyramid;
	DXCylinder *myFirstCylinder;
	DXGeoSphere *myFirstGeoSphere;
	std::vector<DXSphere*>spheres;
	std::vector<DXBox*>boxes;

	//ColladaModelLoader *modelLoader;
	Billboard* billboard;

};

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE prevInstance,
				   PSTR cmdLine, int showCmd)
{
	// Enable run-time memory check for debug builds.
#if defined(DEBUG) | defined(_DEBUG)
	_CrtSetDbgFlag( _CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF );
#endif

	ZombieForce theApp(hInstance);
	
	if( !theApp.Init() )
		return 0;
	
	return theApp.Run();
}

ZombieForce::ZombieForce(HINSTANCE hInstance)
: DX11App(hInstance), mSky(0), mTheta(1.3f*MathHelper::Pi), mPhi(0.4f*MathHelper::Pi), mRadius(2.5f)
{
	modelManager = 0;
	testModel = 0;
	testTexture = 0;

	mMainWndCaption = L"Z-Force Box Demo";
	
	mLastMousePos.x = 0;
	mLastMousePos.y = 0;

	mCam.SetPosition(0.0f, 2.0f, -15.0f);

	mDirLights[0].Ambient  = XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
	mDirLights[0].Diffuse  = XMFLOAT4(0.8f, 0.8f, 0.8f, 1.0f);
	mDirLights[0].Specular = XMFLOAT4(0.6f, 0.6f, 0.6f, 16.0f);
	mDirLights[0].Direction = XMFLOAT3(0.707f, -0.707f, 0.0f);
 
	mDirLights[1].Ambient  = XMFLOAT4(0.2f, 0.2f, 0.2f, 1.0f);
	mDirLights[1].Diffuse  = XMFLOAT4(1.4f, 1.4f, 1.4f, 1.0f);
	mDirLights[1].Specular = XMFLOAT4(0.3f, 0.3f, 0.3f, 16.0f);
	mDirLights[1].Direction = XMFLOAT3(-0.707f, 0.0f, 0.707f);

}

ZombieForce::~ZombieForce()
{
	SafeDelete(mSky);
	if(testModel)
	{
		testModel->Shutdown();
		delete testModel;
		testModel = 0;
	}
	Effects::DestroyAll();
	InputLayouts::DestroyAll();
	//delete stuff man
}

bool ZombieForce::Init()
{
	if(!DX11App::Init())
	{
		return false;
	}
	Effects::InitAll(md3dDevice);
	InputLayouts::InitAll(md3dDevice);

	
	modelManager = new ModelManager;
	if(!modelManager)
	{
		return false;
	}

	textureManager = new TextureManager;
	if(!textureManager)
	{
		return false;
	}

		//load temp model
	testModel = new D3DModel();
	if(!testModel)
	{
		return false;
	}

	testModel->LoadModel(md3dDevice, L"../Assets/Models/soldierTest.md5mesh");

	testTexture = new Texture;
	if(!testModel)
	{
		return false;
	}

	testTexture->Initialize(md3dDevice, L"../Assets/Textures/american_body.jpg");

	testModel->LoadAnimation(L"../Assets/Models/soldierTest.md5anim");
	testModel->SetAnimation(0);

	testModel->LoadTexture(testTexture);
	HR(D3DX11CreateShaderResourceViewFromFile(md3dDevice, 
		L"../Assets/Textures/stonenormals.jpg", 0, 0, &testModel->normalTexture, 0 ));

	mSky = new Skybox(md3dDevice, L"../Assets/Textures/clouds.dds", 5000.0f);

	myFirstBox = new DXBox(md3dDevice, L"../Assets/Textures/brick.dds");
	myFirstBox->SetPosition(Vector3(0,-8,0));
	pyramid = new DXPyramid(md3dDevice, L"../Assets/Textures/brick.dds");
	pyramid->SetPosition(Vector3(0,10,0));
	pyramid->SetScale(Vector3(5,5,5));
	myFirstSphere = new DXSphere(md3dDevice, L"../Assets/Textures/stone2.jpg");
	myFirstSphere->SetPosition(Vector3(0,0,200));
	myFirstSphere->SetScale(Vector3(20,20,20));
	myFirstPlane = new DXPlane(md3dDevice, L"../Assets/Textures/stone.jpg");
	myFirstPlane->SetPosition(Vector3(0,0,0));
	myFirstPlane->SetScale(Vector3(100,1,100));

	myFirstCylinder = new DXCylinder(md3dDevice,L"../Assets/Textures/stone.jpg");
	myFirstGeoSphere = new DXGeoSphere(md3dDevice, L"../Assets/Textures/stone.jpg", 20);
	myFirstGeoSphere->SetPosition(Vector3(0,0,-200));
	myFirstGeoSphere->SetScale(Vector3(30,30,30));
	myFirstCylinder->SetPosition(Vector3(0,-100,-100));
	myFirstCylinder->SetScale(Vector3(30,30,30));

	//CMESHMANAGER->SetDevice(md3dDevice);
	//CMODELLOADER->ReadDaeFile("../Assets/Models/starfighter1.dae", md3dDevice);
	//CMODELLOADER->ReadDaeFile("../Assets/Models/fancygravestone.dae", md3dDevice);
	//CMODELLOADER->ReadDaeFile("../Assets/Models/skinnedexample.dae", md3dDevice);
	//ColladaMesh* mesh = CMESHMANAGER->GetMesh(0);
	//mesh->SetScale(Vector3(.3,.3,-.3));
	//mesh->SetPosition(Vector3(50,50,-50));
	//CMODELLOADER->ReadDaeFile("../Assets/Models/starfighter2.dae", md3dDevice);
			//ColladaMesh* mesh2 = CMESHMANAGER->GetMesh(1);
		//mesh2->SetPosition(Vector3(30,0,50));
		//mesh2->SetScale(Vector3(7,7,-7));
		//mesh2->SetScale(Vector3(.3,.3,-.3));
		//CMODELLOADER->ReadDaeFile("../Assets/Models/aion2.dae", md3dDevice);
	//CMODELLOADER->ReadDaeFile("../Assets/Models/largegravestone.dae", md3dDevice);
	//mesh2 = CMESHMANAGER->GetMesh(2);
	//mesh2->SetPosition(Vector3(30,0,250));
	return true;
}

void ZombieForce::OnResize()
{
	DX11App::OnResize();

	mCam.SetLens(0.25f*MathHelper::Pi, AspectRatio(), .20f, 1000.0f);
}

void ZombieForce::UpdateScene(float dt)
{
	//ColladaMesh* mesh = CMESHMANAGER->GetMesh(0);

	float MoveMultiplier = 1;
	if( GetAsyncKeyState(VK_LSHIFT) & 0x8000 )
		MoveMultiplier = 10;

	// Control the camera.
	if( GetAsyncKeyState('W') & 0x8000 )
		mCam.Walk(10.0f*dt*MoveMultiplier);

	if( GetAsyncKeyState('S') & 0x8000 )
		mCam.Walk(-10.0f*dt*MoveMultiplier);

	if( GetAsyncKeyState('A') & 0x8000 )
		mCam.Strafe(-10.0f*dt*MoveMultiplier);

	if( GetAsyncKeyState('D') & 0x8000 )
		mCam.Strafe(10.0f*dt*MoveMultiplier);

	if( GetAsyncKeyState(VK_NUMPAD1) & 0x8000 )
	{
		testModel->ToggleScattering();
	}

	if( GetAsyncKeyState(VK_NUMPAD2) & 0x8000 )
	{
		testModel->ToggleSobel();
	}

	if( GetAsyncKeyState(VK_NUMPAD3) & 0x8000 )
	{
		testModel->ToggleFog();
	}

	if( GetAsyncKeyState(VK_NUMPAD4) & 0x8000 )
	{
		testModel->ToggleCelShading();
	}

	if( GetAsyncKeyState(VK_NUMPAD5) & 0x8000 )
	{
		testModel->ToggleGlitter();
	}

	if( GetAsyncKeyState(VK_NUMPAD6) & 0x8000 )
	{
		testModel->ToggleGlass();
	}

	if( GetAsyncKeyState(VK_LCONTROL) & 0x8000 )
	{
		CreateSphere();
	}

	if( GetAsyncKeyState(VK_SPACE) & 0x8000 )
	{
		CreateBox();
	}

	testModel->Update(md3dImmediateContext, dt);

    //CMESHMANAGER->Update(dt);
	myFirstSphere->SetRotation(myFirstSphere->GetRotation() + (Vector3(0,2,0)*dt));
	//myFirstPlane->SetRotation(myFirstSphere->GetRotation() + (Vector3(1,0,0)*dt));
	//myFirstGeoSphere->SetRotation(myFirstSphere->GetRotation() + (Vector3(0,2,0)*dt));
	//myFirstCylinder->SetRotation(myFirstSphere->GetRotation() + (Vector3(0,0,1)*dt));
}

void ZombieForce::DrawScene()
{
	md3dImmediateContext->ClearRenderTargetView(mRenderTargetView, reinterpret_cast<const float*>(&Colors::Blue));
	md3dImmediateContext->ClearDepthStencilView(mDepthStencilView, D3D11_CLEAR_DEPTH|D3D11_CLEAR_STENCIL, 1.0f, 0);

	md3dImmediateContext->IASetInputLayout(InputLayouts::Basic32);
    md3dImmediateContext->IASetPrimitiveTopology(D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST);
 
	UINT stride = sizeof(Vertex::Basic32);
    UINT offset = 0;
	
	mCam.UpdateViewMatrix();

	XMMATRIX view  = mCam.View();
	XMMATRIX proj  = mCam.Proj();
	XMMATRIX viewProj = mCam.ViewProj();

	// Set per frame constants.
	Effects::BillboardFX->SetDirLights(mDirLights);
	Effects::BillboardFX->SetEyePosW(mCam.GetPosition());
	Effects::BillboardFX->SetCubeMap(mSky->CubeMapSRV());

	//ID3DX11EffectTechnique* activeTech = Effects::BasicFX->Light2TexTech;
	ID3DX11EffectTechnique* activeTech = Effects::BillboardFX->Light2TexTech;

    D3DX11_TECHNIQUE_DESC techDesc;
	activeTech->GetDesc( &techDesc );
    for(UINT p = 0; p < techDesc.Passes; ++p)
    {
		//pyramid->DrawPyramid(md3dImmediateContext,activeTech, mCam);
		//myFirstSphere->DrawSphere(md3dImmediateContext,activeTech, mCam);
		//myFirstPlane->DrawPlane(md3dImmediateContext,activeTech, mCam);
		//myFirstGeoSphere->DrawGeoSphere(md3dImmediateContext,activeTech, mCam);
		//myFirstCylinder->DrawCylinder(md3dImmediateContext,activeTech, mCam);
		for(unsigned int i = 0; i < spheres.size(); ++i)
		{
			spheres[i]->DrawSphere(md3dImmediateContext,activeTech, mCam);
		}
		for(unsigned int i = 0; i < boxes.size(); ++i)
		{
			boxes[i]->DrawBox(md3dImmediateContext,activeTech, mCam);
		}
		//CMESHMANAGER->Render(md3dImmediateContext, activeTech, mCam);
		testModel->RenderModel(md3dImmediateContext, activeTech, mCam);
    }

	mSky->Draw(md3dImmediateContext, mCam);

	// restore default states, as the SkyFX changes them in the effect file.
	md3dImmediateContext->RSSetState(0);
	md3dImmediateContext->OMSetDepthStencilState(0, 0);

	HR(mSwapChain->Present(0, 0));
}
void ZombieForce::OnMouseDown(WPARAM btnState, int x, int y)
{
	mLastMousePos.x = x;
	mLastMousePos.y = y;

	SetCapture(mhMainWnd);
}

void ZombieForce::OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

void ZombieForce::OnMouseMove(WPARAM btnState, int x, int y)
{
	if( (btnState & MK_LBUTTON) != 0 )
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - mLastMousePos.y));

		mCam.Pitch(dy);
		mCam.RotateY(dx);
	}

	mLastMousePos.x = x;
	mLastMousePos.y = y;
}

void ZombieForce::CreateSphere()
{
	DXSphere* newSphere = new DXSphere(md3dDevice, L"../Assets/Textures/stone2.jpg");
	newSphere->SetPosition(Vector3(mCam.GetPosition().x,mCam.GetPosition().y,mCam.GetPosition().z));
	newSphere->SetScale(Vector3(2,2,2));
	spheres.push_back(newSphere);
}

void ZombieForce::CreateBox()
{
	DXBox *newBox = new DXBox(md3dDevice, L"../Assets/Textures/brick.dds");
	newBox->SetPosition(Vector3(mCam.GetPosition().x,mCam.GetPosition().y,mCam.GetPosition().z));
	newBox->SetScale(Vector3(2,2,2));
	boxes.push_back(newBox);
}