#pragma once

#include "raylib.h"
#include "game/player/player.h"

namespace Projectile
{
	const int playerMaxProjectiles = 3;

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
		int maxFireBallFrames;
		int frameWidth;
		int frameHeight;
		int lifeSpawn;

		bool state;
	};

	//void spawnProjectile(createProjectile projectile);

	void updateProjectiles(createProjectile projectile[], int maxProyectiles);

	void drawProjectiles(createProjectile projectiles[], int maxProjectiles, Texture2D& fireballTexture);

	void updateProjectileCollition(Player::CreatePlayer& player, createProjectile projectile[], Slime::CreateSlime bigSlime[], Slime::CreateSlime mediumSlime[], Slime::CreateSlime smallSlime[]);
}