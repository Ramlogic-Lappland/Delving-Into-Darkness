#include "game.h"

#include "raylib.h"
#include <iostream>
#include <cmath>


#include "Delving_Into_Darkness.h"
#include "globals.h"
#include "collisionManager/collisionManager.h"
#include "button/button.h"
#include "game/player/player.h"
#include "game/player/projectile/projectile.h"
#include "enemy/slime.h"
#include "imageLoader/imageLoader.h"

using namespace Player;
using namespace Projectile;
using namespace Slime;


namespace Game
{

	const int pointerOffSet = 10; //texture shows slightly off to the side of were the pointer is registered 

	button::createButton returnToMenuBttn;
	button::createButton playAgainBttn;

	CreatePlayer player;
	createProjectile projectile[playerMaxProjectiles];

	CreateSlime bigSlime[maxBigSlimes];
	CreateSlime mediumSlime[maxMediumSlimes];
	CreateSlime smallSlime[maxSmallSlimes];



	Music gameMusic;
	Sound fireBallWav;
	Sound slimeDeath;

	Vector2 pointerPosition = { 0.0f, 0.0f };
	Vector2 menuBttnPosition;
	Vector2 fireballOrigin;

	Image image;

	Texture2D gameBackground;
	Texture2D gameMenutexture;
	Texture2D DefeatMenuTexture;
	Texture2D menuBttn;
	Texture2D fireBallText;
	Texture2D pointerTex;



	float projectileSpawnDistance = 30.0f;
	float timePlayed = 0.0f;

	int fireBallFrameWidth;
	int fireBallFrameHeight;
	int maxFireBallFrames;
	float fireballFrameTime;


	bool gameInit = false;
	bool pause = false;
	bool pauseMenu = false;
	bool gameOver = false;


	/* ========================================================== INIT GAME =================================================================== */
	void initGame()
	{
		pause = false;
		pauseMenu = false;
		gameOver = false;

		pointerTex = LoadTexture("res/miscellaneous/cursor.png");

		// BUTTON Init
		
		initBttn(returnToMenuBttn, { 450, 350 }, { 350, 80 }, "res/ui/button/menu_button_1.png", "res/ui/button/menu_button_2.png", 2); // Return to menu button (amount of frames - position - path img1 - path img2 - resize)

		initBttn(playAgainBttn, { 450, 550 }, { 350, 80 }, "res/ui/button/playAgain_button_1.png", "res/ui/button/playAgain_button_2.png", 2); // Play again Button

		// END BUTTON Init

		imageLoader::initImage(gameBackground, { Globals::Screen.size.x, Globals::Screen.size.y }, "res/gamebackground/gameGridB.png"); // texture - size.x - size.y - path
		imageLoader::initImage(DefeatMenuTexture, { static_cast<float>(Globals::Screen.size.x * 0.75) , static_cast<float>(Globals::Screen.size.y * 0.75) }, "res/ui/defeatMenu.png");
		imageLoader::initImage(gameMenutexture, { static_cast<float>(Globals::Screen.size.x / 2) , static_cast<float>(Globals::Screen.size.y) }, "res/ui/ingame_menu_canvas.png");
		imageLoader::initImage(menuBttn, {40, 40}, "res/ui/ingame_menu_button.png");
		//imageLoader::initImage(, {}, );

		fireBallText = LoadTexture("res/character/projectile/Small_Fireball_10x26.png");

		projectile->frameWidth = fireBallText.width / 10;
		projectile->frameHeight = fireBallText.height / 6;
		maxFireBallFrames = 10;
		fireballFrameTime = 0.5f;

		slimeDeath = LoadSound("res/sounds/slimeDeath.wav");
		fireBallWav = LoadSound("res/sounds/fireball.wav");
		gameMusic = LoadMusicStream("res/sounds/gameSong.mp3");
		
		menuBttnPosition = { Globals::Screen.size.x - menuBttn.width - 20, static_cast<float>(0) };

		initPlayer(player); // init player
		spawnElements();
		
		SetMusicVolume(gameMusic, 0.2f);
		SetSoundVolume(fireBallWav, 0.16f);
		SetSoundVolume(slimeDeath, 0.2f);
		PlayMusicStream(gameMusic);

		gameInit = true;
	}
	/* ========================================================== INIT END =================================================================== */


	/* ========================================================== GAME UPDATE =============================================================== */
	void updateGame() 
	{
		UpdateMusicStream(gameMusic);
		timePlayed = GetMusicTimePlayed(gameMusic) / GetMusicTimeLength(gameMusic);
		if (timePlayed > 1.0f) timePlayed = 1.0f;

		pointerPosition = GetMousePosition();

		if (gameOver == true)
		{
			if (collisions::rectangleXrectangle(playAgainBttn.position.x, playAgainBttn.position.y, playAgainBttn.width, playAgainBttn.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)))
			{
				playAgainBttn.buttonFrame = 1;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					resetGame();
				}
			}
			else
			{
				playAgainBttn.buttonFrame = 0;
			}

			if (collisions::rectangleXrectangle(returnToMenuBttn.position.x, returnToMenuBttn.position.y, returnToMenuBttn.width, returnToMenuBttn.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)))
			{
				returnToMenuBttn.buttonFrame = 1;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					gameManager::CurrentScreen = gameManager::menu;
				}
			}
			else
			{
				returnToMenuBttn.buttonFrame = 0;
			}
		}


		if (gameOver == false)
		{
			// Menu logic
			if (collisions::rectangleXrectangle(returnToMenuBttn.position.x, returnToMenuBttn.position.y, returnToMenuBttn.width, returnToMenuBttn.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)) && pauseMenu == true)
			{
				returnToMenuBttn.buttonFrame = 1;
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					gameManager::CurrentScreen = gameManager::menu;
				}
			}
			else
			{
				returnToMenuBttn.buttonFrame = 0;
			}

			if (IsKeyPressed(KEY_P))
			{
				pauseMenu = !pauseMenu;
			}
			if (pointerPosition.x > menuBttnPosition.x && pointerPosition.x < menuBttnPosition.x + menuBttn.width && pointerPosition.y > 0 && pointerPosition.y < menuBttn.height)
			{
				if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
				{
					pauseMenu = !pauseMenu;
				}
			}// End menu logic 

			//Game over logic
			if (player.hp <= 0 || player.score >= 3150) // delete score once respawn for  enemies is applied
			{
				gameOver = true;
			}//End of game over logic

			if (pauseMenu == false)
			{
				if (pause == false)
				{
					/*====================================================== PLAYER ======================================================*/

					updatePlayer(player, pointerPosition); // player rotation & movement update 

					playerBounds(player); // checks if player hits the wall and spawns on oposite side

					playerCheckColl(player, bigSlime, mediumSlime, smallSlime); // check player collisions

					/*=================================================== PLAYER END ======================================================*/

					/*====================================================== PROJECTILE ======================================================*/
					if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
					{
						createProjectile* newProjectile = GetInactiveProjectile();
						if (newProjectile != nullptr)
						{
							newProjectile->position = {
								player.playerRect.x + dirVector.x * projectileSpawnDistance,
								player.playerRect.y + dirVector.y * projectileSpawnDistance
							};
							newProjectile->direction = dirVector;
							newProjectile->state = true;
							newProjectile->rotation = player.rotation;
							newProjectile->currentFireballFrame = 0;
							newProjectile ->fireballFrameCounter = 0;
							PlaySound(fireBallWav);
						}
					}

					updateProjectiles(projectile, playerMaxProjectiles);
					/*
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
									PlaySound(slimeDeath);
									bigSlime[a].state = false;
									player.score += 25;
									Vector2 spawnSpeed = { bigSlime[a].speed.x * 2, bigSlime[a].speed.y * 2 };
									spawnSlime(mediumSlime, maxMediumSlimes, MEDIUM, { bigSlime[a].position.x, bigSlime[a].position.y }, spawnSpeed);
									spawnSlime(mediumSlime, maxMediumSlimes, MEDIUM, { bigSlime[a].position.x + 75, bigSlime[a].position.y }, spawnSpeed);
								}
							}
							for (int b = 0; b < maxMediumSlimes; b++)
							{
								if (mediumSlime[b].state && collisions::circleCircle(mediumSlime[b].position, mediumSlime[b].rad, projectile[i].position, projectile[i].radius))
								{
									projectile[i].state = false;
									projectile[i].lifeSpawn = 0;
									PlaySound(slimeDeath);
									mediumSlime[b].state = false;
									player.score += 50;
									Vector2 spawnSpeed = { mediumSlime[b].speed.x * 2, mediumSlime[b].speed.y * 2 };
									spawnSlime(smallSlime, maxSmallSlimes, SMALL, { mediumSlime[b].position.x, mediumSlime[b].position.y }, spawnSpeed);
									spawnSlime(smallSlime, maxSmallSlimes, SMALL, { mediumSlime[b].position.x + 55, mediumSlime[b].position.y + 55 }, spawnSpeed);
								}
							}
							for (int c = 0; c < maxSmallSlimes; c++)
							{
								if (smallSlime[c].state && collisions::circleCircle(smallSlime[c].position, smallSlime[c].rad, projectile[i].position, projectile[i].radius))
								{
									projectile[i].state = false;
									projectile[i].lifeSpawn = 0;
									smallSlime[c].state = false;
									player.score += 75;
								}
							}
						}
					}
					*/
					updateProjectileCollition( player, projectile, bigSlime, mediumSlime,  smallSlime);

					/*=================================================== PROJECTILE LOGIC END ======================================================*/

					/*====================================================== SLIME ======================================================*/
					// SLIME MOVEMENT
					for (int i = 0; i < maxBigSlimes; i++) // BIG
					{
						if (bigSlime[i].state)
						{
							slimeBounds(bigSlime[i]);
							bigSlime[i].position.x += bigSlime[i].speed.x * GetFrameTime();
							bigSlime[i].position.y += bigSlime[i].speed.y * GetFrameTime();
						}
					}
					for (int i = 0; i < maxMediumSlimes; i++) // MEDIUM
					{
						if (mediumSlime[i].state)
						{
							slimeBounds(mediumSlime[i]);
							mediumSlime[i].position.x += mediumSlime[i].speed.x * GetFrameTime();
							mediumSlime[i].position.y += mediumSlime[i].speed.y * GetFrameTime();
						}
					}
					for (int i = 0; i < maxSmallSlimes; i++) // SMALL
					{
						if (smallSlime[i].state)
						{
							slimeBounds(smallSlime[i]);
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

#ifdef _DEBUG // hit Boxes
		DrawCircle(static_cast<int>(player.position.x + 2), static_cast<int>(player.position.y), player.rad, RED); // player hitbox
		for (int i = 0; i < playerMaxProjectiles; i++)
		{
			if (projectile[i].state)
			{
			DrawCircleV(projectile[i].position, projectile[i].radius, RED); //projectile hitbox		
			}
		}
		DrawText(TextFormat("Angle in radians: %.2f", angle), 10, 60, 20, WHITE);
		DrawText(TextFormat("Angle in degrees: %.2f", angleToDegrees), 10, 80, 20, WHITE);
		DrawText(TextFormat("animation state: %i", player.animationState), 10, 100, 20, WHITE);
#endif	     // end hit boxes

		drawProjectiles(projectile, playerMaxProjectiles, fireBallText);
		
		DrawTexturePro(player.playerTexture, player.playerTextureCoordinate, player.playerRect, player.pivot, player.rotation, WHITE);

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

		if (pauseMenu == false)
		{
			DrawText(TextFormat("SCORE: %i", player.score), 900, 50, 30, WHITE);
		}
		DrawText(TextFormat("HP: %i", player.hp), 900, 100, 20, WHITE);
		DrawTexture(menuBttn, static_cast<int>(menuBttnPosition.x), static_cast<int>(menuBttnPosition.y), WHITE);

		if (pauseMenu == true)
		{
			DrawTexture(gameMenutexture, 300, 0, WHITE);
			DrawText(TextFormat("SCORE: %i", player.score), 500, 150, 30, RED);
			DrawTexture(returnToMenuBttn.buttonText[returnToMenuBttn.buttonFrame], static_cast<int>(returnToMenuBttn.position.x), static_cast<int>(returnToMenuBttn.position.y), WHITE);
		}

		if (gameOver == true)
		{
			DrawTexture(DefeatMenuTexture, 150, 100, LIGHTGRAY);
			DrawText(TextFormat("SCORE: %i", player.score), 500, 250, 50, RED);
			DrawTexture(returnToMenuBttn.buttonText[returnToMenuBttn.buttonFrame], static_cast<int>(returnToMenuBttn.position.x), static_cast<int>(returnToMenuBttn.position.y), LIGHTGRAY);
			DrawTexture(playAgainBttn.buttonText[playAgainBttn.buttonFrame], static_cast<int>(playAgainBttn.position.x), static_cast<int>(playAgainBttn.position.y), LIGHTGRAY);
		}

		DrawTexture(pointerTex, static_cast<int>(pointerPosition.x) - pointerOffSet, static_cast<int>(pointerPosition.y) - pointerOffSet, WHITE);
		
	}

	void unloadGame()
	{
		std::cout << "UNLOADING GAME --------------------------------" << "\n";

		for (int i = 0; i < returnToMenuBttn.amountOfFrames; i++)
		{
			UnloadTexture(returnToMenuBttn.buttonText[i]);
		}
		delete[] returnToMenuBttn.buttonText;

		for (int i = 0; i < playAgainBttn.amountOfFrames; i++)
		{
			UnloadTexture(playAgainBttn.buttonText[i]);
		}
		delete[] playAgainBttn.buttonText;

		UnloadTexture(player.playerTexture);
		UnloadTexture(gameBackground);
		UnloadTexture(fireBallText);
		UnloadTexture(gameMenutexture);
		UnloadTexture(DefeatMenuTexture);
		UnloadTexture(pointerTex);
		UnloadSound(fireBallWav);
		UnloadSound(slimeDeath);
		UnloadMusicStream(gameMusic);

		std::cout << "GAME UNLOADED --------------------------------" << "\n";
	}


	/* ========================================================= FUNCTIONS ========================================================= */


	createProjectile* GetInactiveProjectile() 
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


	void spawnElements()
	{
		for (int i = 0; i < maxBigSlimes; i++)
		{
			bigSlime[i].rad = 40.0f;
			bigSlime[i].type = BIG;
			getSpawnOutOfBounds(bigSlime[i]);
			getRadomSpawnDirection(bigSlime[i]);
			bigSlime[i].state = true;
		}
		for (int i = 0; i < maxMediumSlimes; i++)
		{
			mediumSlime[i].rad = 30.0f;
			mediumSlime[i].type = MEDIUM;
			mediumSlime[i].state = false;
		}
		for (int i = 0; i < maxSmallSlimes; i++)
		{
			smallSlime[i].rad = 20.0f;
			smallSlime[i].type = SMALL;
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

	void resetGame()
	{
		resetPlayer(player);
		spawnElements();
		PlayMusicStream(gameMusic);
		pause = false;
		pauseMenu = false;
		gameOver = false;
	}
	/* ====================================================== FUNCTIONS  END ========================================================= */
}
