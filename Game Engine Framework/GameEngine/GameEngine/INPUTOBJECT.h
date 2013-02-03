#pragma once
#include "WinIncludes.h"

#define INPUT INPUTOBJ::InputInstance()

class INPUTOBJ
{
	INPUTOBJ()
	{
		dx = dy = 0;
		Check = false;
	}
public:
	~INPUTOBJ(){}
	static INPUTOBJ* InputInstance()
	{
		static INPUTOBJ obj;
		return &obj;
	}
	POINT mLastMousePos;
	float dx;
	float dy;
	bool Check;
};