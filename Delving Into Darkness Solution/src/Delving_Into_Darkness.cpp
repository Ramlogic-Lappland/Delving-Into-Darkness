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
        InitAudioDevice();

        init();

        SetTargetFPS(60);

        while (!WindowShouldClose())
        {
            gameManager::update();

            gameManager::draw();
        }

        gameManager::close();

        return 0;
    }

    void init()
    {
        Screen.size = { 1200, 850 };
        Screen.name = "Delving Into Darkness";
        gameManager::CurrentScreen = menu;

        InitWindow(static_cast<int>(Screen.size.x), static_cast<int>(Screen.size.y), Screen.name);

        HideCursor();

        Menu::initMenu();

    }

    void update()
    {
        switch (CurrentScreen)
        {
        case menu:
            Menu::updateMenu();
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
            Menu::drawMenu();
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
        Menu::unloadMenu();
        CloseWindow();
    }

}