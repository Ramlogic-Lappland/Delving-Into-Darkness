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
        float speedMultiplier = (slime.type == Slime::BIG) ? 140.0f :
            (slime.type == Slime::MEDIUM) ? 180.0f : 200.0f;
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