#include "game.h"

#include "raylib.h"
#include <iostream>
#include <math.h>

#include "Delving_Into_Darkness.h"
#include "globals.h"

namespace Game
{
	CreatePlayer player;

	Vector2 pointerPosition = { 0.0f, 0.0f };
	Vector2 playerPosition;
	Vector2 dirVector;

	float rotationSpeed = 100.0f;
	float angle;
	float angleToDegrees;

	void initGame()
	{
		player.playerTexture = LoadTexture("res/character/test.png");
		player.playerRect = { Globals::Screen.size.x /2, Globals::Screen.size.y / 2, 45, 45};
		player.playerTextureCordenate = { 0, 0, 45, 45 };
		player.pivot = { static_cast<float>(player.playerTexture.width/2), static_cast<float>(player.playerTexture.height/2) };
		player.rotation = 0;
		player.animationState = 1;
	}

	void updateGame()
	{
		pointerPosition = GetMousePosition();
		playerPosition = { player.playerRect.x, player.playerRect.y };
		playerRotationUpdate();

		if (player.rotation < 23 && player.rotation > -22) {
			player.animationState = 1; //bottom
		}else if (player.rotation < -22 && player.rotation > -67) {
			player.animationState = 2; //bottom right
		}else if (player.rotation < -67 && player.rotation > -112) {
			player.animationState = 3; //right
		}else if (player.rotation < -112 && player.rotation > -157) {
			player.animationState = 4; //top right
		}else if (player.rotation < -157 && player.rotation > -202) {
			player.animationState = 5; // top
		}else if (player.rotation < -202 && player.rotation > -248) {
			player.animationState = 6; //top left
		}else if (player.rotation < -248 || player.rotation > 68) {
			player.animationState = 7; //left
		}else if (player.rotation < 68 && player.rotation > 23) {
			player.animationState = 8; //bottom left
		}

	}

	void drawGame()
	{
		DrawText(TextFormat("Angle in radians: %.2f", angle), 10, 10, 20, WHITE);
		DrawText(TextFormat("Angle in degrees: %.2f", angleToDegrees), 10, 40, 20, WHITE);
		DrawText(TextFormat("animation state: %i", player.animationState), 10, 80, 20, WHITE);
		DrawTexturePro(player.playerTexture, player.playerTextureCordenate, player.playerRect, player.pivot, player.rotation, WHITE);
	}

	void unloadGame()
	{
		std::cout << "UNLOADING GAME --------------------------------" << "\n";
		UnloadTexture(player.playerTexture);
		std::cout << "GAME UNLOADED --------------------------------" << "\n";
	}

	void playerRotationUpdate()
	{
		dirVector = { pointerPosition.x - playerPosition.x, pointerPosition.y - playerPosition.y };

		angle = atan2f(dirVector.y, dirVector.x);

		angleToDegrees = (angle * (180.0f / PI)) - 90.0f;


		player.rotation = angleToDegrees;
	}

}
