#ifndef WORLD_H
#define WORLD_H

#include "GameManager.h"
#include "IconManager.h"
#include "InputManager.h"

using namespace std;

/*	\brief Responsible for handling the game
	
	Generating the main window and renderer.
	Calling needed functions from the other main classes
*/
class World
{
    public:
        World();
        virtual ~World();

        SDL_Renderer* m_main_renderer;
        SDL_Window* m_main_window;

        int m_SCREEN_WIDTH;
        int m_SCREEN_HEIGHT;

        SDL_Event m_event;
        bool m_endGame;
        Vector2f m_mouseMultiply;

        Endgame endgame;
        Credits credits;
        Menu m_menu;
        SoundManager* m_soundManager;
        GameManager m_gameManager;
        IconManager* m_iconManager;
        InputManager* m_inputManager;

        bool m_quitScene;

        GAME_STATE m_gameState;

        void init();
        void improveRenderer();
        void destroy();
        void input();

    protected:

    private:
};

#endif // WORLD_H
