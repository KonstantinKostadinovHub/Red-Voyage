#include "HealthBar.h"
#include "World.h"

extern World world;

HealthBar::HealthBar()
{
    //ctor
}

HealthBar::~HealthBar()
{
    SDL_DestroyTexture(m_borderTexture);
    SDL_DestroyTexture(m_healthTexture);
}

void HealthBar::init(string configFile)
{
    m_configFile = "config\\UI\\" + configFile;

    fstream stream;
    string tmp;

    stream.open(m_configFile.c_str());

    stream >> tmp >> m_objRect.x >> m_objRect.y >> m_objRect.w >> m_objRect.h;
    stream >> tmp >> m_borderImg;
    stream >> tmp >> m_healthImg;

    stream.close();

    m_borderImg = "\\UI\\" + m_borderImg;
    m_healthImg = "\\UI\\" + m_healthImg;

    m_borderTexture = LoadTexture(m_borderImg, world.m_main_renderer);
    m_healthTexture = LoadTexture(m_healthImg, world.m_main_renderer);
}

void HealthBar::update(int health, int maxHealth)
{
    HP = (float)health / float(maxHealth);
}

void HealthBar::draw(SDL_Renderer* renderer)
{
    /* We expand the image
    */

    m_barRect = m_objRect;
    m_barRect.w = (float)m_objRect.w * HP;

    SDL_RenderCopy(renderer, m_borderTexture, NULL, &m_objRect);
    SDL_RenderCopy(renderer, m_healthTexture, NULL, &m_barRect);
}
