#pragma once

#include "raylib.h"
#include "game/player/projectile/projectile.h"

namespace Game
{
	void initGame();

	void updateGame();

	void drawGame();

	void unloadGame();

	void playerRotationUpdate();

	void checkAnimState();

	Vector2 NormalizeVector(Vector2 v);

	Projectile::createProjectile* GetInactiveProjectile();
}