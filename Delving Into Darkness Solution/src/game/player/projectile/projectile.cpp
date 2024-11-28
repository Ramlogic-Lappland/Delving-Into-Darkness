#include "projectile.h"

#include <iostream>
#include <cmath>

#include "raylib.h"

#include "globals.h"
#include "collisionManager/collisionManager.h"
#include "game/game.h"
#include "game/player/player.h"
#include "game/player/player.h"
#include "game/enemy/slime.h"

namespace Projectile
{
    void drawProjectile(createProjectile& projectile, Texture2D& fireballTexture);
    void updateProjectileAnimation(createProjectile& projectile);
    Vector2 calculateSplitSpeed(Vector2 originalSpeed, float angleOffset);


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

    void updateProjectileCollition(Player::CreatePlayer& player, createProjectile projectile[], Slime::CreateSlime bigSlime[], Slime::CreateSlime mediumSlime[], Slime::CreateSlime smallSlime[])
    {

        for (int i = 0; i < playerMaxProjectiles; i++)
        {
            if (projectile[i].state)
            {
                for (int a = 0; a < Slime::maxBigSlimes; a++)
                {
                    if (bigSlime[a].state && collisions::circleCircle(bigSlime[a].position, bigSlime[a].rad, projectile[i].position, projectile[i].radius))
                    {
                        projectile[i].state = false;
                        projectile[i].lifeSpawn = 0;
                        PlaySound(Game::slimeDeath);
                        bigSlime[a].state = false;
                        player.score += 25;

                        spawnSlime(mediumSlime, Slime::maxMediumSlimes, Slime::MEDIUM,
                                   bigSlime[a].position, calculateSplitSpeed(bigSlime[a].speed, 45.0f * DEG2RAD));
                        spawnSlime(mediumSlime, Slime::maxMediumSlimes, Slime::MEDIUM,
                                   bigSlime[a].position, calculateSplitSpeed(bigSlime[a].speed, -45.0f * DEG2RAD));
                    }
                }
                for (int b = 0; b < Slime::maxMediumSlimes; b++)
                {
                    if (mediumSlime[b].state && collisions::circleCircle(mediumSlime[b].position, mediumSlime[b].rad, projectile[i].position, projectile[i].radius))
                    {
                        projectile[i].state = false;
                        projectile[i].lifeSpawn = 0;
                        PlaySound(Game::slimeDeath);
                        mediumSlime[b].state = false;
                        player.score += 50;

                        spawnSlime(smallSlime, Slime::maxSmallSlimes, Slime::SMALL,
                                   mediumSlime[b].position, calculateSplitSpeed(mediumSlime[b].speed, +45.0f * DEG2RAD));
                        spawnSlime(smallSlime, Slime::maxSmallSlimes, Slime::SMALL,
                                   mediumSlime[b].position, calculateSplitSpeed(mediumSlime[b].speed, -45.0f * DEG2RAD));
                    }
                }
                for (int c = 0; c < Slime::maxSmallSlimes; c++)
                {
                    if (smallSlime[c].state && collisions::circleCircle(smallSlime[c].position, smallSlime[c].rad, projectile[i].position, projectile[i].radius))
                    {
                        projectile[i].state = false;
                        projectile[i].lifeSpawn = 0;
                        PlaySound(Game::slimeDeath);
                        smallSlime[c].state = false;
                        player.score += 75;
                    }
                }
            }
        }
        
    }

    void updateProjectileAnimation(createProjectile& projectile) // need to fix it does not swap animation 
    {
        const float frameTime = 0.002f;

        projectile.fireballFrameCounter += GetFrameTime();
        //std::cout << "Fireball Frame Counter: " << projectile.fireballFrameCounter << std::endl;  it increases

        if (projectile.fireballFrameCounter >= frameTime) 
        {
            projectile.fireballFrameCounter = 0;
            projectile.currentFireballFrame++;

            

           // std::cout << "Fireball Frame Counter: " << projectile.fireballFrameCounter << std::endl; it increases

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
            static_cast<float>((projectile.currentFireballFrame % 10) * frameWidth),  // X pos - divides % the current frame so it gives a round nuumber that can be attached to a specific frame same as below /
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

    Vector2 calculateSplitSpeed(Vector2 originalSpeed, float angleOffset)
    {
        float speedMagnitude = sqrt(originalSpeed.x * originalSpeed.x + originalSpeed.y * originalSpeed.y);
        float originalAngle = atan2(originalSpeed.y, originalSpeed.x);

        float newAngle = originalAngle + angleOffset;
        return { static_cast<float>( ( cos ( newAngle ) * speedMagnitude ) * 1.5 ), static_cast<float>( ( sin ( newAngle ) * speedMagnitude ) * 1.5 ) };
    }
}

