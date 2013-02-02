#ifndef GAMEOPTIONS_H
#define GAMEOPTIONS_H

class GameOptions
{
private:
	struct VideoOptions
	{
		int resolutionX;	//windowed resolution x
		int resolutionY;	//windowed resolution y
		int fullScreen;	//if fullscreen is enabled
		int vSync;		//if vsync is enabled

		bool operator!=(VideoOptions RHS)
		{
			if(resolutionX != RHS.resolutionX)
			{
				return true;
			}
			else if(resolutionY != RHS.resolutionY)
			{
				return true;
			}
			else if(fullScreen != RHS.fullScreen)
			{
				return true;
			}
			else if(vSync != RHS.vSync)
			{
				return true;
			}

			return false;
		}
	} vOptions, vTemp;
public:

	GameOptions();
	~GameOptions();

	bool Initialize();
	void Shutdown();
	void AllowChanges();
	void SaveChanges();

	//video options getters
	int ResolutionX(int = -1);
	int ResolutionY(int = -1);
	int FullScreen(int = -1);
	int VSync(int = -1);

private:
	bool LoadSettingsINI();
	void UpdateSettingsINI();
	bool locked;
};

extern GameOptions* options;

#endif