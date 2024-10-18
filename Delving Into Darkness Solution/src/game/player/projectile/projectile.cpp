#include "projectile.h"

#include "raylib.h"
#include <math.h>

#include "game/player/player.h"

namespace Projectile
{
	void spawnProjectile(createProjectile& projectile, Player::CreatePlayer& player, Vector2 dirVector)
	{
		projectile.position = {static_cast<float>(player.playerRect.x + (sin(player.rotation * DEG2RAD) * player.playerRect.height)), static_cast<float>(player.playerRect.y - (cos(player.rotation * DEG2RAD) *  player.playerRect.height)) };
		projectile.state = true;
		projectile.speed.x = (dirVector.x * player.speed.x * GetFrameTime()) * -1;
		projectile.speed.y = (dirVector.y * player.speed.y * GetFrameTime()) * -1;
		projectile.rotation = player.rotation;
	}
}