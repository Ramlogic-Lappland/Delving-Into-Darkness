#pragma once

#include "raylib.h"

namespace Game
{
	void initGame();

	void updateGame();

	void drawGame();

	void unloadGame();

	void playerRotationUpdate();

	void checkAnimState();

	Vector2 NormalizeVector(Vector2 v);
}