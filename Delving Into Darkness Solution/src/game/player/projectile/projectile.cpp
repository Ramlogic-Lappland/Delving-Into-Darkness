#include "projectile.h"

#include <cmath>

#include "raylib.h"

#include "game/player/player.h"
#include "globals.h"

namespace Projectile
{
    void drawProjectile(createProjectile& projectile, Texture2D& fireballTexture);
    void updateProjectileAnimation(createProjectile& projectile);

	void spawnProjectile(createProjectile& projectile, Player::CreatePlayer& player, Vector2 dirVector)
	{
		projectile.position =
        {
            static_cast<float>(player.playerRect.x + (sin(player.rotation * DEG2RAD) * player.playerRect.height)),
            static_cast<float>(player.playerRect.y - (cos(player.rotation * DEG2RAD) *  player.playerRect.height))
        };
		projectile.state = true;
		projectile.direction.x = (dirVector.x * player.speed.x * GetFrameTime()) * -1;
		projectile.direction.y = (dirVector.y * player.speed.y * GetFrameTime()) * -1;
		projectile.rotation = player.rotation;
	}

    void updateProjectiles(createProjectile projectile[], int maxProyectiles)
    {
        for (int i = 0; i < maxProyectiles; i++)
        {
            if (projectile[i].state)
            {
                updateProjectileAnimation(projectile[i]);

                projectile[i].position.x += projectile[i].direction.x * projectile[i].speed * GetFrameTime();
                projectile[i].position.y += projectile[i].direction.y * projectile[i].speed * GetFrameTime();

                // CHECK PROJECTILE BOUNDS
                if (projectile[i].position.x < 0 || projectile[i].position.x > Globals::Screen.size.x ||
                    projectile[i].position.y < 0 || projectile[i].position.y > Globals::Screen.size.y)
                {
                    projectile[i].state = false;
                }
            }
        }
    }

    void updateProjectileAnimation(createProjectile& projectile)
    {
        const float frameTime = 0.1f; 

        projectile.fireballFrameCounter += GetFrameTime();

        if (projectile.fireballFrameCounter >= frameTime) 
        {
            projectile.fireballFrameCounter = 0;
            projectile.currentFireballFrame++;

            if (projectile.currentFireballFrame >= projectile.maxFireBallFrames)
            {
                projectile.currentFireballFrame = 0;
            }
        }
    }

    void drawProjectiles(createProjectile projectiles[], int maxProjectiles, Texture2D& fireballTexture)
    {
        for (int i = 0; i < maxProjectiles; i++) 
        {
            if (projectiles[i].state) 
            {
                drawProjectile(projectiles[i], fireballTexture);
            }
        }
    }

    void drawProjectile(createProjectile& projectile, Texture2D& fireballTexture) 
    {
        int frameWidth = fireballTexture.width / 10;
        int frameHeight = fireballTexture.height / 6;

        Rectangle sourceRec =
        {
            static_cast<float>((projectile.currentFireballFrame % 10) * frameWidth),    
            static_cast<float>((projectile.currentFireballFrame / 10) * frameHeight),    
            static_cast<float>(frameWidth),                                           
            static_cast<float>(frameHeight)                                           
        };
        Rectangle destRec = 
        {   
            projectile.position.x,    
            projectile.position.y,    
            static_cast<float>(frameWidth),    
            static_cast<float>(frameHeight)
        };

        Vector2 origin = { frameWidth / 2.0f, frameHeight / 2.0f };

        DrawTexturePro(
            fireballTexture,   
            sourceRec,         
            destRec,           
            origin,            
            projectile.rotation, 
            WHITE              
        );

    }
}

