#include "WinUtil.h"

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

void WinUtil::Run()
{
	MSG msg;
	bool done, result;

	__int64 cntsPerSec = 0;
	QueryPerformanceFrequency((LARGE_INTEGER*)&cntsPerSec);
	float secsPerCnt = 1.0f / (float)cntsPerSec;

	__int64 prevTimeStamp = 0;
	QueryPerformanceCounter((LARGE_INTEGER*)&prevTimeStamp);

	ZeroMemory(&msg, sizeof(MSG));

	done = false;
	while(!done)
	{
		if(PeekMessage(&msg, NULL, 0, 0, PM_REMOVE))
		{
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}

		if(msg.message == WM_QUIT)
		{
			done = true;
		}
		else
		{
			__int64 currTimeStamp = 0;
			QueryPerformanceCounter((LARGE_INTEGER*)&currTimeStamp);
			float dt = (currTimeStamp - prevTimeStamp) * secsPerCnt;

			result = game->Update(dt);
			if(!result)
			{
				done = true;
			}

			prevTimeStamp = currTimeStamp;
		}
	}
}

void WinUtil::InitializeWindows()
{
	WNDCLASS wc;

	appHandle = this;

	hInstance = GetModuleHandle(NULL);

	wc.style = CS_HREDRAW | CS_VREDRAW;
	wc.lpfnWndProc = WndProc;
	wc.cbClsExtra = 0;
	wc.cbWndExtra = 0;
	wc.hInstance = hInstance;
	wc.hIcon = LoadIcon(NULL, IDI_WINLOGO);
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)GetStockObject(BLACK_BRUSH);
	wc.lpszMenuName = 0;
	wc.lpszClassName = applicationName;

	RegisterClass(&wc);

	int posX = (GetSystemMetrics(SM_CXSCREEN) - 800) / 2;
	int posY = (GetSystemMetrics(SM_CYSCREEN) - 600) / 2;

	if(posX < 0)
	{
		posX = 0;
	}
	if(posY < 0)
	{
		posY = 0;
	}

	hwnd = CreateWindow(applicationName, applicationName,
		WS_CAPTION | WS_MINIMIZEBOX | WS_SYSMENU, posX, posY, 800, 600, NULL, NULL, hInstance, NULL);

	ShowWindow(hwnd, SW_SHOW);
	UpdateWindow(hwnd);
	SetForegroundWindow(hwnd);
	SetFocus(hwnd);
}

void WinUtil::ShutdownWindows()
{
	DestroyWindow(hwnd);
	hwnd = 0;

	UnregisterClass(applicationName, hInstance);
	hInstance = 0;

	appHandle = 0;
}

LRESULT CALLBACK WndProc(HWND hwnd, UINT uMessage, WPARAM wParam, LPARAM lParam)
{
	switch(uMessage)
	{
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
	default:
		{
			return DefWindowProc(hwnd, uMessage, wParam, lParam);
		}
	}
}