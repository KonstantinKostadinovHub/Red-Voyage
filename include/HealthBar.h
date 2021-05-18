#ifndef HEALTHBAR_H
#define HEALTHBAR_H

#include <SDL.h>
#include <string>
#include <fstream>
#include <iostream>

#include "Engine.h"

using namespace std;

class HealthBar
{
    public:
        HealthBar();
        virtual ~HealthBar();

        void init(string configFile);
        void update(int health, int maxHealth);
        void draw(SDL_Renderer* renderer);
        SDL_Rect m_barRect;

    protected:
        float HP;
        string m_configFile;
        string m_borderImg;
        string m_healthImg;

        SDL_Texture* m_borderTexture;
        SDL_Texture* m_healthTexture;

        SDL_Rect m_objRect;

    private:
};

#endif // HEALTHBAR_H
