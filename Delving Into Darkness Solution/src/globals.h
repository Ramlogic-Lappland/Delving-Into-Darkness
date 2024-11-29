#pragma once

#include "raylib.h"

namespace Globals
{
	extern float gameVersion;

	struct CreateScreen 
	{
		const char* name;
		Vector2 size;
		Vector2 currentSize;
		Vector2 screenOffset;
		Vector2 originalIntendedSize;
	};

	void initGlobals();
	extern CreateScreen Screen;
}