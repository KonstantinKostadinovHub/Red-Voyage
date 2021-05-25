#include "Bullet.h"

#include "World.h"
extern World world;

Bullet::Bullet()
{
    //ctor
}

Bullet::Bullet(const Bullet* model, SDL_Renderer* renderer, coordinates velocity)
{
    m_renderer = renderer;

    m_speed = model -> m_speed;
    m_bulletTexture = model -> m_bulletTexture;
    m_health = model -> m_health;
    m_damage = model -> m_damage;

    m_zoom_lvl = &world.m_camera.zoom_lvl;
    m_cameraRect = &world.m_camera.camera_rect;

    m_velocity.x = velocity.x;
    m_velocity.y = velocity.y;

    m_objRect.w = model->m_objRect.w;
    m_objRect.h = model->m_objRect.h;
}


Bullet::~Bullet()
{

}


void Bullet::load(string configFile)
{
    m_configFile = "config\\" + configFile;

    fstream stream;
    string tmp;

    stream.open(m_configFile.c_str());
    stream >> tmp >> m_objRect.w >> m_objRect.h;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_damage;
    stream >> tmp >> m_img;
    stream >> tmp >> m_health;

    stream.close();

    m_img = "\\player\\" + m_img;

    m_bulletTexture = LoadTexture(m_img, world.m_main_renderer);

    m_cameraRect = &world.m_camera.camera_rect;
    m_zoom_lvl = &world.m_camera.zoom_lvl;
}

void Bullet::update()
{
    /*! 
    *   We move the bullet every frame, using the velocity in the X and Y direction.
    * 
    *   We use m_coor to calculate with precision the position of the bullet then convert it to the objectRect.
    * 
    *   We make a line, the one end is the old position and the other end is the new. Than we check if this line
        has collision with the ship. We use this check, because otherwise the bullet may teleport trough the ship
        and miss the collision check.
    */

    m_coor.x += (float)m_velocity.x * m_speed * SPEED_FACTOR;
    m_coor.y += (float)m_velocity.y * m_speed * SPEED_FACTOR;

    m_objRect.x = m_coor.x;
    m_objRect.y = m_coor.y;

    collLine.finish = collLine.start;
    collLine.start.x = m_objRect.x;
    collLine.start.y = m_objRect.y;
}

void Bullet::draw(SDL_Renderer* renderer)
{
    world.drawObject(m_objRect, m_bulletTexture);
}
