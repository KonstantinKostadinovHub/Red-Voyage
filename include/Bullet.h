#ifndef BULLET_H
#define BULLET_H

#include <iostream>
#include <string>
#include <fstream>
#include <SDL.h>

#include "Engine.h"

using namespace std;

class Bullet
{
    public:
        Bullet();
        Bullet(const Bullet* model, SDL_Renderer* renderer, coordinates coor);
        virtual ~Bullet();

        SDL_Renderer* m_renderer;

        string m_configFile;
        string m_img;

        int m_health;

        SDL_Rect* m_cameraRect;
        float* m_zoom_lvl;

        SDL_Rect m_presentRect;
        SDL_Rect m_objRect;

        line collLine;

        int m_speed;
        int m_damage;
        int health;

        coordinates m_velocity;

        SDL_Texture* m_bulletTexture;

        void init(string configFile, SDL_Renderer* renderer);
        void update();
        void draw(SDL_Renderer* renderer);
        void load(string configFile);

        coordinates m_coor;

    protected:

    private:
};

#endif // BULLET_H
