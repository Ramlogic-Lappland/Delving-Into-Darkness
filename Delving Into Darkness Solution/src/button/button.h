#pragma once

#include "raylib.h"

namespace button
{
	struct createButton
	{
		Vector2 position;

		int amountOfFrames;
		int buttonFrame;

		float width;
		float height;

		bool state;

		Texture2D* buttonText;
	};

	void assignWidthAndHeight(createButton& btn);

	void initBttn(createButton& bttn, Vector2 position, Vector2 resize, const char* path, const char* path2, int amountOfFrames);
}
