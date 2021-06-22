#pragma once

#include <iostream>
#include <string>
#include <SDL.h>
#include <vector>

#include "defines.h"
#include "Engine.h"

#include "CaveRoom.h"

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

using namespace std;

class Cave
{

	public:

		Cave();
		virtual ~Cave();

		int m_roomCount;
		
		string m_img;

		SDL_Rect m_objectRect;
		SDL_Rect m_entranceRect;
		SDL_Texture* m_objectTexture;
		SDL_Texture* m_entranceTexture;

		vector<CaveRoom*> m_rooms;

		bool m_isInCave;

		void init(string config);
		void initSession();
		void deleteSession();
		void initEntrance(string config);
		void update();
		void draw();

		void updateEntrance();
		void drawEntrance();

		void checkForCaveEnter( bool& m_isInCave);

		void loadAllRoooms();
		void getNextRoom();

		


};

