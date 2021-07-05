#include "Gun.h"
#include "World.h"

extern World world;

Gun::Gun()
{
    m_oldVelocity.x = 1;
    m_oldVelocity.y = 0;
}

Gun::~Gun()
{
    //dtor
}

void Gun::init(float attackSpeed)
{
    m_engagementRate = chrono::milliseconds((int)attackSpeed);
    m_elapsed_engage = chrono::high_resolution_clock::now();
    m_canShoot = false;
    m_mouseCoor = &world.m_mouseCoordinates;
}

void Gun::update(coordinates velocity, coordinates playerCoor, bool shootIsPressed)
{
    /*! We calculate the velocity and position the gun to player's coordinates.
    *    
    *   We calculate the cooldown and if it is expired the player can shoot
    */
    aim();

    if(velocity.x == 0 && velocity.y == 0)
    {
        velocity = m_oldVelocity;
    }
    else
    {
        m_oldVelocity = velocity;
    }

    m_objRect.x = playerCoor.x + velocity.x * 55;
    m_objRect.y = playerCoor.y + velocity.y * 80;

    if(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_elapsed_engage) > m_engagementRate && shootIsPressed)
    {
        m_canShoot = true;
    }
    else{
        m_canShoot = false;
    }
}


void Gun::aim()
{
    SDL_Rect presentRect = world.m_gameManager.toScreenCoordinates(*m_playerRect);
    m_playerCenter = { presentRect.x + presentRect.w / 2, presentRect.y + presentRect.h / 2 };
    m_direction = { m_mouseCoor->x - m_playerCenter.x, m_mouseCoor->y - m_playerCenter.y };

    m_shootingPoint.x = m_playerRect->x + m_playerRect->w / 2;
    m_shootingPoint.y = m_playerRect->y + m_playerRect->h / 2;

    m_rotationAngle = returnAngleByCoordinates(m_direction);
}

void Gun::setPlayerRect(SDL_Rect* rect)
{
    m_playerRect = rect;
}

coordinates* Gun::getShootingPoint()
{
    return &m_shootingPoint;
}