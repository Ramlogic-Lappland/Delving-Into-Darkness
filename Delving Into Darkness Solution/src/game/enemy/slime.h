#pragma once
#include "raylib.h"

namespace Slime
{
	struct CreateSlime
	{
		Vector2 position;
		Vector2 speed;
		float radius;
		bool state;
	};
}