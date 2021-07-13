#ifndef ORE_H
#define ORE_H

#include <fstream>

#include <SDL.h>

#include "defines.h"

using namespace std;

class Ore
{
    public:
        Ore();
        Ore(const Ore* model, SDL_Renderer* renderer, Vector2 coor);
        virtual ~Ore();

        SDL_Renderer* m_renderer;

        SDL_Rect m_rect;
        SDL_Rect m_presentRect;
        float* m_zoom_lvl;
        SDL_Rect* m_cameraRect;
        SDL_Texture* m_texture;
        int m_health;
        ORE m_type;

        void load(string configFile);
        void draw();
        void takeHit();

    protected:

    private:
};

#endif // ORE_H
