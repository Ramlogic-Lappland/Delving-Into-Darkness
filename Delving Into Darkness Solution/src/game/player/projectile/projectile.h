#pragma once

#include "raylib.h"
#include "game/player/player.h"

namespace Projectile
{
	struct createProjectile
	{

		Vector2 position;
		Vector2 size;
		Vector2 direction;

		float radius;
		float rotation;
		float speed;
		float fireballFrameCounter;

		int currentFireballFrame;
		int lifeSpawn;

		bool state;
	};
	void spawnProjectile(createProjectile& projectile, Player::CreatePlayer& player,Vector2 dirVector);
}