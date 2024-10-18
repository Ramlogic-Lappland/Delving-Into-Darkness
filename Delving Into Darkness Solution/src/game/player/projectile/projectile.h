#pragma once

#include "raylib.h"

namespace projectile
{
	struct createProjectile
	{
		Vector2 position;
		Vector2 size;
		Vector2 speed;

		float radius;
		float rotation;

		int lifeSpawn;

		bool state;
	};
}