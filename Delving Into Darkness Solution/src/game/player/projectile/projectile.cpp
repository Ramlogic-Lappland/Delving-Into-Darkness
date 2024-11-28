#include "projectile.h"

#include <iostream>
#include <cmath>

#include "raylib.h"

#include "game/player/player.h"
#include "globals.h"
#include "game/player/player.h"

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



    void updateProjectiles(createProjectile projectiles[], int maxProyectiles)
    {
        for (int i = 0; i < maxProyectiles; i++)
        {
            if (projectiles[i].state)
            {
                updateProjectileAnimation(projectiles[i]);

                projectiles[i].position.x += projectiles[i].direction.x * projectiles[i].speed * GetFrameTime();
                projectiles[i].position.y += projectiles[i].direction.y * projectiles[i].speed * GetFrameTime();

                // CHECK PROJECTILE BOUNDS
                if (projectiles[i].position.x < 0 || projectiles[i].position.x > Globals::Screen.size.x ||
                    projectiles[i].position.y < 0 || projectiles[i].position.y > Globals::Screen.size.y)
                {
                    projectiles[i].state = false;
                }
            }
        }
    }

    void updateProjectileAnimation(createProjectile& projectile)
    {
        const float frameTime = 0.002f;

        projectile.fireballFrameCounter += GetFrameTime();
        //std::cout << "Fireball Frame Counter: " << projectile.fireballFrameCounter << std::endl;

        if (projectile.fireballFrameCounter >= frameTime) 
        {
            projectile.fireballFrameCounter = 0;
            projectile.currentFireballFrame++;

            

           // std::cout << "Fireball Frame Counter: " << projectile.fireballFrameCounter << std::endl;

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
            static_cast<float>((projectile.currentFireballFrame / 10) * frameWidth),  // X pos
            static_cast<float>((projectile.currentFireballFrame / 10) *  frameHeight), // y pos
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

