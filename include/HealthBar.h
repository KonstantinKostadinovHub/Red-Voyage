#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>

#include "Engine.h"

using namespace std;

/*! \brief Used to create player's health bars

*/

class HealthBar
{
    public:
        HealthBar();
        virtual ~HealthBar();

        void init(string configFile);
        void update(int health, int maxHealth);
        void draw(SDL_Renderer* renderer);
        SDL_Rect m_barRect;

        float HP;
        string m_configFile;
        string m_borderImg;
        string m_healthImg;

        SDL_Texture* m_borderTexture;
        SDL_Texture* m_healthTexture;

        SDL_Rect m_objRect;

    protected:

    private:
};

#endif // HEALTHBAR_H
