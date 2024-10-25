#include "projectile.h"

#include "raylib.h"
#include <cmath>

#include "game/player/player.h"

namespace Projectile
{

	void spawnProjectile(createProjectile& projectile, Player::CreatePlayer& player, Vector2 dirVector)
	{
		projectile.position = {static_cast<float>(player.playerRect.x + (sin(player.rotation * DEG2RAD) * player.playerRect.height)), static_cast<float>(player.playerRect.y - (cos(player.rotation * DEG2RAD) *  player.playerRect.height)) };
		projectile.state = true;
		projectile.direction.x = (dirVector.x * player.speed.x * GetFrameTime()) * -1;
		projectile.direction.y = (dirVector.y * player.speed.y * GetFrameTime()) * -1;
		projectile.rotation = player.rotation;
	}


	/*
	  	createProjectile* GetInactiveBullet(createProjectile& projectile) 
	{
		if (!projectile.state) {
			return &projectile;
		}

		return nullptr;  
	}
	*/
}