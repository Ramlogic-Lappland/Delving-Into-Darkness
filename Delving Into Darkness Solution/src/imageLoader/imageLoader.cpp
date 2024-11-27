#include "imageLoader.h"

#include "raylib.h"

namespace imageLoader
{
	void initImage(Texture2D& texture, Vector2 size, const char* path)
	{
		Image image;
		image = LoadImage(path);
		ImageResize(&image, static_cast<int> (size.x), static_cast<int>(size.y));
		texture = LoadTextureFromImage(image);
		UnloadImage(image);
	}
}

