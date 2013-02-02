#include "GameInterface.h"
#include "GameOptions.h"

GameInterface::GameInterface()
{
	//initialize interface globals here
	graphics = 0;
}

GameInterface::~GameInterface()
{
}

bool GameInterface::Initialize(HWND hwnd)
{
	bool result;

	options = new GameOptions;
	if(!options)
	{
		return false;
	}

	result = options->Initialize();
	if(!result)
	{
		return false;
	}

	graphics = new GraphicsInterface;
	if(!graphics)
	{
		return false;
	}

	result = graphics->Initialize(hwnd);

	return true;
}

void GameInterface::Shutdown()
{
}

void GameInterface::Update(float dt)
{
	graphics->Update(dt);
}