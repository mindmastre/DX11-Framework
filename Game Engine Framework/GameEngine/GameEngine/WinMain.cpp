#include "WinUtil.h"

int WINAPI WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, PSTR pSCmdLine, int iCmdShow)
{
	WinUtil* system;
	bool result;

	system = new WinUtil;
	if(!system)
	{
		return 0;
	}

	result = system->Initialize(L"Game Engine");
	if(result)
	{
		system->Run();
	}

	system->Shutdown();
	delete system;
	system = 0;

	return 0;
}