#ifndef WINUTIL_H
#define WINUTIL_H

#include "WinIncludes.h"
#include "Timer.h"
#include "GameMain.h"

class WinUtil
{
public:
	WinUtil();
	~WinUtil();

	bool Initialize(LPCWSTR);
	void Shutdown();
	void Run();

	float AspectRatio() const;
	void OnResize();
private:
	void InitializeWindows();
	void ShutdownWindows();

	LPCWSTR applicationName;
	HINSTANCE hInstance;
	HWND hwnd;

	GameMain* game;
	//int mClientWidth;
	//int mClientHeight;
	Timer gameTimer;
	void CalculateFrameStats();
};

static WinUtil* appHandle = 0;

#endif