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
    
	world.m_gameState = MENU; // TITLESCREEN

    screen.load("NiTe_logo.txt", world.m_main_renderer);

    while(!world.m_endGame)
    {
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
        if(world.m_gameState == GAME)
        {
            world.initSession();
            world.m_camera.init(&(world.m_players[0]->m_objRect), &(world.m_players[1]->m_objRect));

            while(!world.m_quitScene)
            {
                world.input();
                world.update();
                world.draw();
                SDL_Delay(25);
            }
            world.deleteSession();
            world.m_quitScene = false;
        }
        if (world.m_gameState == CAVES)
        {

            while (!world.m_quitScene)
            {
                world.input();
                cave.update();
                cave.draw();
                SDL_Delay(25);

            }
            world.m_quitScene = false;

        }
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
