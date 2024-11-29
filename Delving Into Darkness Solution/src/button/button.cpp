#include "button.h"

namespace button
{
	void assignWidthAndHeight(createButton& btn)
	{
		btn.width = static_cast<float>(btn.buttonText->width);
		btn.height = static_cast<float>(btn.buttonText->height);
	}

	void initBttn(createButton& bttn, Vector2 position, Vector2 resize, const char* path, const char* path2, int amountOfFrames) //amount of frames - position - path - resize
	{

		if (amountOfFrames < 2)
		{
			TraceLog(LOG_WARNING, "initBttn: amountOfFrames must be at least 2");
			return; 
		}

		bttn.amountOfFrames = amountOfFrames;
		bttn.buttonFrame = 0;
		bttn.position = { position.x, position.y };
		bttn.buttonText = new Texture2D[bttn.amountOfFrames];

		Image image;

		image = LoadImage(path);
		ImageResize(&image,static_cast<int>(resize.x), static_cast<int>(resize.y));
		bttn.buttonText[0] = LoadTextureFromImage(image);
		UnloadImage(image);

		image = LoadImage(path2);
		ImageResize(&image, static_cast<int>(resize.x), static_cast<int>(resize.y));
		bttn.buttonText[1] = LoadTextureFromImage(image);
		UnloadImage(image);

		bttn.width = static_cast<float>(bttn.buttonText->width);
		bttn.height = static_cast<float>(bttn.buttonText->height);
	}
}
