#ifndef MENU_H
#define MENU_H

#include <SDL.h>

#include <string>
#include "defines.h"

using namespace std;

class Menu
{
    public:

        Menu();
        virtual ~Menu();

        string m_img;
        string m_startImg;
        string m_exitImg;
        string m_logoImg;

        float m_sizeMultiplier;

        SDL_Texture* m_objectTexture;
        SDL_Texture* m_startTexture;
        SDL_Texture* m_exitTexture;
        SDL_Texture* m_logoTexture;

        SDL_Rect m_startRect;
        SDL_Rect m_exitRect;
        SDL_Rect m_logoRect;


        SDL_Rect m_startStartRect;
        SDL_Rect m_startExitRect;

        void load(string config);
        void update();
        void draw();

        void EnlargeButtons(coordinates coor ,SDL_Rect &rect ,SDL_Rect startRect);

    protected:

    private:
};

#endif // MENU_H
