#pragma once
#include "raylib.h"


namespace gameManager
{
	int run(void);

	void init();

	void update();

	void draw();

	void stop();

	void close();

	struct CreateScreen 
	{
		const char* name;
		Vector2 size;
	};

	enum CreateCurrentScreen
	{
		menu,
		game,
		credits,
	};

	extern CreateScreen Screen;
	extern CreateCurrentScreen CurrentScreen;
}