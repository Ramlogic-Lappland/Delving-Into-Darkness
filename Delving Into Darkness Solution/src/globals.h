#pragma once

#include "raylib.h"

namespace Globals
{
	struct CreateScreen {
		const char* name;
		Vector2 size;
	};

	void initGlobals();
	extern CreateScreen Screen;
}