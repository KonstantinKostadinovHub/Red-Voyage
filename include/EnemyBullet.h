#ifndef ENEMYBULLET_H
#define ENEMYBULLET_H

#include "Engine.h"

/*! \brief Used to create bullets for enemy shooters
* 
* This class initializes projectiles and defines their movement.
*/

class EnemyBullet
{
    public:
        EnemyBullet();
        EnemyBullet(const EnemyBullet& model);
        virtual ~EnemyBullet();

        const short LIMIT = 15;

        short m_width;
        short m_heigth;
        short m_velocity;
        short m_damage;
        double m_angle;
        bool m_updateAngle;

        SDL_Rect m_presentRect;
        SDL_Rect* m_cameraRect;
        float* m_zoom_lvl;

        string m_img;

        SDL_Texture* m_objectTexture;
        SDL_Rect m_objectRect;

        void load(string config);
        void update();
        void draw(SDL_Renderer* renderer);

    protected:

    private:
};

#endif // ENEMYBULLET_H
