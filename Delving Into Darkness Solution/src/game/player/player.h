#pragma once

#include "raylib.h"

namespace Player
{
	struct CreatePlayer
	{
		Texture2D playerTexture;

		Rectangle playerTextureCordenate;
		Rectangle playerRect;

		Vector2 pivot;
		Vector2 speed;

		float acceleration;
		float maxAcceleration;
		float rotation;

		int lives;
		//int shieldCharge;
		//int shootState;

		//bool shieldState;
		int animationState;
	};
}