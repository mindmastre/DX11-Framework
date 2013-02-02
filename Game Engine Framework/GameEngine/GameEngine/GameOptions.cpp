#include "GameOptions.h"

#include "INIParser.h"
#include <string>

GameOptions* options = 0;

GameOptions::GameOptions()
{
	locked = true;
}

GameOptions::~GameOptions()
{
}

bool GameOptions::Initialize()
{
	bool result;

	result = LoadSettingsINI();
	if(!result)
	{
		return false;
	}

	vTemp = vOptions;

	return true;
}

void GameOptions::Shutdown()
{
}

void GameOptions::AllowChanges()
{
	locked = false;
}

void GameOptions::SaveChanges()
{
	locked = true;

	UpdateSettingsINI();
}

int GameOptions::ResolutionX(int val)
{
	if(val != -1 && !locked)
	{
		vTemp.resolutionX = val;
	}

	return vOptions.resolutionX;
}

int GameOptions::ResolutionY(int val)
{
	if(val != -1 && !locked)
	{
		vTemp.resolutionY = val;
	}

	return vOptions.resolutionY;
}

int GameOptions::FullScreen(int val)
{
	if(val != -1 && !locked)
	{
		vTemp.fullScreen = val;
	}

	return vOptions.fullScreen;
}

int GameOptions::VSync(int val)
{
	if(val != -1 && !locked)
	{
		vTemp.vSync = val;
	}

	return vOptions.vSync;
}

bool GameOptions::LoadSettingsINI()
{
	using std::string;

	typedef INI <string, string, string> ini_t;
	ini_t ini("Assets/Settings.INI", true);

	//load video settings
	ini.Select("Video Settings");
	vTemp.fullScreen = ini.Get("FullScreen", -1);
	vTemp.resolutionX = ini.Get("ResolutionX", -1);
	vTemp.resolutionY = ini.Get("ResolutionY", -1);
	vTemp.vSync = ini.Get("VSync", -1);

	vOptions = vTemp;

	return true;
}

void GameOptions::UpdateSettingsINI()
{
	using std::string;

	typedef INI <string, string, string> ini_t;
	ini_t ini("Assets/Settings.INI", true);

	//update video settings
	if(vOptions != vTemp)
	{
		ini.Select("Video Settings");
		ini.Set("FullScreen", vTemp.fullScreen);
		ini.Set("ResolutionX", vTemp.resolutionX);
		ini.Set("ResolutionY", vTemp.resolutionY);
		ini.Set("VSync", vTemp.vSync);

		vOptions = vTemp;
	}

	ini.Save();
}