#pragma once

#include <vector>

#include "raylib.h"


namespace Slime
{
	//extern std::vector<int> bigSlimeSlots;
	//extern std::vector<int> mediumSlimeSlots;
	//extern std::vector<int> smallSlimeSlots;
	//extern int bigSlimeIndex;
	//extern int mediumSlimeIndex;
	//extern int smallSlimeIndex;

	const int maxBigSlimes = 8;
	const int maxMediumSlimes = 16;
	const int maxSmallSlimes = 32;

	const int bigSlimeSpeed = 300;
	const int mediumSlimeSpeed = 600;
	const int smallSlimeSpeed = 900;

	enum SlimeSize
	{
		BIG,
		MEDIUM,
		SMALL
	};

	struct CreateSlime
	{
		Rectangle frameRec;

		Vector2 position;
		Vector2 speed;

		bool state;

		float rad;
		float frameTime;

		int currentFrame;

		SlimeSize type;
	};

	void getSpawnOutOfBounds(CreateSlime& slime);

	void getRadomSpawnDirection(CreateSlime& slime);

	void spawnSlime(CreateSlime slime[], int arraySize, SlimeSize type, Vector2 spawnPosition, Vector2 spawnSpeed);

	void updateSlimeMovement(CreateSlime slimes[], int array);

	void slimeBounds(CreateSlime& slime);

	void spawnBigSlimesOverTime(CreateSlime bigSlime[]);

	void updateSlimeAnimation(CreateSlime& slime, float deltaTime);

	void drawSlime(CreateSlime& slime, Texture2D& slimeTexture);
}