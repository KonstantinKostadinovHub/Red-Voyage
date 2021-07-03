#pragma once

#include <iostream>
#include <vector>
#include <fstream>

#include <SDL.h>

#include "defines.h"
#include "Engine.h"
#include "Menu.h"
#include "ConfigManager.h"
#include "Ore.h"
#include "Generator.h"
#include "Player.h"
#include "Bullet.h"
#include "SoundManager.h"
#include "Camera.h"
#include "Food.h"
#include "ChickenWing.h"
#include "Enemy.h"
#include "EnemyShooter.h"
#include "EnemyBullet.h"
#include "Animator.h"
#include "UI.h"
#include "Tutorial.h"
#include "Endgame.h"
#include "Credits.h"
#include "VisualEffect.h"
#include "Helper.h"
#include "PowerUp.h"
#include "Saver.h"
#include "Cave.h"

class GameManager
{
public:
    GameManager();
    ~GameManager();

    SDL_Renderer* m_renderer;

    SDL_Rect m_backgroundRect;
    SDL_Texture* m_backgroundTexture;

    SDL_Texture* m_spaceshipTexture;
    SDL_Texture* m_spaceshipInsideTexture;
    SDL_Rect m_spaceshipRect;

    UI_object resumeButton;
    string m_resumeButtonImg;

    int x, y, m_distance;

    UI_object exitButton;
    string m_exitButtonImg;

    string m_pausedBackgroundImg;
    SDL_Texture* m_pausedBackgroundTexture;
    SDL_Rect m_pausedBackgroundRect;

    SDL_Texture* m_titleScreenTexture;///Mars_Spaceship_Inside_FInal.bmp

    SDL_Rect m_presentRect;

    int win = 0;
    int m_chickenCollected = 0;
    int m_aluminiumCollected = 0;
    int m_titaniumCollected = 0;
    int m_ironCollected = 0;
    bool buffBool;

    SDL_Event* m_event;
    bool* m_drag;
    bool* m_mouseIsPressed;
    bool* m_mouseIsDoubleClicked;
    coordinates* m_mouseCoordinates;

    Camera m_camera;
    coordinates m_directionCoor;

    float m_angle;
    bool m_isPaused;

    Food m_food_spawner;
    ChickenWing* chicken_wings[6];
    ConfigManager m_configManager;
    Generator m_generator;
    Tutorial m_tutorial;
    Helper* m_helper;
    Saver* m_saver;
    SoundManager* m_soundManager;
    Animator m_animator;
    Cave m_cave;

    vector <line> m_collLines;
    vector <Player*> m_players;
    vector <Bullet*> m_bullets;
    vector <Enemy*> m_enemies;
    vector <EnemyBullet*> m_enemyBullets;
    vector <Task*> m_tasks;
    vector <Ore*> m_ores;
    vector <VisualEffect*> m_vfxs;
    vector <PowerUp*> m_powerUps;
    vector <Item*> m_items;

    line m_door;

    UI m_userInterface;

    string m_backgroundImg = " ";

    void init();
    void update();
    void collision();
    void draw();
    void cleaner();
    void initSession();
    void deleteSession();

    void readCollisionPoints(string configFile);
    bool collisionWithShip(SDL_Rect rect);
    bool collisionWithShip(line collLine);
    bool isPlayerInShip();
    bool checkForPause();
    void endGameCheck();

    void addPlayer(string configFile);
    void addBullet(SDL_Rect rect, float angle);
    void addItem(ITEM type, coordinates coor);

    void shoot();


    void drawObject(SDL_Rect rect, SDL_Texture* texture);
    void drawObjectWithSrc(SDL_Rect dstRect, SDL_Rect srcRect, SDL_Texture* texture);



    void drawShipCollision(); //! Draw the collision lines of the spaceship

};