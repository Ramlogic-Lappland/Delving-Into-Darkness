#pragma once

#include "raylib.h"

namespace Slime
{
	enum SlimeSize
	{
		BIG,
		MEDIUM,
		SMALL
	};

	struct CreateSlime
	{
		Vector2 position;
		Vector2 speed;
		bool state;
		float rad;
		SlimeSize type;
	};

	void getSpawnOutOfBounds(CreateSlime& slime);
	void getRadomSpawnDirection(CreateSlime& slime);
	void spawnSlime(CreateSlime slime[], int arraySize, SlimeSize type, Vector2 spawnPosition, Vector2 spawnSpeed);
	void slimeBounds(CreateSlime& slime);
}