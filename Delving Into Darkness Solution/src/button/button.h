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
}
