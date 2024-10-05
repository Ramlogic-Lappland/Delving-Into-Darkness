#include "menu.h"

#include <iostream>
#include "raylib.h"

#include "Delving_Into_Darkness.h"

namespace Menu
{
	const int bookAmountFrames = 12;
	Music menuMusic;
	

	Texture2D menuBackground;
	Image image;

	Texture2D bookFrames[bookAmountFrames];

	Texture2D itchLogo;

	int currentFrame = 0;    // current frame
	float frameTime = 0.2f;  // Time for each frame (in seconds)
	float elapsedTime = 0.0f; // elapsed time

	int bookWidth = static_cast<int>(gameManager::Screen.size.x * 0.75);
	int bookHeight = static_cast<int>(gameManager::Screen.size.y * 0.75);
	bool bookAnimationOn = true;

	int correction = 0;

	float timePlayed = 0.0f;

	void initMenu()
	{

			image = LoadImage("res/BookDesk/grayDesk.png");     // Loaded in CPU memory (RAM)
			ImageResize(&image, static_cast<int>(gameManager::Screen.size.x), static_cast<int>(gameManager::Screen.size.y)); // resize image before aplying to texture
			menuBackground = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
			UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

			bookFrames[0] = LoadTexture("res/OpenBook/1.png");
			bookFrames[1] = LoadTexture("res/OpenBook/2.png");
			bookFrames[2] = LoadTexture("res/OpenBook/3.png");
			bookFrames[3] = LoadTexture("res/OpenBook/4.png");
			bookFrames[4] = LoadTexture("res/OpenBook/5.png");
			bookFrames[5] = LoadTexture("res/OpenBook/6.png");
			bookFrames[6] = LoadTexture("res/OpenBook/7.png");
			bookFrames[7] = LoadTexture("res/OpenBook/8.png");
			bookFrames[8] = LoadTexture("res/OpenBook/9.png");
			bookFrames[9] = LoadTexture("res/OpenBook/10.png");
			bookFrames[10] = LoadTexture("res/OpenBook/11.png");
			bookFrames[11] = LoadTexture("res/OpenBook/12.png");  

			image = LoadImage("res/itch_Io_logo.png");     
			ImageResize(&image, 21, 21); 
			itchLogo = LoadTextureFromImage(image);
			UnloadImage(image);

			menuMusic = LoadMusicStream("res/sound/TheVeilofNight.mp3");
			PlayMusicStream(menuMusic);
			SetMusicVolume(menuMusic, 0.5f);
	}

	void updateMenu()
	{
		UpdateMusicStream(menuMusic);

		timePlayed = GetMusicTimePlayed(menuMusic) / GetMusicTimeLength(menuMusic);

		if (timePlayed > 1.0f) timePlayed = 1.0f;

		elapsedTime += GetFrameTime();

		if (bookAnimationOn) {
			// Update elapsed time
			elapsedTime += GetFrameTime();

			// Check if it's time to switch frames
			if (elapsedTime >= frameTime) {
				// Increment frame if we're not at the last frame
				if (currentFrame < bookAmountFrames - 1) {
					currentFrame++;
				}
				else {
					// Stop the animation when the last frame is reached
					bookAnimationOn = false;
				}

				elapsedTime = 0.0f;  // Reset elapsed time
			}
		}


	}

	void drawMenu()
	{

		ClearBackground(DARKGRAY);

		DrawTexture(menuBackground, 0, 0, GRAY);

		if (currentFrame < 5)
		{
			DrawTexture(bookFrames[currentFrame], 180 - (14 * currentFrame), 0, WHITE);
			correction = 14 * currentFrame;
		}
		else 
			if (currentFrame >= 5)
			{
				DrawTexture(bookFrames[currentFrame], 180 - correction, 0, WHITE);
			}
		if (currentFrame > 9)
		{
			DrawTexture(itchLogo, 948, 265, WHITE);
		}

	}

	void unloadMenu()
	{
		system("cls");

		UnloadMusicStream(menuMusic);

		UnloadTexture(menuBackground);
		UnloadTexture(itchLogo);
		
		for (int i = 0; i < bookAmountFrames; i++) {
			UnloadTexture(bookFrames[i]);
		}

		std::cout << "MENU UNLOADED";
	}

}
