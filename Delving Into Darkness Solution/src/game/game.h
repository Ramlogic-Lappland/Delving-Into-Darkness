#pragma once

#include "raylib.h"

#include "game/player/projectile/projectile.h"

namespace Game
{
	extern Sound slimeDeath;
	extern bool gameInit;

	void initGame();

	void updateGame();

	void drawGame();

	void unloadGame();

	void resetGame();

	void spawnElements();

	Projectile::createProjectile* GetInactiveProjectile();

}