#include "HealthBar.h"
#include "World.h"

extern World world;

HealthBar::HealthBar()
{
    m_health;
    m_maxHealth;
}

HealthBar::~HealthBar()
{
    SDL_DestroyTexture(m_borderTexture);
    SDL_DestroyTexture(m_healthTexture);
}

void HealthBar::init(string configFile, float* health, float* maxHealth, float* shield)
{
    m_configFile = "config\\" + UI_FOLDER + configFile;

    fstream stream;
    string tmp, borderImg, healthImg, shieldImg;

    stream.open(m_configFile.c_str());

    stream >> tmp >> m_objRect.x >> m_objRect.y >> m_objRect.w >> m_objRect.h;
    stream >> tmp >> borderImg;
    stream >> tmp >> healthImg;
    stream >> tmp >> shieldImg;

    stream.close();

    m_health = health;
    m_maxHealth = maxHealth;
    m_shield = shield;

    borderImg = UI_FOLDER + borderImg;
    healthImg = UI_FOLDER + healthImg;
    shieldImg = UI_FOLDER + shieldImg;

    m_borderTexture = LoadTexture(borderImg, world.m_main_renderer);
    m_healthTexture = LoadTexture(healthImg, world.m_main_renderer);
    m_shieldTexture = LoadTexture(shieldImg, world.m_main_renderer);
    
    m_barRect = m_objRect;
    m_shieldRect = m_objRect;
}

void HealthBar::update()
{
    HP = *m_health / *m_maxHealth;
    m_shieldPercentage = *m_shield / *m_maxHealth;
}

void HealthBar::draw(SDL_Renderer* renderer)
{
    /// We expand the image

    m_barRect.w = (float)m_objRect.w * HP;
    m_shieldRect.w = (float)m_objRect.h * m_shieldPercentage;
    m_shieldRect.x = m_objRect.x + m_objRect.w - m_shieldRect.w;

    SDL_RenderCopy(renderer, m_borderTexture, NULL, &m_objRect);
    SDL_RenderCopy(renderer, m_healthTexture, NULL, &m_barRect);
    SDL_RenderCopy(renderer, m_shieldTexture, NULL, &m_shieldRect);
}
