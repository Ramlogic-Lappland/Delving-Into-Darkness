#include "menu.h"

#include <iostream>
#include "raylib.h"

#include "Delving_Into_Darkness.h"

namespace Menu
{
	const int candleAmountFrames = 4;
	const int bookAmountFrames = 12;

	Music menuMusic;
	Sound bookOpen;

	Texture2D menuBackground;
	Image image;

	Texture2D bookFrames[bookAmountFrames];
	Texture2D candleFrames[candleAmountFrames];

	Texture2D itchLogo;

	int candleCurrentFrame = 0;
	float candleFrameTime = 0.5f;
	float candleElapsedTime = 0.0f;

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

			//book opens
			bookFrames[0] = LoadTexture("res/OpenBook/1.png");
			bookFrames[1] = LoadTexture("res/OpenBook/2.png");
			bookFrames[2] = LoadTexture("res/OpenBook/3.png");
			bookFrames[3] = LoadTexture("res/OpenBook/4.png");
			bookFrames[4] = LoadTexture("res/OpenBook/5.png");
			//markers open from here on
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

			candleFrames[0] = LoadTexture("res/candle/can5.png");
			candleFrames[1] = LoadTexture("res/candle/can6.png");
			candleFrames[2] = LoadTexture("res/candle/can7.png");
			candleFrames[3] = LoadTexture("res/candle/can8.png");

			menuMusic = LoadMusicStream("res/sounds/TheVeilofNight.mp3");
			bookOpen = LoadSound("res/sounds/bookpage.wav");

			PlayMusicStream(menuMusic);
			SetMusicVolume(menuMusic, 0.5f);
			SetSoundVolume(bookOpen, 0.1f);
	}

	void updateMenu()
	{
		UpdateMusicStream(menuMusic);

		timePlayed = GetMusicTimePlayed(menuMusic) / GetMusicTimeLength(menuMusic);

		if (timePlayed > 1.0f) timePlayed = 1.0f;

		elapsedTime += GetFrameTime();
		candleElapsedTime += GetFrameTime();

		if (currentFrame == 0)
		{
			PlaySound(bookOpen);
		}


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

		if (candleElapsedTime >= candleFrameTime) {
			candleCurrentFrame = (candleCurrentFrame + 1) % candleAmountFrames; // Cycle to the next frame
			candleElapsedTime = 0.0f; // Reset elapsed time
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

		DrawTexture(candleFrames[candleCurrentFrame], 40, 30, WHITE);

	}

	void unloadMenu()
	{
		system("cls");

		CloseAudioDevice();
		UnloadMusicStream(menuMusic);
		UnloadSound(bookOpen);

		UnloadTexture(menuBackground);
		UnloadTexture(itchLogo);
		
		for (int i = 0; i < bookAmountFrames; i++) {
			UnloadTexture(bookFrames[i]);
		}

		for (int i = 0; i < candleAmountFrames; i++) {
			UnloadTexture(candleFrames[i]);
		}

		std::cout << "MENU UNLOADED --------------------------------------------------" << "\n";
	}

}
