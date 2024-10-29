#include "slime.h"

#include <cmath>

#include "globals.h"

namespace Slime
{
	void getSpawnOutOfBounds(CreateSlime& slime)
	{
		slime.position.x = (rand() % 2 == 0) ? -50.0f : Globals::Screen.size.x + 50.0f;
        slime.position.y = (rand() % 2 == 0) ? -50.0f : Globals::Screen.size.y + 50.0f;
	}

	void getRadomSpawnDirection(CreateSlime& slime)
	{
        float angle = rand() % 360 * (PI / 180.0f);
        float speedMultiplier = (slime.type == Slime::BIG) ? 100.0f :
            (slime.type == Slime::MEDIUM) ? 150.0f : 200.0f;
        slime.speed = { cosf(angle) * speedMultiplier, sinf(angle) * speedMultiplier };
	}

    void spawnSlime(CreateSlime slime[], int arraySize,SlimeSize type, Vector2 spawnPosition, Vector2 spawnSpeed)
    {
        for (int i = 0; i < arraySize; i++)
        {
            if (!slime[i].state)  // Find inactive slime
            {
                slime[i].position = spawnPosition;
                slime[i].speed = spawnSpeed;
                slime[i].state = true;
                slime[i].type = type;
                break;
            }
        }
    }

	void slimeBounds(CreateSlime& slime)
	{
		if (slime.position.x > Globals::Screen.size.x + (slime.rad * 1.5))
		{
			slime.position.x = static_cast<float>(0 - (slime.rad));
		}
		if (slime.position.x < 0 - (slime.rad * 1.5))
		{
			slime.position.x = static_cast<float>(Globals::Screen.size.x + slime.rad);
		}
		if (slime.position.y > Globals::Screen.size.y + (slime.rad * 1.5))
		{
			slime.position.y = static_cast<float>(0 - (slime.rad));
		}
		if (slime.position.y < 0 - (slime.rad * 1.5))
		{
			slime.position.y = static_cast<float>(Globals::Screen.size.y + slime.rad);
		}
	}
}

/* OLD SLIME COLLISION LOGIC

		for (int i = 0; i < maxBigSlimes; i++) // BIG SLIME
		{
			if (bigSlime[i].state && collisions::circleCircle(bigSlime[i].position.x, bigSlime[i].position.y, bigSlime[i].rad, projectile[i].position.x, projectile[i].position.y, projectile[i].radius))
			{
				bigSlime[i].state = false;  // Destroy big slime

				// Spawn two medium slimes at the position of the big slime
				Vector2 spawnSpeed = { bigSlime[i].speed.x * 2.0f, bigSlime[i].speed.y * 2.0f };
				Slime::spawnSlime(mediumSlime, maxMediumSlimes, Slime::MEDIUM, { bigSlime[i].position.x, bigSlime[i].position.y }, spawnSpeed);
				Slime::spawnSlime(mediumSlime, maxMediumSlimes, Slime::MEDIUM, { bigSlime[i].position.x * -1, bigSlime[i].position.y * -1}, spawnSpeed);
			}
		}
		for (int i = 0; i < maxMediumSlimes; i++) // MEDIUM SLIME
		{
			if (mediumSlime[i].state && collisions::circleCircle(mediumSlime[i].position.x, mediumSlime[i].position.y, mediumSlime[i].rad, projectile[i].position.x, projectile[i].position.y, projectile[i].radius))  // Add your collision logic here
			{
				mediumSlime[i].state = false;  // Destroy medium slime

				// Spawn two small slimes at the position of the destroyed medium slime
				Vector2 spawnSpeed = { mediumSlime[i].speed.x * 2.0f, mediumSlime[i].speed.y * 2.0f };  // Increase speed for small slimes
				spawnSlime(smallSlime, maxSmallSlimes, Slime::SMALL, mediumSlime[i].position, spawnSpeed);
				spawnSlime(smallSlime, maxSmallSlimes, Slime::SMALL, mediumSlime[i].position, spawnSpeed);
			}
		}
		for (int i = 0; i < maxSmallSlimes; i++) // SMALL SLIME
		{
			if (smallSlime[i].state && collisions::circleCircle(smallSlime[i].position.x, smallSlime[i].position.y, smallSlime[i].rad, projectile[i].position.x, projectile[i].position.y, projectile[i].radius))  // Add your collision logic here
			{
				smallSlime[i].state = false;  // Destroy small slime
			}
		}

*/