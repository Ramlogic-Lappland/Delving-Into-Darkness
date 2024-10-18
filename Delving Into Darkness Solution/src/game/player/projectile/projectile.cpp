#include "projectile.h"

#include "raylib.h"
#include <math.h>

#include "game/player/player.h"

namespace Projectile
{
	void spawnProjectile(createProjectile& projectile, Player::CreatePlayer& player)
	{
		projectile.position = {static_cast<float>(player.playerRect.x + (sin(player.rotation * DEG2RAD) * player.playerRect.height)), static_cast<float>(player.playerRect.y - (cos(player.rotation * DEG2RAD) *  player.playerRect.height))};
		projectile.state = true;
		projectile.speed.x = static_cast<float>(1.5f * sin(player.rotation * DEG2RAD) * player.speed.x);
		projectile.speed.y = static_cast<float>(1.5f * cos(player.rotation * DEG2RAD) * player.speed.y);
		projectile.rotation = player.rotation;
	}
}