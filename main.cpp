#include "World.h"

#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0500
#endif // _WIN32_WINNT

#include <windows.h>

World world;

int main(int argc, char* argv[])
{
    //ShowWindow(GetConsoleWindow(), SW_HIDE);

	cout << __LINE__ << endl;

    world.init();
    
	cout << __LINE__ << endl;
	world.m_gameState = MENU;
    world.loadTitleScreen();

	cout << __LINE__ << endl;

	cout << "here \n";

    while(!world.m_endGame)
    {
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
        if(world.m_gameState == CREDITS)
        {
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
