#include "Enemy.h"
#include <World.h>

extern World world;

Enemy::Enemy()
{
    /*
    * Basic constructor.
    */
    m_chargeMax = chrono::milliseconds(0);
    m_chargeTime = chrono::high_resolution_clock::now();
    m_inSpaceship = false;
    m_stepSpaceship = false;
    m_engagementIndex = -1;
}

Enemy::Enemy(const Enemy& model) {
    /*
    * Constructor that uses a constant model and copies the variables.
    */
    m_objectRect = model.m_objectRect;
    m_objectTexture = model.m_objectTexture;
    m_spaceshipCoord.x = model.m_spaceshipCoord.x;
    m_spaceshipCoord.y = model.m_spaceshipCoord.y;
    m_entryRange = model.m_entryRange;
    m_angle = model.m_angle;
    m_velocity = model.m_velocity;
    m_health = model.m_health;
    m_readChargeMax = model.m_readChargeMax;
    m_range = model.m_range;
    m_damage = model.m_damage;

    m_chargeMax = chrono::milliseconds(m_readChargeMax);
    m_chargeTime = chrono::high_resolution_clock::now();
    m_inSpaceship = false;
    m_stepSpaceship = false;
    m_engagementIndex = -1;

    m_cameraRect = &world.m_camera.camera_rect;
    m_zoom_lvl = &world.m_camera.zoom_lvl;
    m_renderer = model.m_renderer;

    anim = new animation;
    anim -> frames = 3;
    anim -> lastFrameUpdate = chrono::high_resolution_clock::now();
    anim -> timePerFrame = chrono::milliseconds((int)100);
    anim -> widthOfFrame = model.m_widthOfFrame;
    anim -> srcRect = &m_srcRect;
    anim -> srcRect -> x = model.m_animRect.x;
    anim -> srcRect -> y = model.m_animRect.y;
    anim -> srcRect -> w = model.m_animRect.w;
    anim -> srcRect -> h = model.m_animRect.h;

    world.m_animator.m_animations.push_back(anim);
}

Enemy::~Enemy()
{
    /*
    * Destructor.
    */
}

void Enemy::load(string config) {
    /*
    * Loads variables for the first time.
    */
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
    stream >> tmp >> m_velocity;
    stream >> tmp >> m_health;
    stream >> tmp >> m_readChargeMax;
    stream >> tmp >> m_range;
    stream >> tmp >> m_damage;
    stream >> tmp >> m_animRect.x >> m_animRect.y >> m_animRect.w >> m_animRect.h;
    stream >> tmp >> m_widthOfFrame;

    stream.close();

    m_objectRect.w = m_width;
    m_objectRect.h = m_height;
    m_angle = 0;

    m_renderer = world.m_main_renderer;

    m_objectTexture = LoadTexture(m_img, m_renderer);

}

void Enemy::engage() {
    /*
    * Chooses a target for the enemy.
    */
    m_targetSpaceship = true;
    m_targetOutside = true;

    for (auto player: world.m_players) {
        if (!player->m_inSpaceship) m_targetSpaceship = false;
        if (player->m_inSpaceship) m_targetOutside = false;
    }

    if ((m_targetOutside && m_inSpaceship) || (m_targetSpaceship && !m_inSpaceship)) {
        m_targetCoord.x = m_spaceshipCoord.x;
        m_targetCoord.y = m_spaceshipCoord.y;

        m_stepSpaceship = true;
    } else {
        m_stepSpaceship = false;

        int closest = world.m_SCREEN_WIDTH*world.m_SCREEN_WIDTH + world.m_SCREEN_HEIGHT*world.m_SCREEN_HEIGHT;
        int current;

        for (int i = 0; i != world.m_players.size(); i++) {
            if (world.m_players[i]->m_inSpaceship != m_inSpaceship) continue;

            current = sqrt((world.m_players[i]->m_objRect.x - m_objectRect.x)*(world.m_players[i]->m_objRect.x - m_objectRect.x) +
                           (world.m_players[i]->m_objRect.y - m_objectRect.y)*(world.m_players[i]->m_objRect.y - m_objectRect.y));
            if (current <= closest) {
                closest = current;
                m_engagementIndex = i;
            }
        }

        if (m_engagementIndex != -1) {
            m_targetCoord.x = world.m_players[m_engagementIndex]->m_objRect.x;
            m_targetCoord.y = world.m_players[m_engagementIndex]->m_objRect.y;
        }
    }
}

void Enemy::step() {
    /*
    * Moves the enemy.
    */
    int diffX = m_targetCoord.x - m_objectRect.x;
    int diffY = m_targetCoord.y - m_objectRect.y;

    m_targetAngle = asin(abs(diffX) / sqrt(diffX*diffX + diffY*diffY))*180.0/PI;

    if (diffX > 0 && diffY > 0) m_targetAngle = 180 - m_targetAngle;
    if (diffX < 0 && diffY > 0) m_targetAngle = m_targetAngle - 180;
    if (diffX < 0 && diffY < 0) m_targetAngle = - m_targetAngle;
    if (m_targetAngle < 0) m_targetAngle += 360;

    if (!m_stepSpaceship) {
        if (!m_inSpaceship && m_targetSpaceship && sqrt(diffX*diffX + diffY*diffY) <= m_range) {
            m_inSpaceship = true;
        } else if (m_inSpaceship && m_targetOutside && sqrt(diffX*diffX + diffY*diffY) <= m_range) {
            m_inSpaceship = false;
        } else if (sqrt(diffX*diffX + diffY*diffY) <= m_range) return;
    } else {
        if (!m_inSpaceship && m_targetSpaceship && sqrt(diffX*diffX + diffY*diffY) <= m_entryRange) {
            m_inSpaceship = true;
        } else if (m_inSpaceship && m_targetOutside && sqrt(diffX*diffX + diffY*diffY) <= m_entryRange) {
            m_inSpaceship = false;
        } else if (sqrt(diffX*diffX + diffY*diffY) <= m_entryRange) return;
    }

    if (!(abs(m_angle - m_targetAngle) <= ACCURACY)) {
        if (m_targetAngle <= 22.5) {
            m_angle = 0;
        } else if (m_targetAngle < 67.5) {
            m_angle = 45;
        } else if (m_targetAngle <= 112.5) {
            m_angle = 90;
        } else if (m_targetAngle < 157.5) {
            m_angle = 135;
        } else if (m_targetAngle <= 202.5) {
            m_angle = 180;
        } else if (m_targetAngle < 247.5) {
            m_angle = 225;
        } else if (m_targetAngle <= 292.5) {
            m_angle = 270;
        } else if (m_targetAngle < 337.5) {
            m_angle = 315;
        }
    }

    m_objectRect.x += m_velocity*sin(m_angle*PI/180);
    m_objectRect.y -= m_velocity*cos(m_angle*PI/180);
}

void Enemy::attack() {
    /*
    * Attack target.
    */
    for (auto player: world.m_players) {
        if (sqrt((player->m_objRect.x - m_objectRect.x)*(player->m_objRect.x - m_objectRect.x) +
            (player->m_objRect.y - m_objectRect.y)*(player->m_objRect.y - m_objectRect.y)) <= m_range) {

            if (chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_chargeTime) >= m_chargeMax) {
                player->m_health -= m_damage;

                m_chargeTime = chrono::high_resolution_clock::now();
            }
        }
    }
}

void Enemy::update() {
    /*
    * Update the enemy.
    */
    engage();
    step();
    attack();
}

void Enemy::draw() {
    /*
    * Draw the enemy;
    */
    m_presentRect = {
		static_cast<int>(*m_zoom_lvl * static_cast<double>(m_objectRect.x - m_cameraRect->x)),
		static_cast<int>(*m_zoom_lvl * static_cast<double>(m_objectRect.y - m_cameraRect->y)),
		static_cast<int>(*m_zoom_lvl * m_objectRect.w),
		static_cast<int>(*m_zoom_lvl * m_objectRect.h)
    };

    SDL_RenderCopyEx(m_renderer, m_objectTexture, &m_srcRect, &m_presentRect, m_angle, NULL, SDL_FLIP_NONE);
}
