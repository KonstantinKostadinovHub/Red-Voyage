#ifndef WORLD_H
#define WORLD_H

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

using namespace std;

/*	\brief Responsible for handling the game
	
	Generating the main window and renderer.
	Handling the update of all objects and their drawing.
	Cleaning all the used/dead objects in the scene.
*/
class World
{
    public:
        World();
        virtual ~World();

        SDL_Renderer* m_main_renderer;
        SDL_Window* m_main_window;

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
        int m_SCREEN_WIDTH;
        int m_SCREEN_HEIGHT;
        int m_chickenCollected = 0;
        int m_aluminiumCollected = 0;
        int m_titaniumCollected = 0;
        int m_ironCollected = 0;

        bool buffBool;

        Camera m_camera;
        coordinates m_mouseCoordinates;
        coordinates m_directionCoor;

        double m_MOUSE_MULTIPLY_X;
        double m_MOUSE_MULTIPLY_Y;

        float m_angle;

        bool m_mouseIsPressed;
        bool m_mouseIsDoubleClicked;
        bool m_isPaused;

        SDL_Event m_event;

        Endgame endgame;
        Credits credits;
        Menu m_menu;
        ConfigManager m_configManager;
        Generator m_generator;
        SoundManager* m_soundManager;
        Food m_food_spawner;
        ChickenWing* chicken_wings[6];
        Animator m_animator;
        Tutorial m_tutorial;
		Helper* m_helper;
        Saver* m_saver;

        vector <line> m_collLines;
		vector <Player*> m_players;
		vector <Bullet*> m_bullets;
		vector <Enemy*> m_enemies;
		vector <EnemyBullet*> m_enemyBullets;
		vector <Task*> m_tasks;
		vector <Ore*> m_ores;
		vector <VisualEffect*> m_vfxs;
		vector <PowerUp*> m_powerUps;

        line m_door;

        UI m_userInterface;

        bool m_quitScene;
        bool m_endGame;
        bool m_drag;

        GAME_STATE m_gameState;

		string m_backgroundImg = " ";

        void init();
        void input();
        void improveRenderer();
        void update();
        void draw();
        void destroy();
        void cleaner();
        void initSession();

        void readCollisionPoints(string configFile);
        bool collisionWithShip(SDL_Rect rect);
        bool collisionWithShip(line collLine);
        bool isPlayerInShip();

        void addPlayer(string configFile);
        void addBullet(SDL_Rect rect, coordinates coor);
        void shoot();
        void deleteSession();

        void endGameCheck();

        void drawObject(SDL_Rect rect, SDL_Texture* texture);
        void drawObjectWithSrc(SDL_Rect dstRect,SDL_Rect srcRect, SDL_Texture* texture);

        void collision();

        bool checkForPause();

		void drawShipCollision(); //! Draw the collision lines of the spaceship

    protected:

    private:
};

#endif // WORLD_H
