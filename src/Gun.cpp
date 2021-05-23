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
}

void Gun::update(coordinates velocity, coordinates playerCoor, bool shootIsPressed)
{
    /*! We calculate the velocity and position the gun to player's coordinates.
    *    
    *   We calculate the cooldown and if it is expired the player can shoot
    */

    if(velocity.x == 0 && velocity.y == 0)
    {
        velocity = m_oldVelocity;
    }
    else
    {
        m_oldVelocity = velocity;
    }

    m_objRect.x = playerCoor.x + velocity.x * 70;
    m_objRect.y = playerCoor.y + velocity.y * 70;

    if(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_elapsed_engage) > m_engagementRate && shootIsPressed)
    {
        m_canShoot = true;
    }
    else{
        m_canShoot = false;
    }
}
