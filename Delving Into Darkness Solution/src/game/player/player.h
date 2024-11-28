#pragma once

#include "raylib.h"
#include "game/enemy/slime.h"

namespace Player
{
	extern float angle;
	extern float angleToDegrees;

	extern Vector2 dirVector;

	struct CreatePlayer
	{
		Texture2D playerTexture;

		Rectangle playerTextureCoordinate;
		Rectangle playerRect;

		Vector2 position;
		Vector2 pivot;
		Vector2 speed;

		float acceleration;
		float maxAcceleration;
		float rotation;
		float rad; 

		int hp;
		int score;
		int animationState;
		//int shieldCharge;
        //bool shieldState;
	};

	void initPlayer(CreatePlayer& player);

	void resetPlayer(CreatePlayer& player);

	void updatePlayer(CreatePlayer& player, Vector2 pointerPosition);

	int checkAnimState(CreatePlayer& player);

	void playerBounds(CreatePlayer& player);

	void playerCheckColl(CreatePlayer& player, Slime::CreateSlime bigSlime[], Slime::CreateSlime mediumSlime[], Slime::CreateSlime smallSlime[]);
}