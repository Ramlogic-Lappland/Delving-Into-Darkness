#pragma once

#include "raylib.h"

#include "game/player/player.h"

namespace Projectile
{
	const int playerMaxProjectiles = 8;

	struct createProjectile
	{
		Rectangle frameRec;

		Vector2 position;
		Vector2 size;
		Vector2 direction;

		float radius;
		float rotation;
		float speed;
		float fireballFrameCounter;
		float frameTime;

		int currentFrame;
		int currentFireballFrame;
		int maxFireBallFrames;
		int frameWidth;
		int frameHeight;
		int lifeSpawn;
		int currentRow;

		bool state;
	};


	void updateProjectiles(createProjectile projectile[], int maxProyectiles, Texture2D& texture);

	void updateProjectileAnimation(createProjectile& projectile, float deltaTime, int rows, int cols, Texture2D& texture);

	void drawProjectiles(createProjectile projectiles[], int projectileCount, Texture2D& projectileTexture);

	void updateProjectileCollition(Player::CreatePlayer& player, createProjectile projectile[], Slime::CreateSlime bigSlime[], Slime::CreateSlime mediumSlime[], Slime::CreateSlime smallSlime[]);

}