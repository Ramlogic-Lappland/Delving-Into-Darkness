#include "urlManager.h"

#include "raylib.h"

#include "collisionManager/collisionManager.h"
#include "Delving_Into_Darkness.h"
#include "menu.h"

namespace urlManager
{
	void initUrlButton(urlButton& buttn, Vector2 position, float textSize,const char* path)
	{
		buttn.path = path;
		buttn.urlBounds = { position.x, position.y, static_cast<float>(MeasureText(buttn.path,static_cast<int>(textSize))),static_cast<float>(textSize) };
	}

	void urlCollision(urlButton& buttn, Texture2D& pointerTex, Vector2& pointerPosition)
	{
	    
		if (collisions::rectangleXrectangle(buttn.urlBounds.x, buttn.urlBounds.y, buttn.urlBounds.width, buttn.urlBounds.height, pointerPosition.x, pointerPosition.y, static_cast<float>(pointerTex.width), static_cast<float>(pointerTex.height)) && gameManager::CurrentScreen == gameManager::credits)
		{
			if (IsMouseButtonPressed(MOUSE_BUTTON_LEFT) && Menu::flag == false)
			{
				OpenURL(buttn.path);
			}
			if (IsMouseButtonReleased(MOUSE_BUTTON_LEFT))
			{
			}
		}
	}
}