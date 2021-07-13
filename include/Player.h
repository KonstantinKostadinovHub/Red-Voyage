#ifndef PLAYER_H
#define PLAYER_H

#include <SDL.h>

#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <map>
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

    Vector2 m_oldCoor;
    Vector2 m_coor;
    Vector2 m_velocity;
    Vector2 m_oldvelocity;

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

    string m_playerImg;
    string HP;
    string m_configFile;

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
    friend class Saver;
    void saveItems(fstream& stream);
    friend class ItemManager;
    void equipItem(ITEM_TYPE type, ITEM item);
    friend class Saver;
    void loadItems(fstream& stream);
    friend class GameManager;
    Vector2 getShootingPoint();
private:
    vector<ITEM> m_collectable;

    ITEM m_helmet;
    ITEM m_chestplate;
    ITEM m_leggings;
    ITEM m_boots;

    ITEM m_primaryWeapon;
    ITEM m_secondaryWeapon;

    Vector2* m_shootingPoint;
};

#endif // PLAYER_H
