#include "player.h"

#include <cmath>

#include "globals.h"
#include "game/game.h"
#include "collisionManager/collisionManager.h"
#include "game/enemy/slime.h"


namespace Player
{
	void playerRotationUpdate(CreatePlayer& player, Vector2& pointerPosition, Vector2& playerPosition);
	void playerMovementUpdate(CreatePlayer& player, Vector2 pointerPosition);

	Vector2 NormalizeVector(Vector2 v);

	Vector2 dirVector;

	float angle;
	float angleToDegrees;


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
		player.maxMana = 100;
		player.mana = 100;
		player.manaRegenTimer = 0;
		player.manaRegenRate = 1;
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
		player.mana = 100;
		player.manaRegenTimer = 0;
		player.score = 0;
	}

	void resetPlayerPosition(CreatePlayer& player)
	{
		player.playerRect.x = Globals::Screen.size.x / 2;
		player.playerRect.y = Globals::Screen.size.y / 2;
		player.rotation = 0;
		player.speed = { 0, 0 };
		player.animationState = 1;
		player.mana = 100;
	}

	void updatePlayer(CreatePlayer& player, Vector2 pointerPosition)
	{
		player.position = { player.playerRect.x, player.playerRect.y };
		playerRotationUpdate(player, pointerPosition, player.position);

		player.animationState = checkAnimState(player);
		dirVector = NormalizeVector(dirVector);

		playerMovementUpdate (player, pointerPosition);
	}

	void updateMana(CreatePlayer& player)
	{
		player.manaRegenTimer += GetFrameTime();

		if (player.manaRegenTimer >= 0.1f) //speed
		{		
			if (player.mana < player.maxMana)
			{
				player.mana += static_cast<int>(player.manaRegenRate);
				if (player.mana > player.maxMana)
				{
					player.mana = player.maxMana;
				}
			}
			player.manaRegenTimer = 0.0f;
		}
	}

	void playerRotationUpdate(CreatePlayer& player, Vector2& pointerPosition, Vector2& playerPosition)
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

	void playerMovementUpdate(CreatePlayer& player, Vector2 pointerPosition)
	{
		if (pointerPosition.x < Globals::Screen.size.x && pointerPosition.y < Globals::Screen.size.y)
		{
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
			{
				player.speed.x += dirVector.x * player.acceleration * GetFrameTime();
				player.speed.y += dirVector.y * player.acceleration * GetFrameTime();
			}
		}
		if (player.speed.x > player.maxAcceleration) { player.speed.x = player.maxAcceleration; }
		if (player.speed.y > player.maxAcceleration) { player.speed.y = player.maxAcceleration; }
		player.playerRect.x += player.speed.x * GetFrameTime();
		player.playerRect.y += player.speed.y * GetFrameTime();
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

	void playerCheckColl(CreatePlayer& player , Slime::CreateSlime bigSlime[], Slime::CreateSlime mediumSlime[], Slime::CreateSlime smallSlime[])
	{
		for (int i = 0; i < Slime::maxBigSlimes; i++)
		{
			if (bigSlime[i].state && collisions::circleCircle({ player.playerRect.x , player.playerRect.y }, player.rad, bigSlime[i].position, bigSlime[i].rad))
			{
				player.hp -= 50;
				if (player.hp < 0)
				{
					player.hp = 0;
				}
				Game::spawnElements();
				resetPlayerPosition(player);
			}
		}
		for (int i = 0; i < Slime::maxMediumSlimes; i++)
		{
			if (mediumSlime[i].state && collisions::circleCircle(player.position, player.rad, mediumSlime[i].position, mediumSlime[i].rad))
			{
				player.hp -= 35;
				if (player.hp < 0)
				{
					player.hp = 0;
				}
				Game::spawnElements();
				resetPlayerPosition(player);
			}
		}
		for (int i = 0; i < Slime::maxSmallSlimes; i++)
		{
			if (smallSlime[i].state && collisions::circleCircle(player.position, player.rad, smallSlime[i].position, smallSlime[i].rad))
			{
				player.hp -= 25;
				if (player.hp < 0)
				{
					player.hp = 0;
				}
				Game::spawnElements();
				resetPlayerPosition(player);
			}
		}
	}


	Vector2 NormalizeVector(Vector2 v)
	{
		float length = sqrtf(v.x * v.x + v.y * v.y);
		if (length != 0.0f)
		{
			v.x /= length;
			v.y /= length;
		}
		return v;
	}

}