#include "EnemyBullet.h"
#include <fstream>

#include  "World.h"
extern World world;

EnemyBullet::EnemyBullet()
{
    /*
    * Basic constructor.
    */
}

EnemyBullet::EnemyBullet(const EnemyBullet& model) {
    /*
    * Constructor that uses a constant model and copies the variables.
    */
    m_objectRect = model.m_objectRect;
    m_objectTexture = model.m_objectTexture;
    m_velocity = model.m_velocity;
    m_damage = model.m_damage;

    m_updateAngle = true;

    m_cameraRect = &world.m_camera.camera_rect;
    m_zoom_lvl = &world.m_camera.zoom_lvl;
}

EnemyBullet::~EnemyBullet() {
    /*
    * Destructor.
    */
}

void EnemyBullet::load(string config) {
    /*
    * Loads variables for the first time.
    */
    config = "config\\" + config;
    ifstream stream;
    stream.open(config.c_str());

    string tmp;
    stream >> tmp >> m_width;
    stream >> tmp >> m_heigth;
    stream >> tmp >> m_img;
    stream >> tmp >> m_velocity;
    stream >> tmp >> m_damage;

    stream.close();

    m_img = "\\enemy\\" + m_img;

    m_objectRect.w = m_width;
    m_objectRect.h = m_heigth;
    m_angle = 0;

    m_objectTexture = LoadTexture(m_img, world.m_main_renderer);
}

void EnemyBullet::update() {
    /*
    * Moves the bullet.
    */
    if (m_updateAngle) {
        m_angle += rand()%(2*LIMIT) - LIMIT;
        m_updateAngle = false;
    }

    m_objectRect.x += m_velocity*sin(m_angle*PI/180);
    m_objectRect.y -= m_velocity*cos(m_angle*PI/180);
}

void EnemyBullet::draw(SDL_Renderer* renderer) {
    /*
    * Draws the bullet.
    */
    m_presentRect = {
        (int)(*m_zoom_lvl * (double)(m_objectRect.x - m_cameraRect->x)),
		(int)(*m_zoom_lvl * (double)(m_objectRect.y - m_cameraRect->y)),
		(int)(*m_zoom_lvl * m_objectRect.w),
		(int)(*m_zoom_lvl * m_objectRect.h)
    };


    SDL_RenderCopyEx(renderer, m_objectTexture, NULL, &m_presentRect, m_angle, NULL, SDL_FLIP_NONE);
}
