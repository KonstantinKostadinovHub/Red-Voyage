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

        void init(string configFile, float* health, float* maxHealth, float* shield);
        void update();
        void draw(SDL_Renderer* renderer);
        SDL_Rect m_barRect;

        float* m_health;
        float* m_maxHealth;
        float* m_shield;

        float HP;
        float m_shieldPercentage;
        string m_configFile;

        SDL_Texture* m_borderTexture;
        SDL_Texture* m_healthTexture;
        SDL_Texture* m_shieldTexture;

        SDL_Rect m_objRect;
        SDL_Rect m_shieldRect;

    protected:

    private:
};

#endif // HEALTHBAR_H
