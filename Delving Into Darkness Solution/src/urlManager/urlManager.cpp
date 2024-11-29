# include "urlManager.h"

namespace urlManager
{
	void initUrlButton(urlButton& buttn, Vector2 position, float textSize,const char* path)
	{
		buttn.path = path;
		buttn.urlBounds = { position.x, position.y, static_cast<float>(MeasureText(buttn.path,static_cast<int>(textSize))),static_cast<float>(textSize) };
	}
}