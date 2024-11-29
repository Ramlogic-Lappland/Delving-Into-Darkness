#include "Delving_Into_Darkness.h"

#include <iostream>
#include "raylib.h"

#include "ui/menu.h"
#include "game/game.h"
#include "globals.h"

using namespace std;

namespace gameManager
{
    CreateCurrentScreen CurrentScreen;
    bool isRunning = true;

    int run(void)
    {     
        init();

        while (isRunning && !WindowShouldClose())
        {
            gameManager::update();

            gameManager::draw();
        }

        close();

        return 0;
    }

    void init()
    {
        InitAudioDevice();

        Globals:: initGlobals();
        gameManager::CurrentScreen = menu;

        InitWindow(static_cast<int>(Globals::Screen.size.x), static_cast<int>(Globals::Screen.size.y), Globals::Screen.name);

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
            Game::updateGame();
            break;
        case credits:
            Menu::updateMenu();
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
            Game::drawGame();
        }
        if (CurrentScreen == credits)
        {
            Menu::drawMenu();
        }
        EndDrawing();
    }

    void stop()
    {
        isRunning = false;
    }


    void close()
    {
        Menu::unloadMenu();
        Game::unloadGame();
        CloseWindow();
    }


}