#pragma once

#include "raylib.h"

namespace Player
{
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

	int checkAnimState(CreatePlayer& player);

	void playerRotationUpdate(CreatePlayer& player, Vector2& dirVector, Vector2& pointerPosition, Vector2& playerPosition, float& angle, float& angleToDegrees);

	void playerBounds(CreatePlayer& player);
}