#ifndef WORLD_H
#define WORLD_H

#include "GameManager.h"

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
        double m_MOUSE_MULTIPLY_X;
        double m_MOUSE_MULTIPLY_Y;

        bool m_drag;
        bool m_mouseIsPressed;
        bool m_mouseIsDoubleClicked;
        coordinates m_mouseCoordinates;

        Endgame endgame;
        Credits credits;
        Menu m_menu;
        SoundManager* m_soundManager;
        GameManager m_gameManager;

        bool m_quitScene;

        GAME_STATE m_gameState;

        void init();
        void input();
        void improveRenderer();
        void destroy();

    protected:

    private:
};

#endif // WORLD_H
