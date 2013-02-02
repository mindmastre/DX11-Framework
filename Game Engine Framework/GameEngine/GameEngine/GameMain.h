#ifndef GAMEMAIN_H
#define GAMEMAIN_H

#include "WinIncludes.h"
#include "GameInterface.h"

class GameMain
{
public:
	GameMain()
	{
		engine = 0;
	}
	~GameMain()
	{
	}

	bool Initialize(HWND);
	void Shutdown();
	bool Update(float);

private:

	GameInterface* engine;
};

#endif