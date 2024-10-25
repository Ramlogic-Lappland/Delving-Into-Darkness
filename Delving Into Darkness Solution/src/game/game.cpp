#include "game.h"

#include "raylib.h"
#include <iostream>
#include <cmath>

#include "Delving_Into_Darkness.h"
#include "globals.h"
#include "game/player/player.h"
#include "game/player/projectile/projectile.h"

namespace Game
{
#define PLAYER_MAX_PROJECTILES 15

	Player::CreatePlayer player;
	Projectile::createProjectile projectile[PLAYER_MAX_PROJECTILES];

	Vector2 pointerPosition = { 0.0f, 0.0f };
	Vector2 playerPosition;
	Vector2 dirVector;

	Texture2D gameBackground;
	Image image;

	float rotationSpeed = 100.0f;
	float angle;
	float angleToDegrees;

	float projectileSpawnDistance = 30.0f;

	void initGame()
	{
		//SetExitKey(0);
		player.playerTexture = LoadTexture("res/character/test.png");
		player.playerRect = { Globals::Screen.size.x /2, Globals::Screen.size.y / 2, 45, 45};
		player.playerTextureCoordinate = { 0, 0, 45, 45 };
		player.pivot = { static_cast<float>(player.playerTexture.width/2), static_cast<float>(player.playerTexture.height/2) };
		player.rotation = 0;
		player.animationState = 1;
		player.maxAcceleration = 700;
		player.acceleration = 400.0f;
		//player.maxAcceleration = 150.0f;

		image = LoadImage("res/gamebackground/gameGridB.png");     
		ImageResize(&image, static_cast<int>(Globals::Screen.size.x), static_cast<int>(Globals::Screen.size.y)); 
		gameBackground = LoadTextureFromImage(image);
		UnloadImage(image);

		for (int i = 0; i < PLAYER_MAX_PROJECTILES; i++)
		{
			projectile[i].position = { 0, 0 };
			projectile[i].direction = { 0, 0 };
			projectile[i].speed = 700;
			projectile[i].radius = 5.0f;
			projectile[i].state = false;
		}
	}

	void updateGame()
	{
		pointerPosition = GetMousePosition();
		playerPosition = { player.playerRect.x, player.playerRect.y };
		playerRotationUpdate();
		checkAnimState();
		dirVector = NormalizeVector(dirVector);


		if (pointerPosition.x < Globals::Screen.size.x && pointerPosition.y < Globals::Screen.size.y) {
			if (IsMouseButtonDown(MOUSE_BUTTON_RIGHT)) {
				
				player.speed.x += dirVector.x * player.acceleration * GetFrameTime();
				player.speed.y += dirVector.y * player.acceleration * GetFrameTime();
			}
		}
		if (player.speed.x > player.maxAcceleration) { player.speed.x = player.maxAcceleration; }
		if (player.speed.y > player.maxAcceleration) { player.speed.y = player.maxAcceleration; }
		player.playerRect.x += player.speed.x * GetFrameTime();
		player.playerRect.y += player.speed.y * GetFrameTime();

		if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
			Projectile::createProjectile* newProjectile = GetInactiveProjectile();
			if (newProjectile != nullptr) {
				newProjectile->position = {
					player.playerRect.x + dirVector.x * projectileSpawnDistance,
					player.playerRect.y + dirVector.y * projectileSpawnDistance
				};
				newProjectile->direction = dirVector;
				newProjectile->state = true;
			}
		}

		for (int i = 0; i < PLAYER_MAX_PROJECTILES; i++) {
			if (projectile[i].state) {
				projectile[i].position.x += projectile[i].direction.x * projectile[i].speed * GetFrameTime();
				projectile[i].position.y += projectile[i].direction.y * projectile[i].speed * GetFrameTime();

				// CHECK PROJECTILE BOUNDS
				if (projectile[i].position.x < 0 || projectile[i].position.x > Globals::Screen.size.x ||
					projectile[i].position.y < 0 || projectile[i].position.y > Globals::Screen.size.y) {
					projectile[i].state = false;  
				}
			}
		}

		playerBounds();

	}

	void drawGame()
	{
		DrawTexture(gameBackground, 0, 0, GRAY);
		DrawText(TextFormat("Angle in radians: %.2f", angle), 10, 10, 20, WHITE);
		DrawText(TextFormat("Angle in degrees: %.2f", angleToDegrees), 10, 40, 20, WHITE);
		DrawText(TextFormat("animation state: %i", player.animationState), 10, 80, 20, WHITE);
		for (int i = 0; i < PLAYER_MAX_PROJECTILES; i++)
		{
			if (projectile[i].state) { DrawCircleV(projectile[i].position, projectile[i].radius, RED); }
		}

		DrawTexturePro(player.playerTexture, player.playerTextureCoordinate, player.playerRect, player.pivot, player.rotation, WHITE);
	}

	void unloadGame()
	{
		std::cout << "UNLOADING GAME --------------------------------" << "\n";
		UnloadTexture(player.playerTexture);
		UnloadTexture(gameBackground);
		std::cout << "GAME UNLOADED --------------------------------" << "\n";
	}


	/*========================================================= FUNCTIONS =========================================================*/


	void playerRotationUpdate()
	{
		dirVector = { pointerPosition.x - playerPosition.x, pointerPosition.y - playerPosition.y };

		angle = atan2f(dirVector.y, dirVector.x);

		angleToDegrees = (angle * (180.0f / PI)) - 90;

		if (angleToDegrees < 0) {
			angleToDegrees += 360.0f;
		}

		player.rotation = angleToDegrees;
	}

	void checkAnimState()
	{

		if (player.rotation < 23 || player.rotation > 338) {
			player.animationState = 1; //bottom
		}
		else if (player.rotation < 338 && player.rotation > 293) {
			player.animationState = 2; //bottom right
		}
		else if (player.rotation < 293 && player.rotation > 248) {
			player.animationState = 3; //right
		}
		else if (player.rotation < 248 && player.rotation > 203) {
			player.animationState = 4; //top right
		}
		else if (player.rotation < 203 && player.rotation > 158) {
			player.animationState = 5; // top
		}
		else if (player.rotation < 158 && player.rotation > 113) {
			player.animationState = 6; //top left
		}
		else if (player.rotation < 113 && player.rotation > 68) {
			player.animationState = 7; //left
		}
		else if (player.rotation < 68 && player.rotation > 23) {
			player.animationState = 8; //bottom left
		}
	}

	Vector2 NormalizeVector(Vector2 v) {
		float length = sqrtf(v.x * v.x + v.y * v.y);
		if (length != 0.0f) {
			v.x /= length;
			v.y /= length;
		}
		return v;
	}

	Projectile::createProjectile* GetInactiveProjectile() {
		for (int i = 0; i < PLAYER_MAX_PROJECTILES; i++) {
			if (!projectile[i].state) {
				return &projectile[i];  // Return pointer to inactive bullet
			}
		}
		return nullptr;  // No inactive bullets available
	}

	void playerBounds()
	{
		if (player.playerRect.x > Globals::Screen.size.x + (player.playerRect.width * 1.5)) {
			player.playerRect.x = static_cast<float>(0 - (player.playerRect.width));
		}
		if (player.playerRect.x < 0 - (player.playerRect.width * 1.5)) {
			player.playerRect.x = static_cast<float>(Globals::Screen.size.x + player.playerRect.width);
		}
		if (player.playerRect.y > Globals::Screen.size.y + (player.playerRect.height * 1.5)) {
			player.playerRect.y = static_cast<float>(0 - (player.playerRect.height));
		}
		if (player.playerRect.y < 0 - (player.playerRect.height * 1.5)) {
			player.playerRect.y = static_cast<float>(Globals::Screen.size.y + player.playerRect.height);
		}
	}

}
