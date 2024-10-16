#include "globals.h"

#include "raylib.h"

namespace Globals
{
	CreateScreen Screen;

	void initGlobals()
	{
		Screen.size = { 1200, 850 };
		Screen.name = "Delving Into Darkness";
	}

}
