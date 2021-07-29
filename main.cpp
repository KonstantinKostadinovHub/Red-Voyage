#include "World.h"
#include "TitleScreen.h"
#include "Cave.h"

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif // _WIN32_WINNT

#include <windows.h>

World world;
TitleScreen screen;
Cave cave;

int main(int argc, char* argv[])
{
    //ShowWindow(GetConsoleWindow(), SW_HIDE);

    world.init();
    
	world.m_gameState = GAME; // TITLESCREEN

    screen.load("NiTe_logo.txt", world.m_main_renderer);

    while(!world.m_endGame)
    {
#pragma region TITLESCREEN_LOOP
        if (world.m_gameState == TITLESCREEN)
        {
            while (!world.m_quitScene)
            {
                world.input();
                screen.update();
                screen.draw(world.m_main_renderer);
            }
            world.m_quitScene = false;
        }
#pragma endregion

#pragma region MENU_LOOP
        if(world.m_gameState == MENU)
        {
            while(!world.m_quitScene)
            {
                world.input();
                world.m_menu.update();
                world.m_menu.draw();
                SDL_Delay(25);
            }
            world.m_quitScene = false;
        }
#pragma endregion

#pragma region GAME_LOOP
        if(world.m_gameState == GAME)
        {
            world.m_gameManager.initSession();
            
            while(!world.m_quitScene)
            {
                world.input();
                world.m_gameManager.update();
                world.m_gameManager.draw();
                SDL_Delay(25);
            }
            world.m_gameManager.deleteSession();
            world.m_quitScene = false;
        }
#pragma endregion

#pragma region CAVES_LOOP
        if (world.m_gameState == CAVES)
        {
            SDL_ShowCursor(SDL_ENABLE);

            world.m_gameManager.m_cave.initSession();
            while (!world.m_quitScene)
            {
                world.input();
                world.m_gameManager.m_cave.update();
                world.m_gameManager.m_cave.draw();
                SDL_Delay(25);
            }
            world.m_gameManager.m_cave.deleteSession();
            world.m_quitScene = false;

        }
#pragma endregion

#pragma region CREDITS_LOOP
        if(world.m_gameState == CREDITS)
        {
            SDL_ShowCursor(SDL_ENABLE);

            world.credits.init("credits.txt");
            while(!world.m_quitScene)
            {
                world.input();
                world.credits.draw();
                world.credits.update();
                SDL_Delay(25);
            }
            world.m_quitScene = false;
        }
#pragma endregion

        if(world.m_gameState == EXIT)
        {
            world.m_endGame = true;
        }

        if(world.m_gameState == ENDGAME)
        {
            SDL_ShowCursor(SDL_ENABLE);

            world.endgame.init("endgame.txt");
            while(!world.m_quitScene)
            {
                world.input();
                world.endgame.draw();
                world.endgame.update();

                SDL_Delay(25);
            }
            world.m_quitScene = false;
        }
    }
    world.destroy();

    return 0;
}
