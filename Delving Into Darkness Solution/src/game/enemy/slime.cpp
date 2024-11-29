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

    void updateSlimeMovement(CreateSlime slimes[], int array)
    {
        for (int i = 0; i < array; i++)
        {
            if (slimes[i].state)
            {
                slimeBounds(slimes[i]);
                updateSlimeAnimation(slimes[i], GetFrameTime());
                slimes[i].position.x += slimes[i].speed.x * GetFrameTime();
                slimes[i].position.y += slimes[i].speed.y * GetFrameTime();
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


    void spawnBigSlimesOverTime(CreateSlime bigSlime[])
    {
        int activeBigSlimes = 0;

        for (int i = 0; i < Slime::maxBigSlimes; i++)
        {
            if (bigSlime[i].state)
            {
                activeBigSlimes++;
            }
        }

        if (activeBigSlimes < 4) 
        {
            for (int i = 0; i < Slime::maxBigSlimes; i++)
            {
                if (!bigSlime[i].state)
                {
                    bigSlime[i].rad = 40.0f;
                    bigSlime[i].type = Slime::BIG;
                    Slime::getSpawnOutOfBounds(bigSlime[i]);
                    Slime::getRadomSpawnDirection(bigSlime[i]);
                    bigSlime[i].state = true;

                    activeBigSlimes++;
                    if (activeBigSlimes >= 4)
                    {
                        break;
                    }
                }
            }
        }
    }

    void updateSlimeAnimation(CreateSlime& slime, float deltaTime)
    {
        slime.frameTime += deltaTime;

        if (slime.frameTime >= 0.2f)
        {
            slime.frameTime = 0.0f;
            slime.currentFrame = (slime.currentFrame + 1) % 8;
        }

        slime.frameRec.x = slime.currentFrame * slime.frameRec.width;
        slime.frameRec.y = slime.frameRec.height * 1;
    }

    void drawSlime(CreateSlime& slime, Texture2D& slimeTexture)
    {
        float scale = (slime.rad * 2.5f) / slime.frameRec.width;

        Rectangle textureRec = { slime.position.x, slime.position.y, slime.frameRec.width * scale, slime.frameRec.height * scale };

        Vector2 originTexture = { textureRec.width / 2.0f, textureRec.height / 2.0f };

        DrawTexturePro(slimeTexture, slime.frameRec, textureRec, originTexture, 0.0f, WHITE);

    }
}