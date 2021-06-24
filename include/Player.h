#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <chrono>
#include <ctime>
#include <cmath>

#include "Gun.h"
#include "HealthBar.h"
#include "Engine.h"
#include "Animator.h"

using namespace std;

/*! \brief Responible for all player's functions
* 
*   We use this class to move the player, to shoot and to do tasks.
*/

class Player
{
public:
    Player();
    virtual ~Player();

    coordinates m_oldCoor;
    coordinates m_coor;
    coordinates m_center;
    coordinates m_velocity;
    coordinates m_oldvelocity;
    coordinates m_direction;

    int m_widthOfFrame;

    animation* anim;

    HealthBar* m_healthBar;

    SDL_Rect rect;

    float* m_zoom_lvl;
    SDL_Rect* m_camera_rect;

    SDL_Rect m_presentRect;
    SDL_Rect m_animRect;

    time_t m_startShootCooldown;
    time_t m_shootCooldown;

    bool m_inSpaceship = false;

    float m_speed;
    float m_screenSpeed;

    string s_move_up;
    string s_move_down;
    string s_move_left;
    string s_move_right;
    string s_shoot;
    string s_craft;
    string m_playerImg;
    string HP;
    string m_configFile;

    SDL_Scancode move_up;
    SDL_Scancode move_down;
    SDL_Scancode move_left;
    SDL_Scancode move_right;
    SDL_Scancode shoot;
    SDL_Scancode craft;

    SDL_Rect m_objRect;

    void init(SDL_Renderer* renderer, string confingFile);
    void update();
    void draw();

    chrono::high_resolution_clock::time_point m_elapsed_engage;
    chrono::duration<float> m_engagementRate;

	time_t m_lastDustEffect; //< Remember when we last spawned a dust effect
	unsigned short m_timeBetweenDustEffects; //< How much time should we wait before we spawn a dust effect

    Gun* m_gun; //< The point from where the player shoots

    SDL_Texture* playerTexture;
    SDL_Texture* flipTexture;

    bool checkForShooting();
    bool m_canShoot;
    bool shootIsPressed;
    bool craftIsPressed;
    bool m_collWithDoor;

    line top, bot, left, right;
    
    int m_dmg, m_distance;

    SDL_Rect m_srcRect;

    /// Stats for the player
    float m_health;
    float m_maxHealth;
    float m_armor;
    float m_shield;

    void takeDamage(float damage);

protected:

private:
};

#endif // PLAYER_H
