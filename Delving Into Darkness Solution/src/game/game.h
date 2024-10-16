#pragma once

#include "raylib.h"

namespace Game
{
	struct CreatePlayer
	{
		Texture2D playerTexture;

		Rectangle playerTextureCordenate;
		Rectangle playerRect;

		Vector2 pivot;
		Vector2 speed;

		float acceleration;
		float rotation;

		int lives;
		//int shieldCharge;
		//int shootState;
		
		//bool shieldState;
		int animationState;
	};

	void initGame();

	void updateGame();

	void drawGame();

	void unloadGame();

	void playerRotationUpdate();
}