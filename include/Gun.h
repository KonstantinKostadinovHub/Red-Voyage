#ifndef GUN_H
#define GUN_H

#include <time.h>
#include <SDL.h>
#include <chrono>

#include "Engine.h"

class Gun
{
    public:
        virtual ~Gun();
        Gun();

        SDL_Rect m_objRect;

        coordinates m_coor;
        coordinates m_oldVelocity;

        float m_rotationAngle;

        time_t m_startShootCooldown;
        time_t m_shootCooldown;

        bool m_canShoot;
        bool isPressed;

        chrono::high_resolution_clock::time_point m_elapsed_engage;
        chrono::duration<float> m_engagementRate;

        void init(float attackSpeed);
        void update(coordinates, coordinates playerCoor, bool shootIsPressed);

    protected:

    private:
};

#endif // GUN_H
