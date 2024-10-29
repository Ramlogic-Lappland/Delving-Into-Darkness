#include "game.h"

#include "raylib.h"
#include <iostream>
#include <cmath>

#include "Delving_Into_Darkness.h"
#include "globals.h"
#include "collisionManager/collisionManager.h"

#include "game/player/player.h"
#include "game/player/projectile/projectile.h"

#include "enemy/slime.h"

namespace Game
{
	const int playerMaxProjectiles = 3;
	const int maxBigSlimes = 6;
	const int maxMediumSlimes = 12;
	const int maxSmallSlimes = 24;
	const int bigSlimeSpeed = 200;
	const int mediumSlimeSpeed = 400;
	const int smallSlimeSpeed = 600;

	Player::CreatePlayer player;
	Projectile::createProjectile projectile[playerMaxProjectiles];

	Slime::CreateSlime bigSlime[maxBigSlimes];
	Slime::CreateSlime mediumSlime[maxMediumSlimes];
	Slime::CreateSlime smallSlime[maxSmallSlimes];

	Vector2 pointerPosition = { 0.0f, 0.0f };
	Vector2 dirVector;
	Vector2 menuBttnPosition;

	Texture2D gameBackground;
	Texture2D menuBttn;
	Image image;

	Sound fireBallWav;

	float rotationSpeed = 100.0f;
	float angle;
	float angleToDegrees;
	float projectileSpawnDistance = 30.0f;

	bool pause = false;
	bool pauseMenu = false;
	bool gameOver = false;


	/* ========================================================== INIT GAME =================================================================== */
	void initGame()
	{
		SetExitKey(0);

		image = LoadImage("res/gamebackground/gameGridB.png");
		ImageResize(&image, static_cast<int>(Globals::Screen.size.x), static_cast<int>(Globals::Screen.size.y));
		gameBackground = LoadTextureFromImage(image);
		UnloadImage(image);

		image = LoadImage("res/ui/ingame_menu_button.png");
		ImageResize(&image, 40, 40);
		menuBttn = LoadTextureFromImage(image);
		UnloadImage(image);

		fireBallWav = LoadSound("res/sounds/fireball.wav");

		player.playerTexture = LoadTexture("res/character/test.png");
		player.playerRect = { Globals::Screen.size.x /2, Globals::Screen.size.y / 2, 45, 45};
		player.playerTextureCoordinate = { 0, 0, 45, 45 };
		player.pivot = { static_cast<float>(player.playerTexture.width/2), static_cast<float>(player.playerTexture.height/2) };
		player.rotation = 0;
		player.animationState = 1;
		player.maxAcceleration = 700;
		player.acceleration = 400.0f;
		player.rad = 18.0f;
		player.hp = 100;

		menuBttnPosition = { Globals::Screen.size.x - menuBttn.width - 20, static_cast<float>( 0 ) };

		spawnElements();
		SetSoundVolume(fireBallWav, 0.16f);
	}
	/* ========================================================== INIT END =================================================================== */


	/* ========================================================== GAME UPDATE =============================================================== */
	void updateGame() 
	{
		pointerPosition = GetMousePosition();

		if (gameOver == true)
		{
			if (IsKeyPressed(KEY_ENTER))
			{
				initGame();
			}
		}

		if (gameOver == false)
		{

			if (IsKeyPressed(KEY_ESCAPE))
			{
				pauseMenu = !pauseMenu;
			}
			if (pointerPosition.x > menuBttnPosition.x && pointerPosition.x < menuBttnPosition.x + menuBttn.width && pointerPosition.y > 0 && pointerPosition.y < menuBttn.height)
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					pauseMenu = !pauseMenu;
				}
			}

			if (player.hp < 0)
			{
				gameOver = true;
			}
			if (pauseMenu == false)
			{
				if (pause == false)
				{
					/*====================================================== PLAYER ======================================================*/					
					player.position = { player.playerRect.x, player.playerRect.y };
					Player::playerRotationUpdate(player, dirVector, pointerPosition, player.position, angle, angleToDegrees);
					player.animationState = Player::checkAnimState(player);
					dirVector = NormalizeVector(dirVector);


					if (pointerPosition.x < Globals::Screen.size.x && pointerPosition.y < Globals::Screen.size.y)
					{
						if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT))
						{

							player.speed.x += dirVector.x * player.acceleration * GetFrameTime();
							player.speed.y += dirVector.y * player.acceleration * GetFrameTime();
						}
					}
					if (player.speed.x > player.maxAcceleration) { player.speed.x = player.maxAcceleration; }
					if (player.speed.y > player.maxAcceleration) { player.speed.y = player.maxAcceleration; }
					player.playerRect.x += player.speed.x * GetFrameTime();
					player.playerRect.y += player.speed.y * GetFrameTime();
					playerBounds(); // checks if player hits the wall and spawns on oposite side

					for (int i = 0; i < maxBigSlimes; i++)
					{
						if (bigSlime[i].state && collisions::circleCircle({ player.playerRect.x , player.playerRect.y }, player.rad, bigSlime[i].position, bigSlime[i].rad))
						{
							player.hp -= 50;
							spawnElements();
						}
					}
					for (int i = 0; i < maxMediumSlimes; i++)
					{
						if (mediumSlime[i].state && collisions::circleCircle(player.position, player.rad, mediumSlime[i].position, mediumSlime[i].rad))
						{
							player.hp -= 25;
							spawnElements();
						}
					}
					for (int i = 0; i < maxSmallSlimes; i++)
					{
						if (smallSlime[i].state && collisions::circleCircle(player.position, player.rad, smallSlime[i].position, smallSlime[i].rad))
						{
							player.hp -= 15;
							spawnElements();
						}
					}
					/*=================================================== PLAYER END ======================================================*/

					/*====================================================== PROJECTILE ======================================================*/
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						Projectile::createProjectile* newProjectile = GetInactiveProjectile();
						if (newProjectile != nullptr)
						{
							newProjectile->position = {
								player.playerRect.x + dirVector.x * projectileSpawnDistance,
								player.playerRect.y + dirVector.y * projectileSpawnDistance
							};
							newProjectile->direction = dirVector;
							newProjectile->state = true;
							PlaySound(fireBallWav);
						}
					}
					for (int i = 0; i < playerMaxProjectiles; i++)
					{
						if (projectile[i].state)
						{
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
					for (int i = 0; i < playerMaxProjectiles; i++)
					{
						if (projectile[i].state)
						{
							for (int a = 0; a < maxBigSlimes; a++)
							{
								if (bigSlime[a].state && collisions::circleCircle(bigSlime[a].position, bigSlime[a].rad, projectile[i].position, projectile[i].radius))
								{
									projectile[i].state = false;
									projectile[i].lifeSpawn = 0;
									bigSlime[a].state = false;
									player.score += 50;
									Vector2 spawnSpeed = { bigSlime[a].speed.x * 2, bigSlime[a].speed.y * 2 };
									Slime::spawnSlime(mediumSlime, maxMediumSlimes, Slime::MEDIUM, { bigSlime[a].position.x, bigSlime[a].position.y }, spawnSpeed);
									Slime::spawnSlime(mediumSlime, maxMediumSlimes, Slime::MEDIUM, { bigSlime[a].position.x + 75, bigSlime[a].position.y + 75 }, spawnSpeed);
								}
							}
						}
					}
					for (int i = 0; i < playerMaxProjectiles; i++)
					{
						if (projectile[i].state)
						{
							for (int a = 0; a < maxBigSlimes; a++)
							{
								if (bigSlime[a].state && collisions::circleCircle(bigSlime[a].position, bigSlime[a].rad, projectile[i].position, projectile[i].radius))
								{
									projectile[i].state = false;
									projectile[i].lifeSpawn = 0;
									bigSlime[a].state = false;
									player.score += 25;
									Vector2 spawnSpeed = { bigSlime[a].speed.x * 2, bigSlime[a].speed.y * 2 };
									Slime::spawnSlime(mediumSlime, maxMediumSlimes, Slime::MEDIUM, { bigSlime[a].position.x, bigSlime[a].position.y }, spawnSpeed);
									Slime::spawnSlime(mediumSlime, maxMediumSlimes, Slime::MEDIUM, { bigSlime[a].position.x + 75, bigSlime[a].position.y }, spawnSpeed);
								}
							}
							for (int b = 0; b < maxMediumSlimes; b++)
							{
								if (mediumSlime[b].state && collisions::circleCircle(mediumSlime[b].position, mediumSlime[b].rad, projectile[i].position, projectile[i].radius))
								{
									projectile[i].state = false;
									projectile[i].lifeSpawn = 0;
									mediumSlime[b].state = false;
									player.score += 50;
									Vector2 spawnSpeed = { mediumSlime[b].speed.x * 2, mediumSlime[b].speed.y * 2 };
									Slime::spawnSlime(smallSlime, maxSmallSlimes, Slime::SMALL, { mediumSlime[b].position.x, mediumSlime[b].position.y }, spawnSpeed);
									Slime::spawnSlime(smallSlime, maxSmallSlimes, Slime::SMALL, { mediumSlime[b].position.x + 55, mediumSlime[b].position.y + 55 }, spawnSpeed);
								}
							}
							for (int c = 0; c < maxSmallSlimes; c++)
							{
								if (smallSlime[c].state && collisions::circleCircle(smallSlime[c].position, smallSlime[c].rad, projectile[i].position, projectile[i].radius))
								{
									projectile[i].state = false;
									projectile[i].lifeSpawn = 0;
									smallSlime[c].state = false;
									player.score += 100;
								}
							}
						}
					}
					/*=================================================== PROJECTILE LOGIC END ======================================================*/

					/*====================================================== SLIME ======================================================*/
					// SLIME MOVEMENT
					for (int i = 0; i < maxBigSlimes; i++) // BIG
					{
						if (bigSlime[i].state)
						{
							Slime::slimeBounds(bigSlime[i]);
							bigSlime[i].position.x += bigSlime[i].speed.x * GetFrameTime();
							bigSlime[i].position.y += bigSlime[i].speed.y * GetFrameTime();
						}
					}
					for (int i = 0; i < maxMediumSlimes; i++) // MEDIUM
					{
						if (mediumSlime[i].state)
						{
							Slime::slimeBounds(mediumSlime[i]);
							mediumSlime[i].position.x += mediumSlime[i].speed.x * GetFrameTime();
							mediumSlime[i].position.y += mediumSlime[i].speed.y * GetFrameTime();
						}
					}
					for (int i = 0; i < maxSmallSlimes; i++) // SMALL
					{
						if (smallSlime[i].state)
						{
							Slime::slimeBounds(smallSlime[i]);
							smallSlime[i].position.x += smallSlime[i].speed.x * GetFrameTime();
							smallSlime[i].position.y += smallSlime[i].speed.y * GetFrameTime();
						}
					}
					/*====================================================== SLIME END ======================================================*/
				}
			}
		}
	}


	/* ========================================================== DRAW GAME ================================================================== */
	void drawGame()
	{
		DrawTexture(gameBackground, 0, 0, GRAY);
#ifdef _DEBUG
		for (int i = 0; i < playerMaxProjectiles; i++)
		{
			if (projectile[i].state) { DrawCircleV(projectile[i].position, projectile[i].radius, RED); }
		}
		DrawCircle(static_cast<int>(player.position.x), static_cast<int>(player.position.y), player.rad, RED);
#endif
		DrawTexturePro(player.playerTexture, player.playerTextureCoordinate, player.playerRect, player.pivot, player.rotation, WHITE);
#ifdef _DEBUG
		// Draw all big slimes
		for (int i = 0; i < maxBigSlimes; i++)
		{
			if (bigSlime[i].state) {
				DrawCircleV(bigSlime[i].position, bigSlime[i].rad, RED);
			}
		}
		// Draw all medium slimes
		for (int i = 0; i < maxMediumSlimes; i++)
		{
			if (mediumSlime[i].state) {
				DrawCircleV(mediumSlime[i].position, mediumSlime[i].rad, RED);
			}
		}
		// Draw all small slimes
		for (int i = 0; i < maxSmallSlimes; i++)
		{
			if (smallSlime[i].state) {
				DrawCircleV(smallSlime[i].position, smallSlime[i].rad, RED);
			}
		}
		DrawText(TextFormat("Angle in radians: %.2f", angle), 10, 60, 20, WHITE);
		DrawText(TextFormat("Angle in degrees: %.2f", angleToDegrees), 10, 80, 20, WHITE);
		DrawText(TextFormat("animation state: %i", player.animationState), 10, 100, 20, WHITE);
#endif
		DrawText(TextFormat("SCORE: %i", player.score), 900, 50, 30, WHITE);
		DrawText(TextFormat("HP: %i", player.hp), 900, 100, 20, WHITE);
		DrawTexture(menuBttn, static_cast<int>(menuBttnPosition.x), static_cast<int>(menuBttnPosition.y), WHITE);
		
	}

	void unloadGame()
	{
		std::cout << "UNLOADING GAME --------------------------------" << "\n";
		UnloadTexture(player.playerTexture);
		UnloadTexture(gameBackground);
		UnloadTexture(menuBttn);
		UnloadSound(fireBallWav);
		std::cout << "GAME UNLOADED --------------------------------" << "\n";
	}


	/* ========================================================= FUNCTIONS ========================================================= */
	Vector2 NormalizeVector(Vector2 v) 
	{
		float length = sqrtf(v.x * v.x + v.y * v.y);
		if (length != 0.0f) 
		{
			v.x /= length;
			v.y /= length;
		}
		return v;
	}

	Projectile::createProjectile* GetInactiveProjectile() 
	{
		for (int i = 0; i < playerMaxProjectiles; i++) 
		{
			if (!projectile[i].state) 
			{
				return &projectile[i];  // pointer to inactive bullet
			}
		}
		return nullptr;  // No inactive bullets available
	}

	void playerBounds()
	{
		if (player.playerRect.x > Globals::Screen.size.x + (player.playerRect.width * 1.5))
		{
			player.playerRect.x = static_cast<float>(0 - (player.playerRect.width));
		}
		if (player.playerRect.x < 0 - (player.playerRect.width * 1.5))
		{
			player.playerRect.x = static_cast<float>(Globals::Screen.size.x + player.playerRect.width);
		}
		if (player.playerRect.y > Globals::Screen.size.y + (player.playerRect.height * 1.5)) 
		{
			player.playerRect.y = static_cast<float>(0 - (player.playerRect.height));
		}
		if (player.playerRect.y < 0 - (player.playerRect.height * 1.5)) 
		{
			player.playerRect.y = static_cast<float>(Globals::Screen.size.y + player.playerRect.height);
		}
	}

	void spawnElements()
	{
		for (int i = 0; i < maxBigSlimes; i++)
		{
			bigSlime[i].rad = 40.0f;
			bigSlime[i].type = Slime::BIG;
			getSpawnOutOfBounds(bigSlime[i]);
			getRadomSpawnDirection(bigSlime[i]);
			bigSlime[i].state = true;
		}
		for (int i = 0; i < maxMediumSlimes; i++)
		{
			mediumSlime[i].rad = 30.0f;
			mediumSlime[i].type = Slime::MEDIUM;
			mediumSlime[i].state = false;
		}
		for (int i = 0; i < maxSmallSlimes; i++)
		{
			smallSlime[i].rad = 20.0f;
			smallSlime[i].type = Slime::SMALL;
			smallSlime[i].state = false;
		}
		for (int i = 0; i < playerMaxProjectiles; i++)
		{
			projectile[i].position = { 0, 0 };
			projectile[i].direction = { 0, 0 };
			projectile[i].speed = 720;
			projectile[i].radius = 10.0f;
			projectile[i].state = false;
		}
	}
	/* ====================================================== FUNCTIONS  END ========================================================= */
}
