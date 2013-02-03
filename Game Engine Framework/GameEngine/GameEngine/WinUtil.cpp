#include "WinUtil.h"
#include "INPUTOBJECT.h"
#include <WinUser.h>
#include <sstream>
LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam);

WinUtil::WinUtil()
{
	game = 0;
}

WinUtil::~WinUtil()
{
}

bool WinUtil::Initialize(LPCWSTR windowName)
{
	bool result;

	applicationName = windowName;

	//initialize main window
	InitializeWindows();

	//initialize game
	game = new GameMain;
	if(!game)
	{
		return false;
	}

	result = game->Initialize(hwnd);
	if(!result)
	{
		return false;
	}

	return true;
}

void WinUtil::Shutdown()
{
	//shutdown game
	if(game)
	{
		game->Shutdown();
		delete game;
		game = 0;
	}

	//shutdown window
	ShutdownWindows();
}

float WinUtil::AspectRatio()const
{
	//For window resize, need to set up access to ClientWidth/Height values
//	return static_cast<float>(mClientWidth) / mClientHeight;
	return 0;
}

void WinUtil::Run()
{
	//	ZeroMemory(&msg, sizeof(MSG));
	MSG msg = {0};  //Same as above
	bool result;
	gameTimer.Reset();

	while(msg.message != WM_QUIT)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else
		{
			gameTimer.Tick();
			CalculateFrameStats();
			result = game->Update(gameTimer.DeltaTime());
			
		}
	}
}

void WinUtil::InitializeWindows()
{
	WNDCLASS wc;

	/*appHandle = this;

	hInstance = GetModuleHandle(NULL);*/

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_APPLICATION);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(WHITE_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = applicationName;

	if( !RegisterClass(&wc) )
	{
		MessageBox(0, L"RegisterClass Failed.", 0, 0);
		return;
	}

	// Compute window rectangle dimensions based on requested client area dimensions.
	RECT R = { 0, 0, 800, 600 };
    AdjustWindowRect(&R, WS_OVERLAPPEDWINDOW, false);
	int width  = R.right - R.left;
	int height = R.bottom - R.top;

	hwnd = CreateWindow(applicationName,  applicationName,
		WS_OVERLAPPEDWINDOW, CW_USEDEFAULT, CW_USEDEFAULT, width, height, NULL, NULL, hInstance, NULL);

	if( !hwnd )
	{
		MessageBox(0, L"CreateWindow Failed.", 0, 0);
		return;
	}

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	//SetForegroundWindow(hwnd);
	//SetFocus(hwnd);
}

void WinUtil::ShutdownWindows()
{
	DestroyWindow(hwnd);
	hwnd = 0;

	UnregisterClass(applicationName, hInstance);
	hInstance = 0;

	appHandle = 0;
}

void OnMouseDown(HWND hwnd, WPARAM btnState, int x, int y)
{
	INPUT->mLastMousePos.x = x;
	INPUT->mLastMousePos.y = y;

	SetCapture(hwnd);
}

void OnMouseMove(WPARAM btnState, int x, int y)
{
	if( (btnState & MK_LBUTTON) != 0 )
	{
		// Make each pixel correspond to a quarter of a degree.
		float dx = XMConvertToRadians(0.25f*static_cast<float>(x - INPUT->mLastMousePos.x));
		float dy = XMConvertToRadians(0.25f*static_cast<float>(y - INPUT->mLastMousePos.y));

		INPUT->dy = dy;
		INPUT->dx = dx;
		INPUT->Check = true;
	}
	else
	{
		INPUT->Check = false;
	}

	INPUT->mLastMousePos.x = x;
	INPUT->mLastMousePos.y = y;
}

void OnMouseUp(WPARAM btnState, int x, int y)
{
	ReleaseCapture();
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
	// Catch this message so to prevent the window from becoming too small.
	case WM_GETMINMAXINFO:
		{
			((MINMAXINFO*)lParam)->ptMinTrackSize.x = 200;
			((MINMAXINFO*)lParam)->ptMinTrackSize.y = 200;
			return 0;
		}
	// The WM_MENUCHAR message is sent when a menu is active and the user presses 
	// a key that does not correspond to any mnemonic or accelerator key. 
	case WM_MENUCHAR:
		{
			// Don't beep when we alt-enter.
			return MAKELRESULT(0, MNC_CLOSE);
		}
	case WM_DESTROY:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_CLOSE:
		{
			PostQuitMessage(0);
			return 0;
		}
	case WM_LBUTTONDOWN:
	case WM_MBUTTONDOWN:
	case WM_RBUTTONDOWN:
		{
			OnMouseDown(hwnd, wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	case WM_MOUSEMOVE:
		{
			OnMouseMove(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	case WM_LBUTTONUP:
	case WM_MBUTTONUP:
	case WM_RBUTTONUP:
		{
			OnMouseUp(wParam, GET_X_LPARAM(lParam), GET_Y_LPARAM(lParam));
			return 0;
		}
	default:
		{
			return DefWindowProc(hwnd, uMessage, wParam, lParam);
		}
	}
}

void WinUtil::CalculateFrameStats()
{
	// Code computes the average frames per second, and also the 
	// average time it takes to render one frame.  These stats 
	// are appended to the window caption bar.

	static int frameCnt = 0;
	static float timeElapsed = 0.0f;

	frameCnt++;

	// Compute averages over one second period.
	if( (gameTimer.TotalTime() - timeElapsed) >= 1.0f )
	{
		float fps = (float)frameCnt; // fps = frameCnt / 1
		float mspf = 1000.0f / fps;

		std::wostringstream outs;   
		outs.precision(6);
		outs << applicationName << L"    "
			 << L"FPS: " << fps << L"    " 
			 << L"Frame Time: " << mspf << L" (ms)";
		SetWindowText(hwnd, outs.str().c_str());
		
		// Reset for next average.
		frameCnt = 0;
		timeElapsed += 1.0f;
	}
}