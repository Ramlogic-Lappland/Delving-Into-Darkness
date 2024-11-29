#pragma once

#include "raylib.h"

namespace urlManager
{
	struct urlButton
	{
		const char* path;
		Rectangle urlBounds;
	};

	void initUrlButton(urlButton& buttn, Vector2 position, float textSize, const char* path);
	void urlCollision(urlButton& buttn, Texture2D& pointerTex, Vector2& pointerPosition);
}