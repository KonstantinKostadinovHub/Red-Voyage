#include "EnemyShooter.h"
#include <World.h>

extern World world;

EnemyShooter::EnemyShooter()
{
    //ctor
}

EnemyShooter::EnemyShooter(const EnemyShooter& model) {
    m_objectRect = model.m_objectRect;
    m_objectTexture = model.m_objectTexture;
    m_bulletConfig = model.m_bulletConfig;
    m_spaceshipCoord.x = model.m_spaceshipCoord.x;
    m_spaceshipCoord.y = model.m_spaceshipCoord.y;
    m_entryRange = model.m_entryRange;
    m_angle = model.m_angle;
    m_velocity = model.m_velocity;
    m_health = model.m_health;
    m_readChargeMax = model.m_readChargeMax;
    m_range = model.m_range;

    m_chargeMax = chrono::milliseconds(m_readChargeMax);
    m_chargeTime = chrono::high_resolution_clock::now();
    m_inSpaceship = false;
    m_stepSpaceship = false;

    m_zoom_lvl = model.m_zoom_lvl;
    m_cameraRect = model.m_cameraRect;
    m_renderer = model.m_renderer;
}

EnemyShooter::~EnemyShooter()
{

}

void EnemyShooter::load(string config) {
    ifstream stream;
    config = "config\\" + config;
    stream.open(config);

    string tmp;
    stream >> tmp >> m_width;
    stream >> tmp >> m_height;
    stream >> tmp >> m_spaceshipCoord.x;
    stream >> tmp >> m_spaceshipCoord.y;
    stream >> tmp >> m_entryRange;
    stream >> tmp >> m_img;
    stream >> tmp >> m_bulletConfig;
    stream >> tmp >> m_velocity;
    stream >> tmp >> m_health;
    stream >> tmp >> m_readChargeMax;
    stream >> tmp >> m_range;
    stream.close();

    m_objectRect.w = m_width;
    m_objectRect.h = m_height;
    m_angle = 0;

    m_renderer = world.m_main_renderer;
    m_zoom_lvl = &world.m_camera.zoom_lvl;
    m_cameraRect = &world.m_camera.camera_rect;

    m_objectTexture = LoadTexture(m_img, m_renderer);
}

void EnemyShooter::attack() {
    for (auto player: world.m_players) {
        if (sqrt((player->m_objRect.x - m_objectRect.x)*(player->m_objRect.x - m_objectRect.x) +
            (player->m_objRect.y - m_objectRect.y)*(player->m_objRect.y - m_objectRect.y)) <= m_range
            && !(m_targetCoord.x == m_spaceshipCoord.x && m_targetCoord.y == m_spaceshipCoord.y && (m_targetSpaceship || m_targetOutside))) {
            if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_chargeTime) >= m_chargeMax) {

                EnemyBullet* bullet = new EnemyBullet(world.m_configManager.m_enemyBullet);

                bullet->m_objectRect.x = m_objectRect.x + bullet->m_objectRect.w/2;
                bullet->m_objectRect.y = m_objectRect.y + bullet->m_objectRect.h/2;
                bullet->m_angle = m_targetAngle;

                world.m_enemyBullets.push_back(bullet);

                m_chargeTime = chrono::high_resolution_clock::now();
            }
        }
    }
}

void EnemyShooter::draw() {
    m_presentRect = {
		(int)(*m_zoom_lvl * (double)(m_objectRect.x - m_cameraRect->x)),
		(int)(*m_zoom_lvl * (double)(m_objectRect.y - m_cameraRect->y)),
		(int)(*m_zoom_lvl * m_objectRect.w),
		(int)(*m_zoom_lvl * m_objectRect.h)
    };

    SDL_RenderCopyEx(m_renderer, m_objectTexture, NULL, &m_presentRect, m_angle, NULL, SDL_FLIP_NONE);
}
