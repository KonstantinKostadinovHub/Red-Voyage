#ifndef GUN_H
#define GUN_H

#include <time.h>
#include <SDL.h>
#include <chrono>

#include "Engine.h"

/*! \brief This class is responsible for the shooting of the player

    With this class me create a gun with which the player can shoot.
*/

class Gun
{
public:
    virtual ~Gun();
    Gun();

    SDL_Rect m_objRect;

    Vector2 m_oldVelocity;

    float m_rotationAngle;

    time_t m_startShootCooldown;
    time_t m_shootCooldown;

    bool m_canShoot;
    bool isPressed;

    chrono::high_resolution_clock::time_point m_elapsed_engage;
    chrono::duration<float> m_engagementRate;

    void init(float attackSpeed);
    void update(Vector2 velocity, Vector2 playerCoor, bool shootIsPressed);

protected:
    friend class Player;
    void setPlayerRect(SDL_Rect* rect);
    Vector2* getShootingPoint();
        
private:
    Vector2* m_mouseCoor;
    SDL_Rect* m_playerRect;
    Vector2 m_playerCenter;
    Vector2 m_direction;
    Vector2 m_shootingPoint;
    void aim();
};

#endif // GUN_H
