#include "menu.h"

#include <iostream>
#include <cstdlib>

#include "raylib.h"

#include "globals.h"
#include "collisionManager/collisionManager.h"
#include "Delving_Into_Darkness.h"
#include "ui/button.h"
#include "ui/urlManager.h"
#include "game/game.h"


namespace Menu
{

	void openBookAnim();
	void swapMenuPage();
	void OpenURL(const char* url);


	button::createButton playBttn;
	button::createButton creditsBttn;
	button::createButton returnBttn;
	button::createButton exitBttn;

	urlManager::urlButton creatorItchLink;
	urlManager::urlButton raylibLink;
	urlManager::urlButton menuSongLink;
	urlManager::urlButton gameSongLink;
	urlManager::urlButton soundsLink;
	urlManager::urlButton characterLink; 
	urlManager::urlButton fireballLink;
	urlManager::urlButton humblepixelLink;

	const int candleAmountFrames = 4;
	const int bookAmountFrames = 19;
	const int pointerOffSet = 10;
	const int bookOpenFrames = 12;
	const int bookSwapPageFrames = 7;
	const char* linkURL = "https://itch.io/c/4957050/delving";

	Music menuMusic;
	Sound bookOpen;
	Sound flipPage;
	Sound buttonBop;

	Image image;

	Texture2D menuBackground;
	Texture2D bookFrames[bookAmountFrames];
	Texture2D candleFrames[candleAmountFrames];
	Texture2D itchLogo;
	Texture2D pointerTex;

	Vector2 pointerPosition = {0.0f, 0.0f};
	Vector2 itchIoPos = {948, 265};

	int candleCurrentFrame = 0;
	int currentFrame = 0;    // current frame
	int bookWidth = static_cast<int>(Globals::Screen.size.x * 0.75);
	int bookHeight = static_cast<int>(Globals::Screen.size.y * 0.75);
	int correction = 0;

	float candleFrameTime = 0.5f;
	float candleElapsedTime = 0.0f;
	float frameTime = 0.2f;  // Time for each frame (in seconds)
	float elapsedTime = 0.0f; // elapsed time

    float timePlayed = 0.0f;

	bool bookOpenAnimationOn = true;
	bool bookSwapRight = false;
	bool bookSwapLeft = false;

	void initMenu()  // START INIT ======================================================================================================================================================
	{
		initBttn(playBttn,    { 330, 240 }, { 200, 44 }, "res/ui/button/play_button_1.png", "res/ui/button/play_button_2.png", 2); // Return to menu button (amount of frames - position - path img1 - path img2 - resize)

		initBttn(creditsBttn, { 330, 340 }, { 200, 44 }, "res/ui/button/credits_button_1.png", "res/ui/button/credits_button_2.png", 2);

		initBttn(exitBttn,    { 330, 440 }, { 200, 44 }, "res/ui/button/exit_button_1.png", "res/ui/button/exit_button_2.png", 2);

		initBttn(returnBttn,  { 750, 550 }, { 160, 38 }, "res/ui/button/return_button_1.png", "res/ui/button/return_button_2.png", 2);


		image = LoadImage("res/BookDesk/grayDesk.png");    
		ImageResize(&image, static_cast<int>(Globals::Screen.size.x), static_cast<int>(Globals::Screen.size.y)); // resize image before aplying to texture
		menuBackground = LoadTextureFromImage(image);       
		UnloadImage(image);   

		//Book opens
		bookFrames[0] = LoadTexture("res/OpenBook/1.png");
		bookFrames[1] = LoadTexture("res/OpenBook/2.png");
		bookFrames[2] = LoadTexture("res/OpenBook/3.png");
		bookFrames[3] = LoadTexture("res/OpenBook/4.png");
		bookFrames[4] = LoadTexture("res/OpenBook/5.png");
		//Markers open from here on
		bookFrames[5] = LoadTexture("res/OpenBook/6.png");
		bookFrames[6] = LoadTexture("res/OpenBook/7.png");
		bookFrames[7] = LoadTexture("res/OpenBook/8.png");
		bookFrames[8] = LoadTexture("res/OpenBook/9.png");
		bookFrames[9] = LoadTexture("res/OpenBook/10.png");
		bookFrames[10] = LoadTexture("res/OpenBook/11.png");
		bookFrames[11] = LoadTexture("res/OpenBook/12.png");
		//Page swap
		bookFrames[12] = LoadTexture("res/OpenBook/13.png");
		bookFrames[13] = LoadTexture("res/OpenBook/14.png");
		bookFrames[14] = LoadTexture("res/OpenBook/15.png");
		bookFrames[15] = LoadTexture("res/OpenBook/16.png");
		bookFrames[16] = LoadTexture("res/OpenBook/17.png");
		bookFrames[17] = LoadTexture("res/OpenBook/18.png");
		bookFrames[18] = LoadTexture("res/OpenBook/19.png");
		//ItchIO Logo 
		itchLogo = LoadTexture("res/miscellaneous/itch_Io_logo.png");
		//Candle Anim
		candleFrames[0] = LoadTexture("res/candle/can5.png");
		candleFrames[1] = LoadTexture("res/candle/can6.png");
		candleFrames[2] = LoadTexture("res/candle/can7.png");
		candleFrames[3] = LoadTexture("res/candle/can8.png");
		//MousePointer
		pointerTex = LoadTexture("res/miscellaneous/feather.png");

		//Audio
		menuMusic = LoadMusicStream("res/sounds/TheVeilofNight.mp3");
		bookOpen = LoadSound("res/sounds/openBook.wav");
		flipPage = LoadSound("res/sounds/pageFlip.wav");
		buttonBop = LoadSound("res/sounds/buttonpop.wav");

		urlManager::initUrlButton(creatorItchLink, { 280, 265 }, 13, "https://ramlogic.itch.io");
		urlManager::initUrlButton(raylibLink, { 280, 300 }, 13, "https://www.raylib.com");  
		urlManager::initUrlButton(menuSongLink, { 280, 340 }, 13, "https://crowshade.itch.io/horror-music-pack");  
		urlManager::initUrlButton(gameSongLink, { 280, 380 }, 13, "https://suno.com"); 
		urlManager::initUrlButton(soundsLink, { 280, 420 }, 13, "https://artlist.io/sfx"); 
		urlManager::initUrlButton(characterLink, { 630, 270 }, 13, "https://pixivan.itch.io");
		urlManager::initUrlButton(fireballLink, { 630, 310 }, 13, "https://stealthix.itch.io/animated-fires");
		urlManager::initUrlButton(humblepixelLink, { 630, 410 }, 13, "https://itch.io/queue/c/4957050/delving");
		
		//Init AudioFiles
		PlayMusicStream(menuMusic);
		SetMusicVolume(menuMusic, 0.5f);
		SetSoundVolume(bookOpen, 0.1f);
		SetSoundVolume(flipPage, 0.3f);
		SetSoundVolume(buttonBop, 0.2f);

	} //END INIT ======================================================================================================================================================



	void updateMenu() // START UPDATE ======================================================================================================================================================
	{
		pointerPosition = GetMousePosition();

		UpdateMusicStream(menuMusic);

		timePlayed = GetMusicTimePlayed(menuMusic) / GetMusicTimeLength(menuMusic);

		if (timePlayed > 1.0f) timePlayed = 1.0f;

		elapsedTime += GetFrameTime();
		candleElapsedTime += GetFrameTime();

		if (currentFrame == 0)
		{
			PlaySound(bookOpen);
		}

		openBookAnim();

		if (collisions::rectangleXrectangle(playBttn.position.x, playBttn.position.y, playBttn.width, playBttn.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)) && gameManager::CurrentScreen == gameManager::menu)
		{
			playBttn.buttonFrame = 1;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) 
			{
				PlaySound(buttonBop);
				gameManager::CurrentScreen = gameManager::game;
				if (Game::gameInit == false)
				{
					Game::initGame();
				}
				else
				{
					Game::resetGame();
				}
			}
		}else 
		{
			playBttn.buttonFrame = 0;
		}

		if (collisions::rectangleXrectangle(creditsBttn.position.x, creditsBttn.position.y, creditsBttn.width, creditsBttn.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)) && gameManager::CurrentScreen == gameManager::menu)
		{
			creditsBttn.buttonFrame = 1;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				if (!bookSwapRight && currentFrame == bookOpenFrames - 1)
				{
					PlaySound(buttonBop);
					bookSwapRight = true;
					PlaySound(flipPage);
					gameManager::CurrentScreen = gameManager::credits;
				}
			}
		}else
		{
			creditsBttn.buttonFrame = 0;
		}

		if (collisions::rectangleXrectangle(exitBttn.position.x, exitBttn.position.y, exitBttn.width, exitBttn.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)) && gameManager::CurrentScreen == gameManager::menu)
		{
			exitBttn.buttonFrame = 1;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				PlaySound(buttonBop);
				gameManager::stop();
			}
		}else
		{
			exitBttn.buttonFrame = 0;
		}

		if (collisions::rectangleXrectangle(returnBttn.position.x, returnBttn.position.y, returnBttn.width, returnBttn.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)) && gameManager::CurrentScreen == gameManager::credits)
		{
			returnBttn.buttonFrame = 1;
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				if (!bookSwapLeft && currentFrame == (bookOpenFrames + bookSwapPageFrames - 1))
				{
					PlaySound(buttonBop);
					bookSwapLeft = true;
					PlaySound(flipPage);
					gameManager::CurrentScreen = gameManager::menu; // CHANGE MENU DRAW STATE FROM CREDITS TO MENU 
				}
			}
		}else
		{
			returnBttn.buttonFrame = 0;
		}
		
		urlManager::urlCollision(creatorItchLink, pointerTex, pointerPosition);

		urlManager::urlCollision(raylibLink, pointerTex, pointerPosition);

		urlManager::urlCollision(menuSongLink, pointerTex, pointerPosition);

		urlManager::urlCollision(soundsLink, pointerTex, pointerPosition);

		urlManager::urlCollision(fireballLink, pointerTex, pointerPosition);

		urlManager::urlCollision(humblepixelLink, pointerTex, pointerPosition);


		if (collisions::rectangleXrectangle(itchIoPos.x, itchIoPos.y, static_cast<float>(itchLogo.width), static_cast<float>(itchLogo.height), pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)))
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT))
			{
				OpenURL(linkURL);
			}
		}
		

		if (candleElapsedTime >= candleFrameTime) 
		{
			candleCurrentFrame = (candleCurrentFrame + 1) % candleAmountFrames; // Cycle to the next frame
			candleElapsedTime = 0.0f; // Reset elapsed time
		}
		
		swapMenuPage(); 

	} // END UPDATE ======================================================================================================================================================




	void drawMenu() // START DRAW ======================================================================================================================================================
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
		{ // LOGO LOAD
			DrawTexture(itchLogo, 948, 265, WHITE); 
		}

		if (gameManager::CurrentScreen == gameManager::menu && currentFrame > 8 && currentFrame < 13) // MENU STATE AND NO ANIMATION 
		{
			DrawTexture(playBttn.buttonText[playBttn.buttonFrame], static_cast<int>(playBttn.position.x), static_cast<int>(playBttn.position.y), WHITE);
			DrawTexture(creditsBttn.buttonText[creditsBttn.buttonFrame], static_cast<int>(creditsBttn.position.x), static_cast<int>(creditsBttn.position.y), WHITE); 
			DrawTexture(exitBttn.buttonText[exitBttn.buttonFrame], static_cast<int>(exitBttn.position.x), static_cast<int>(exitBttn.position.y), WHITE);

			DrawText("CONTROLS: ", 630, 250, 20, BLACK);
			DrawText("Movement: ", 630, 275, 18, BLACK);
			DrawText("You accelerate in the direction your ", 630, 300, 16, BLACK);
			DrawText("pointer is, by holding right click.", 630, 320, 16, BLACK);
			DrawText("Shooting: ", 630, 350, 18, BLACK);
			DrawText("You shoot in the direction your", 630, 370, 16, BLACK);
			DrawText("pointer is, by clicking left click.", 630, 390, 16, BLACK);
			DrawText("Health: ", 630, 420, 18, BLACK);
			DrawText("if you hit a slime you lose hp", 630, 440, 16, BLACK);
			DrawText("the bigger the slime the more u lose.", 630, 460, 16, BLACK);
			DrawText("Points: ", 630, 500, 18, BLACK);
			DrawText("the smaller the slime", 630, 520, 16, BLACK);
			DrawText("the more points it gives.", 630, 540, 16, BLACK);
			DrawText("During game press P to pause.", 630, 570, 16, BLACK);
		}

		if (gameManager::CurrentScreen == gameManager::credits && currentFrame > 16 ) // MENU STATE AND NO ANIMATION 
		{
			DrawTexture(returnBttn.buttonText[returnBttn.buttonFrame], static_cast<int>(returnBttn.position.x), static_cast<int>(returnBttn.position.y), WHITE);

			DrawText("Made By: Estanislao Sala Barraquero", 280, 250, 14, BLACK);
			DrawText(creatorItchLink.path, static_cast<int>(creatorItchLink.urlBounds.x), static_cast<int>(creatorItchLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(creatorItchLink.urlBounds.x), static_cast<int>(creatorItchLink.urlBounds.y + 13),
				     static_cast<int>(creatorItchLink.urlBounds.x + creatorItchLink.urlBounds.width), static_cast<int>(creatorItchLink.urlBounds.y + 13), BLUE);

			DrawText("Made using: Raylib", 280, 285, 14, BLACK); 
			DrawText(raylibLink.path, static_cast<int>(raylibLink.urlBounds.x), static_cast<int>(raylibLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(raylibLink.urlBounds.x), static_cast<int>(raylibLink.urlBounds.y + 13),
				     static_cast<int>(raylibLink.urlBounds.x + raylibLink.urlBounds.width), static_cast<int>(raylibLink.urlBounds.y + 13), BLUE);

			DrawText("Menu song by: Crow Shade ", 280, 320, 14, BLACK); 
			DrawText(menuSongLink.path, static_cast<int>(menuSongLink.urlBounds.x), static_cast<int>(menuSongLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(menuSongLink.urlBounds.x), static_cast<int>(menuSongLink.urlBounds.y + 13),
				static_cast<int>(menuSongLink.urlBounds.x + menuSongLink.urlBounds.width), static_cast<int>(menuSongLink.urlBounds.y + 13), BLUE);

			DrawText("Game song made with suno (ai)", 280, 360, 14, BLACK);
			DrawText(gameSongLink.path, static_cast<int>(gameSongLink.urlBounds.x), static_cast<int>(gameSongLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(gameSongLink.urlBounds.x), static_cast<int>(gameSongLink.urlBounds.y + 13),
				     static_cast<int>(gameSongLink.urlBounds.x + gameSongLink.urlBounds.width), static_cast<int>(gameSongLink.urlBounds.y + 13), BLUE);
			
			DrawText("sounds made with artlist (ai)", 280, 400, 14, BLACK);
			DrawText(soundsLink.path, static_cast<int>(soundsLink.urlBounds.x), static_cast<int>(soundsLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(soundsLink.urlBounds.x), static_cast<int>(soundsLink.urlBounds.y + 13),
				     static_cast<int>(soundsLink.urlBounds.x + soundsLink.urlBounds.width), static_cast<int>(soundsLink.urlBounds.y + 13), BLUE);
			
			DrawText("Character made by PixiVan", 630, 250, 14, BLACK); 
			DrawText(characterLink.path, static_cast<int>(characterLink.urlBounds.x), static_cast<int>(characterLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(characterLink.urlBounds.x), static_cast<int>(characterLink.urlBounds.y + 13),
				     static_cast<int>(characterLink.urlBounds.x + characterLink.urlBounds.width), static_cast<int>(characterLink.urlBounds.y + 13), BLUE);

			DrawText("Fireball made by Stealthix", 630, 290, 14, BLACK);
			DrawText(fireballLink.path, static_cast<int>(fireballLink.urlBounds.x), static_cast<int>(fireballLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(fireballLink.urlBounds.x), static_cast<int>(fireballLink.urlBounds.y + 13),
				     static_cast<int>(fireballLink.urlBounds.x + fireballLink.urlBounds.width), static_cast<int>(fireballLink.urlBounds.y + 13), BLUE);

			DrawText("Book made by humblepixel", 630, 330, 14, BLACK);
			DrawText("Menu background by humblepixel", 630, 350, 14, BLACK);
			DrawText("Defeat menu background by humblepixel", 630, 370, 14, BLACK);
			DrawText("Pause menu background humblepixel", 630, 390, 14, BLACK);
			DrawText(humblepixelLink.path, static_cast<int>(humblepixelLink.urlBounds.x), static_cast<int>(humblepixelLink.urlBounds.y), 14, BLUE);
			DrawLine(static_cast<int>(humblepixelLink.urlBounds.x), static_cast<int>(humblepixelLink.urlBounds.y + 13),
				     static_cast<int>(humblepixelLink.urlBounds.x + humblepixelLink.urlBounds.width), static_cast<int>(humblepixelLink.urlBounds.y + 13), BLUE);

			DrawText("Slime: missing", 630, 430, 14, BLACK);
			
			DrawText("FOR LINKS CLICK ON ITCH.IO LOGO", 630, 480, 14, BLACK);
		}


		DrawTexture(candleFrames[candleCurrentFrame], 40, 30, WHITE);

		DrawTexture(pointerTex, static_cast<int>(pointerPosition.x) - pointerOffSet, static_cast<int>(pointerPosition.y) - pointerOffSet, WHITE);

		DrawText(TextFormat("Version : %f", Globals::gameVersion), 40, static_cast<int> (Globals::Screen.size.y - 28), 24, WHITE);
		

	} // END DRAW ======================================================================================================================================================




	void unloadMenu() // START UNLOAD ======================================================================================================================================================
	{
		system("cls");
		std::cout << "MENU UNLOAD START --------------------------------------------------" << "\n";

		CloseAudioDevice();
		UnloadMusicStream(menuMusic);
		UnloadSound(bookOpen);
		UnloadSound(flipPage);
		UnloadSound(buttonBop);

		UnloadTexture(menuBackground);
		UnloadTexture(itchLogo);
		UnloadTexture(pointerTex);
		
		for (int i = 0; i < playBttn.amountOfFrames; i++)
		{
			UnloadTexture(playBttn.buttonText[i]);
		}
		delete[] playBttn.buttonText;

		for (int i = 0; i < exitBttn.amountOfFrames; i++)
		{
			UnloadTexture(exitBttn.buttonText[i]);
		}
		delete[] exitBttn.buttonText;

		for (int i = 0; i < creditsBttn.amountOfFrames; i++)
		{
			UnloadTexture(creditsBttn.buttonText[i]);
		}
		delete[] creditsBttn.buttonText;

		for (int i = 0; i < returnBttn.amountOfFrames; i++)
		{
			UnloadTexture(returnBttn.buttonText[i]);
		}
		delete[] returnBttn.buttonText;

		for (int i = 0; i < bookAmountFrames; i++) 
		{
			UnloadTexture(bookFrames[i]);
		}

		for (int i = 0; i < candleAmountFrames; i++)
		{
			UnloadTexture(candleFrames[i]);
		}

		std::cout << "MENU UNLOADED --------------------------------------------------" << "\n";

	} // START UNLOAD ======================================================================================================================================================





	void openBookAnim()  // BOOK OPEN ANIM ======================================================================================================================================================
	{
		if (bookOpenAnimationOn) 
		{
			// Update elapsed time
			elapsedTime += GetFrameTime();

			// Check if it's time to switch frames
			if (elapsedTime >= frameTime) 
			{
				// Increment frame if we're not at the last frame
				if (currentFrame < bookOpenFrames - 1) 
				{
					currentFrame++;
				}
				else {
					// Stop the animation when the last frame is reached
					bookOpenAnimationOn = false;
				}

				elapsedTime = 0.0f;  // Reset elapsed time
			}
		}
    }

	void swapMenuPage() //SWAP MENU PAGE ======================================================================================================================================================
	{
		if (!bookOpenAnimationOn) 
		{
			// SWAP MENU STAGE =====================================================================
			if (!bookSwapRight && currentFrame == bookOpenFrames - 1)
			{ 
				// SWAP RIGHT ==================================================================
				if (IsKeyPressed(KEY_RIGHT))
				{
					bookSwapRight = true;
					PlaySound(flipPage);
					gameManager::CurrentScreen = gameManager::credits; // CHANGE MENU DRAW STATE FROM MENU TO CREDITS
				}
			}
			if (bookSwapRight)
			{
				elapsedTime += GetFrameTime();

				if (elapsedTime >= frameTime) 
				{

					if (currentFrame < bookOpenFrames + bookSwapPageFrames - 1) 
					{
						currentFrame++;
					}
					else 
					{
						bookSwapRight = false;
					}

					elapsedTime = 0.0f;
				}
			} // END SWAP RIGHT ==================================================================

			if (!bookSwapLeft && currentFrame == (bookOpenFrames + bookSwapPageFrames - 1))
			{
				// SWAP LEFT ==================================================================
				if (IsKeyPressed(KEY_LEFT)) 
				{
					bookSwapLeft = true;
					PlaySound(flipPage);
					gameManager::CurrentScreen = gameManager::menu; // CHANGE MENU DRAW STATE FROM CREDITS TO MENU ==================================================================
				}
			}
			if (bookSwapLeft) 
			{
				elapsedTime += GetFrameTime();

				if (elapsedTime >= frameTime) 
				{

					if (currentFrame > bookOpenFrames - 1) 
					{
						currentFrame--;
					}
					else
					{
						bookSwapLeft = false;
					}

					elapsedTime = 0.0f;
				}
			}//  END SWAP LEFT ==================================================================


		} // END SWAPPING MENU STAGE
	}



	void OpenURL(const char* url) {
#if defined(_WIN32)
		system((std::string("start ") + url).c_str());
#endif
	}

}// END NAMESPACE