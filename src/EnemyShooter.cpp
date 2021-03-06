#include "EnemyShooter.h"
#include <World.h>

extern World world;

EnemyShooter::EnemyShooter()
{
    /*
    * Basic constructor.
    */
}

EnemyShooter::EnemyShooter(const EnemyShooter& model) {
    /*
    * Constructor that uses a constant model and copies the variables.
    */
    m_objectRect = model.m_objectRect;
    m_objectTexture = model.m_objectTexture;
    m_bulletConfig = model.m_bulletConfig;
    m_pathCoord = model.m_pathCoord;
    m_angle = model.m_angle;
    m_velocity = model.m_velocity;
    m_health = model.m_health;
    m_readChargeMax = model.m_readChargeMax;
    m_range = model.m_range;

    m_chargeMax = chrono::milliseconds(m_readChargeMax);
    m_chargeTime = chrono::high_resolution_clock::now();
    m_pathIndex = m_pathCoord.size() - 1;
    m_inSpaceship = false;
    m_engage = false;

    m_type = ENEMY::SHOOTER;

    m_zoom_lvl = model.m_zoom_lvl;
    m_cameraRect = model.m_cameraRect;
    m_renderer = model.m_renderer;
}

EnemyShooter::~EnemyShooter()
{
    /*
    * Destructor.
    */
}

void EnemyShooter::load(string config) {
    /*
    * Loads variables for the first time.
    */
    ifstream stream;

    config = "config\\enemy\\" + config;
    stream.open(config);

    string tmp;
    stream >> tmp >> m_width;
    stream >> tmp >> m_height;
    stream >> tmp >> m_img;
    stream >> tmp >> m_bulletConfig;
    stream >> tmp >> m_pathData;
    stream >> tmp >> m_velocity;
    stream >> tmp >> m_health;
    stream >> tmp >> m_readChargeMax;
    stream >> tmp >> m_range;

    stream.close();

    m_img = "\\enemy\\" + m_img;

    m_pathData = "config\\enemy\\" + m_pathData;
    stream.open(m_pathData);

    short tmpValX;
    short tmpValY;
    Vector2 tmpCoord;

    while (!stream.eof()) {
        stream >> tmpValX >> tmpValY;
        tmpCoord.x = tmpValX;
        tmpCoord.y = tmpValY;

        m_pathCoord.push_back(tmpCoord);
    }

    stream.close();

    m_objectRect.w = m_width;
    m_objectRect.h = m_height;
    m_angle = 0;

    m_renderer = world.m_main_renderer;
    m_zoom_lvl = &world.m_gameManager.m_camera.zoom_lvl;
    m_cameraRect = &world.m_gameManager.m_camera.camera_rect;

    m_objectTexture = LoadTexture(m_img, m_renderer);
}

void EnemyShooter::attack() {
    /*
    * Enemy shooter's attack target.
    */
    for (auto player: world.m_gameManager.m_players) {
        if (sqrt((player->m_objRect.x - m_objectRect.x)*(player->m_objRect.x - m_objectRect.x) +
            (player->m_objRect.y - m_objectRect.y)*(player->m_objRect.y - m_objectRect.y)) <= m_range) {
            if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_chargeTime) >= m_chargeMax) {

                EnemyBullet* bullet = new EnemyBullet(world.m_gameManager.m_configManager.m_enemyBullet);

                bullet->m_objectRect.x = m_objectRect.x + bullet->m_objectRect.w/2;
                bullet->m_objectRect.y = m_objectRect.y + bullet->m_objectRect.h/2;
                bullet->m_angle = m_targetAngle;

                world.m_gameManager.m_enemyBullets.push_back(bullet);

                m_chargeTime = chrono::high_resolution_clock::now();
            }
        }
    }
}

void EnemyShooter::draw() {
    /*
    * Draw the enemy
    */
    m_presentRect = {
		(int)(*m_zoom_lvl * (double)(m_objectRect.x - m_cameraRect->x)),
		(int)(*m_zoom_lvl * (double)(m_objectRect.y - m_cameraRect->y)),
		(int)(*m_zoom_lvl * m_objectRect.w),
		(int)(*m_zoom_lvl * m_objectRect.h)
    };

    SDL_RenderCopyEx(m_renderer, m_objectTexture, NULL, &m_presentRect, m_angle, NULL, SDL_FLIP_NONE);
}
