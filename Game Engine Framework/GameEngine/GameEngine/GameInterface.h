#ifndef GAMEINTERFACE_H
#define GAMEINTERFACE_H

#include "WinIncludes.h"
#include "GraphicsInterface.h"

class GameInterface
{
public:
	GameInterface();
	~GameInterface();

	bool Initialize(HWND);
	void Shutdown();
	void Update(float);

private:

	//interface globals go here
	GraphicsInterface* graphics;
};

#endif