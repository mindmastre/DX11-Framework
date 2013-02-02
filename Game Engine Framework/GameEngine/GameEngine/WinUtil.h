#ifndef WINUTIL_H
#define WINUTIL_H

#include "WinIncludes.h"

#include "GameMain.h"

class WinUtil
{
public:
	WinUtil();
	~WinUtil();

	bool Initialize(LPCWSTR);
	void Shutdown();
	void Run();

private:
	void InitializeWindows();
	void ShutdownWindows();

	LPCWSTR applicationName;
	HINSTANCE hInstance;
	HWND hwnd;

	GameMain* game;
};

static WinUtil* appHandle = 0;

#endif