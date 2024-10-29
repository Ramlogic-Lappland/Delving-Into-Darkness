#include "Delving_Into_Darkness.h"

#include <iostream>
#include "raylib.h"

#include "menu/menu.h"
#include "game/game.h"
#include "globals.h"
using namespace std;


namespace gameManager
{
    //CreateScreen Screen;
    CreateCurrentScreen CurrentScreen;
    bool isRunning = true;

    int run(void)
    {     
        init();

        SetTargetFPS(60);

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

        //HideCursor();

        Menu::initMenu();
        //Game::initGame();

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

    void close()
    {
        Menu::unloadMenu();
        Game::unloadGame();
        CloseWindow();
    }

    void stop()
    {
        isRunning = false;
    }

}