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
    //void drawProjectile(createProjectile& projectile, Texture2D& fireballTexture);
    //void updateProjectileAnimation(createProjectile& projectile);
    void drawProjectile(createProjectile& projectile, Texture2D& projectileTexture);
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


    void updateProjectiles(createProjectile projectiles[], int maxProyectiles, Texture2D& texture)
    {
        for (int i = 0; i < maxProyectiles; i++)
        {
            if (projectiles[i].state)
            {
                //updateProjectileAnimation(projectiles[i]);

                updateProjectileAnimation(projectiles[i], GetFrameTime(), 6, 10, texture);

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
                        bigSlime[i].currentFrame = 0;
                        bigSlime[i].frameTime = 0.0f;

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
                        mediumSlime[i].currentFrame = 0;
                        mediumSlime[i].frameTime = 0.0f;

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
                        smallSlime[i].currentFrame = 0;
                        smallSlime[i].frameTime = 0.0f;
                    }
                }
            }
        }
        
    }

    void updateProjectileAnimation(createProjectile& projectile, float deltaTime, int rows, int cols, Texture2D& texture)
    {
        projectile.frameTime += deltaTime;

        if (projectile.frameTime >= 0.2f)
        {
            projectile.frameTime = 0.0f;

            projectile.currentFrame++;

            if (projectile.currentFrame >= cols)
            {
                projectile.currentFrame = 0;
                projectile.currentRow++;


                if (projectile.currentRow >= rows)
                {
                    projectile.currentRow = 0;
                }
            }
        }

        
        float frameWidth = texture.width / static_cast<float>(cols);
        float frameHeight = texture.height / static_cast<float>(rows);

        projectile.frameRec.x = projectile.currentFrame * frameWidth;
        projectile.frameRec.y = projectile.currentRow * frameHeight;
        projectile.frameRec.width = frameWidth;
        projectile.frameRec.height = frameHeight;
    }

    void drawProjectiles(createProjectile projectiles[], int projectileCount, Texture2D& projectileTexture)
    {
        for (int i = 0; i < projectileCount; i++)
        {
            if (projectiles[i].state) // Only draw active projectiles
            {
                drawProjectile(projectiles[i], projectileTexture);
            }
        }
    }

    void drawProjectile(createProjectile& projectile, Texture2D& projectileTexture)
    {
        float scale = projectile.radius / (projectile.frameRec.width / 2.0f); // Scale based on projectile radius

        Rectangle textureRec = { projectile.position.x, projectile.position.y, projectile.frameRec.width * scale, projectile.frameRec.height * scale };

        Vector2 originTexture = { textureRec.width / 2.0f, textureRec.height / 2.0f };

        DrawTexturePro(projectileTexture, projectile.frameRec, textureRec, originTexture, projectile.rotation, WHITE);
    }

    

    Vector2 calculateSplitSpeed(Vector2 originalSpeed, float angleOffset)
    {
        float speedMagnitude = sqrt(originalSpeed.x * originalSpeed.x + originalSpeed.y * originalSpeed.y);
        float originalAngle = atan2(originalSpeed.y, originalSpeed.x);

        float newAngle = originalAngle + angleOffset;
        return { static_cast<float>( ( cos ( newAngle ) * speedMagnitude ) * 1.5 ), static_cast<float>( ( sin ( newAngle ) * speedMagnitude ) * 1.5 ) };
    }
}

