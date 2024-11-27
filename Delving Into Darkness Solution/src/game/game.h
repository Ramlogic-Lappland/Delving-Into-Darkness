#pragma once

#include "raylib.h"

#include "game/player/projectile/projectile.h"

namespace Game
{
	extern bool gameInit;

	void initGame();

	void updateGame();

	void drawGame();

	void unloadGame();

	void resetGame();

	Vector2 NormalizeVector(Vector2 v);

	Projectile::createProjectile* GetInactiveProjectile();

}