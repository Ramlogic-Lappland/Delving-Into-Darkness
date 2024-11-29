#include "globals.h"

#include "raylib.h"

namespace Globals
{
	float gameVersion;

	CreateScreen Screen;

	void initGlobals()
	{
		gameVersion = 2.0f;

		Screen.originalIntendedSize = { 1200, 850 };
		Screen.size = { 1200, 850 };
		Screen.currentSize = { 1024, 768 };
		Screen.screenOffset = { Screen.currentSize.x /  Screen.originalIntendedSize.x, Screen.currentSize.y / Screen.originalIntendedSize.y };
		Screen.name = "Delving Into Darkness";
	}

	void updateScreenOffset()
	{
		Screen.screenOffset = { Screen.currentSize.x / Screen.originalIntendedSize.x, Screen.currentSize.y / Screen.originalIntendedSize.y };
	}

}
