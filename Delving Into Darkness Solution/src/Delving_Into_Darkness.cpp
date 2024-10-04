#include "Delving_Into_Darkness.h"

#include "raylib.h"
#include <iostream>

#include "menu/menu.h"

using namespace std;


namespace gameManager
{
    CreateScreen Screen;
    CreateCurrentScreen CurrentScreen;


int run(void)
{
    init();

    SetTargetFPS(60);

    while (!WindowShouldClose())
    {
        update();

        draw();
    }

    close();

    return 0;
}

void init()
{
    Screen.size = {1000, 800};
    Screen.name = "Delving Into Darkness";
    gameManager::CurrentScreen  = menu;

    initMenu();

    InitWindow(static_cast<int>(Screen.size.x), static_cast<int>(Screen.size.y), Screen.name);

}

void update()
{
    switch (CurrentScreen)
    {
    case menu:
        updateMenu();
        break;
    case game:
       // updateGame();
        break;
    case credits:
       // updateCredits();
        break;
    default:
        break;
    }
}

void draw()
{
    BeginDrawing();
    ClearBackground(BLACK);

    if (CurrentScreen == menu)
    {
        drawMenu();
    }
    if (CurrentScreen == game)
    {
       // drawGame();
    }
    if (CurrentScreen == credits)
    {
       // drawCredits();
    }
    EndDrawing();
}

void close()
{
    CloseWindow();
}

}