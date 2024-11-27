#include "player.h"

#include <cmath>

#include "globals.h"

namespace Player
{
	void initPlayer(CreatePlayer& player)
	{
		player.playerTexture = LoadTexture("res/character/test.png");
		player.playerRect = { Globals::Screen.size.x / 2, Globals::Screen.size.y / 2, 45, 45 };
		player.playerTextureCoordinate = { 0, 0, 45, 45 };
		player.pivot = { static_cast<float>(player.playerTexture.width / 2), static_cast<float>(player.playerTexture.height / 2) };
		player.rotation = 0;
		player.animationState = 1;
		player.maxAcceleration = 700;
		player.acceleration = 400.0f;
		player.rad = 18.0f;
		player.hp = 100;
		player.score = 0;
	}

	void resetPlayer(CreatePlayer& player)
	{
		player.playerRect.x = Globals::Screen.size.x / 2;
		player.playerRect.y = Globals::Screen.size.y / 2;
		player.pivot = { static_cast<float>(player.playerTexture.width / 2), static_cast<float>(player.playerTexture.height / 2) };
		player.rotation = 0;
		player.acceleration = 400.0f;
		player.speed = { 0, 0 };
		player.animationState = 1;
		player.hp = 100;
		player.score = 0;
	}

	void playerRotationUpdate(CreatePlayer& player, Vector2& dirVector, Vector2& pointerPosition, Vector2& playerPosition,	float& angle, float& angleToDegrees)
	{
		dirVector = { pointerPosition.x - playerPosition.x, pointerPosition.y - playerPosition.y };

		angle = atan2f(dirVector.y, dirVector.x);

		angleToDegrees = (angle * (180.0f / PI)) - 90;

		if (angleToDegrees < 0) 
		{
			angleToDegrees += 360.0f;
		}

		player.rotation = angleToDegrees;
	}

	int checkAnimState( CreatePlayer& player)
	{

		if (player.rotation < 23 || player.rotation > 338)
		{
			return 1; //bottom
		}
		else if (player.rotation < 338 && player.rotation > 293) 
		{
			return 2; //bottom right
		}
		else if (player.rotation < 293 && player.rotation > 248) 
		{
			return 3; //right
		}
		else if (player.rotation < 248 && player.rotation > 203)
		{
			return 4; //top right
		}
		else if (player.rotation < 203 && player.rotation > 158) 
		{
			return 5; // top
		}
		else if (player.rotation < 158 && player.rotation > 113)
		{
			return 6; //top left
		}
		else if (player.rotation < 113 && player.rotation > 68) 
		{
			return 7; //left
		}
		else if (player.rotation < 68 && player.rotation > 23) 
		{
			return 8; //bottom left
		}
		else
		return 0;
	}

	void playerBounds(CreatePlayer& player)
	{
		if (player.playerRect.x > Globals::Screen.size.x + (player.playerRect.width * 1.5))
		{
			player.playerRect.x = static_cast<float>(0 - (player.playerRect.width));
		}
		if (player.playerRect.x < 0 - (player.playerRect.width * 1.5))
		{
			player.playerRect.x = static_cast<float>(Globals::Screen.size.x + player.playerRect.width);
		}
		if (player.playerRect.y > Globals::Screen.size.y + (player.playerRect.height * 1.5))
		{
			player.playerRect.y = static_cast<float>(0 - (player.playerRect.height));
		}
		if (player.playerRect.y < 0 - (player.playerRect.height * 1.5))
		{
			player.playerRect.y = static_cast<float>(Globals::Screen.size.y + player.playerRect.height);
		}
	}

}