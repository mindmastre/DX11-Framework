#include "GameMain.h"

#include "EntityManager.h"

bool GameMain::Initialize(HWND hwnd)
{
	bool result;

	entityManager = new EntityManager();

	engine = new GameInterface;
	if(!engine)
	{
		return false;
	}

	result = engine->Initialize(hwnd);
	if(!result)
	{
		return false;
	}

///////////////////////////////////////
//  GAME CODE INITIALIZATIONS GO HERE
///////////////////////////////////////

	return true;
}

void GameMain::Shutdown()
{
///////////////////////////////////////
//     GAME CODE SHUTDOWNS GO HERE
///////////////////////////////////////

	if(engine)
	{
		engine->Shutdown();
		delete engine;
		engine = 0;
	}
}

bool GameMain::Update(float dt)
{
///////////////////////////////////////
//      GAME CODE UPDATES GO HERE
///////////////////////////////////////

	engine->Update(dt);

	return true;
}