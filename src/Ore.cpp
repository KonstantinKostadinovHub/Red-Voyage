#include "Ore.h"

#include "World.h"
extern World world;

Ore::Ore()
{
    //ctor
}

Ore::Ore(const Ore* model, SDL_Renderer* renderer, coordinates coor)
{
    m_renderer = renderer;

    m_health = model->m_health;
    m_texture = model->m_texture;
    m_type = model->m_type;

    m_zoom_lvl = &world.m_camera.zoom_lvl;
    m_cameraRect = &world.m_camera.camera_rect;

    m_rect.x = coor.x;
    m_rect.y = coor.y;

    m_rect.w = model->m_rect.w;
    m_rect.h = model->m_rect.h;
}

Ore::~Ore()
{
    //dtor
}

void Ore::load(string configFile)
{
    configFile = "config\\" + configFile;

    fstream stream;
    string tmp, img;
    int type;
    stream.open(configFile);
    stream >> tmp >> img;
    stream >> tmp >> type;
    stream >> tmp >> m_health;
    stream >> tmp >> m_rect.w >> m_rect.h;
    stream.close();

    m_type = (ORE)type;

    img = "\\ores\\" + img;
    m_texture = LoadTexture(img, world.m_main_renderer);
}

void Ore::takeHit()
{
    m_health --;
}

void Ore::draw()
{
    world.drawObject(m_rect, m_texture);
}
