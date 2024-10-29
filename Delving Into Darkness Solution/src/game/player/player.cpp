#include "player.h"

#include <cmath>

namespace Player
{
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

}