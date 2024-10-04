#include "menu.h"

#include <iostream>
#include "raylib.h"

#include "Delving_Into_Darkness.h"

namespace Menu
{

	Texture2D menuBackground;
	Image image;

	void initMenu()
	{

			image = LoadImage("res/BookDesk/grayDesk.png");     // Loaded in CPU memory (RAM)
			ImageResize(&image, static_cast<int>(gameManager::Screen.size.x), static_cast<int>(gameManager::Screen.size.y)); // resize image before aplying to texture
			menuBackground = LoadTextureFromImage(image);          // Image converted to texture, GPU memory (VRAM)
			UnloadImage(image);   // Once image has been converted to texture and uploaded to VRAM, it can be unloaded from RAM

	}

	void updateMenu()
	{

	}

	void drawMenu()
	{

		ClearBackground(DARKGRAY);

		DrawTexture(menuBackground, 0, 0, GRAY);

	}

	void unloadMenu()
	{
		system("cls");
		UnloadTexture(menuBackground);
		std::cout << "MENU UNLOADED";
	}

}