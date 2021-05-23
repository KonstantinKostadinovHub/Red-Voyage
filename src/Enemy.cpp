#include "Enemy.h"
#include <World.h>

extern World world;

Enemy::Enemy()
{
    /*
    * Basic constructor.
    */
}

Enemy::Enemy(const Enemy& model) {
    /*
    * Constructor that uses a constant model and copies the variables.
    */
    m_objectRect = model.m_objectRect;
    m_objectTexture = model.m_objectTexture;
    m_pathCoord = model.m_pathCoord;
    m_angle = model.m_angle;
    m_velocity = model.m_velocity;
    m_health = model.m_health;
    m_readChargeMax = model.m_readChargeMax;
    m_range = model.m_range;
    m_damage = model.m_damage;

    m_chargeMax = chrono::milliseconds(m_readChargeMax);
    m_chargeTime = chrono::high_resolution_clock::now();
    m_pathIndex = m_pathCoord.size() - 1;
    m_inSpaceship = false;
    m_engage = false;
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
	m_renderer = nullptr;
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
    stream >> tmp >> m_img;
    stream >> tmp >> m_pathData;
    stream >> tmp >> m_velocity;
    stream >> tmp >> m_health;
    stream >> tmp >> m_readChargeMax;
    stream >> tmp >> m_range;
    stream >> tmp >> m_damage;
    stream >> tmp >> m_animRect.x >> m_animRect.y >> m_animRect.w >> m_animRect.h;
    stream >> tmp >> m_widthOfFrame;

    stream.close();

    m_pathData = "config\\" + m_pathData;
    stream.open(m_pathData);

    short tmpValX;
    short tmpValY;
    coordinates tmpCoord;

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
    m_objectTexture = LoadTexture(m_img, m_renderer);
}

void Enemy::search() {
    /*
    * Searches for players on the same path level or switches to the opposite
    */
    bool level = false;

    if (!m_inSpaceship) {
        for (auto player : world.m_players) {
            if (!player->m_inSpaceship) level = true;
        }
    }
    else {
        for (auto player : world.m_players) {
            if (player->m_inSpaceship) level = true;
        }
    }

    if (level) { 
        engage(); 
        m_engage = true;
    }
    else {
        m_engage = false;

        m_targetCoord.x = m_pathCoord[m_pathIndex].x;
        m_targetCoord.y = m_pathCoord[m_pathIndex].y;

        if (m_pathIndex == 0) {
            m_inSpaceship = true;
        }
        if (m_pathIndex == m_pathCoord.size() - 1) {
            m_inSpaceship = false;
        }
    }
}

void Enemy::engage() {
    /*
    * Chooses a player target for the enemy.
    */
    int closest = world.m_SCREEN_WIDTH * world.m_SCREEN_WIDTH + world.m_SCREEN_HEIGHT * world.m_SCREEN_HEIGHT;
    int current;

    for (int i = 0; i != world.m_players.size(); i++) {
        if (world.m_players[i]->m_inSpaceship != collRectRect(world.m_spaceshipRect, m_objectRect)) continue;

        current = sqrt((world.m_players[i]->m_objRect.x - m_objectRect.x) * (world.m_players[i]->m_objRect.x - m_objectRect.x) +
            (world.m_players[i]->m_objRect.y - m_objectRect.y) * (world.m_players[i]->m_objRect.y - m_objectRect.y));

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

    if (m_engage) {
        if (sqrt(diffX * diffX + diffY * diffY) <= m_range) return;
    }
    else {
        if (!m_inSpaceship && (diffX * diffX + diffY * diffY) <= SMOOTH) m_pathIndex--;
        if (m_inSpaceship && (diffX * diffX + diffY * diffY) <= SMOOTH) m_pathIndex++;
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
    search();
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

void Enemy::destroy()
{
	anim->finished = true;
}
