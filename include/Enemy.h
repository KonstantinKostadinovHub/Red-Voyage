#ifndef ENEMY_H
#define ENEMY_H

#include <chrono>

#include <SDL.h>
#include <Engine.h>
#include <EnemyBullet.h>
#include "Animator.h"

/*! \brief Used to create enemies (AI) and define their actions
* 
* This class initializes melee fighting enemies or ones that don't shoot projectiles.
*/

class Enemy
{
    public:
        Enemy();
        Enemy(const Enemy& model);
        virtual ~Enemy();

        SDL_Rect m_presentRect;
        SDL_Rect* m_cameraRect;
        float* m_zoom_lvl;

        SDL_Renderer* m_renderer;

        const short ACCURACY = 35;
        const short SMOOTH = 12;

        short m_width;
        short m_height;
        short m_velocity;
        short m_health;
        short m_readChargeMax;
        short m_engagementIndex;
        short m_range;
        short m_damage;
        double m_angle;
        double m_targetAngle;
        bool m_inSpaceship;
        bool m_engage;

        int m_widthOfFrame;

        animation* anim;

        SDL_Rect m_animRect;
        SDL_Rect m_srcRect;

        coordinates m_targetCoord;
        vector<coordinates> m_pathCoord;
        string m_pathData;
        short m_pathIndex;

        chrono::high_resolution_clock::time_point m_chargeTime;
        chrono::duration<float> m_chargeMax;

        string m_img;
        SDL_Texture* m_objectTexture;

        SDL_Rect m_objectRect;


        void search();
        void engage();
        void step();
        virtual void attack();

        virtual void load(string stream);
        void update();
        virtual void draw();
		virtual void destroy();

    protected:

    private:
};

#endif // ENEMY_H
