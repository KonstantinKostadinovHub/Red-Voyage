#include "Cave.h"

#include <fstream>

#include "World.h"
extern World world;

Cave::Cave()
{
	m_isInCave = false;
}

Cave::~Cave()
{

}

#pragma region SESSION_CONTROL
void Cave::initSession()
{
	world.m_gameManager.addPlayer("player1.txt");
	//world.m_gameManager.addPlayer("player2.txt");


	world.m_gameManager.m_userInterface.load("ui.txt");

	//world.m_gameManager.m_camera.init(&(world.m_gameManager.m_players[0]->m_objRect), &(world.m_gameManager.m_players[1]->m_objRect));


	world.m_gameManager.m_helper = new Helper(&world.m_gameManager.m_players, world.m_main_renderer, &(world.m_gameManager.m_camera.zoom_lvl), &(world.m_gameManager.m_camera.camera_rect), &world.m_gameManager.m_bullets);

}
void Cave::deleteSession()
{
	/*! After a session is used, delete all the objects in order to save memory.

	*/
	for (int i = 0; i < world.m_gameManager.m_players.size(); i++)
	{
		delete  world.m_gameManager.m_players[i];
	}
	world.m_gameManager.m_players.clear();

	for (int i = 0; i < world.m_gameManager.m_enemies.size(); i++)
	{
		delete  world.m_gameManager.m_enemies[i];
	}
	world.m_gameManager.m_enemies.clear();

	for (int i = 0; i < world.m_gameManager.m_bullets.size(); i++)
	{
		delete  world.m_gameManager.m_bullets[i];
	}
	world.m_gameManager.m_bullets.clear();

	for (int i = 0; i < world.m_gameManager.m_enemyBullets.size(); i++)
	{
		delete  world.m_gameManager.m_enemyBullets[i];
	}
	world.m_gameManager.m_enemyBullets.clear();


	for (int i = 0; i < world.m_gameManager.m_ores.size(); i++)
	{
		delete  world.m_gameManager.m_ores[i];
	}
	world.m_gameManager.m_ores.clear();

	for (int i = 0; i < world.m_gameManager.m_animator.m_animations.size(); i++)
	{
		delete   world.m_gameManager.m_animator.m_animations[i];
	}
	world.m_gameManager.m_animator.m_animations.clear();

	for (int i = 0; i < world.m_gameManager.m_vfxs.size(); i++)
	{
		delete  world.m_gameManager.m_vfxs[i];
	}
	world.m_gameManager.m_vfxs.clear();

	for (int i = 0; i < world.m_gameManager.m_powerUps.size(); i++)
	{
		delete  world.m_gameManager.m_powerUps[i];
	}
	world.m_gameManager.m_powerUps.clear();

	world.m_gameManager.m_ironCollected = 0;
	world.m_gameManager.m_chickenCollected = 0;
	world.m_gameManager.m_aluminiumCollected = 0;
	world.m_gameManager.m_titaniumCollected = 0;

	world.m_gameManager.m_isPaused = false;
}
#pragma endregion

#pragma region CAVE_ESSENTIALS
void Cave::init(string config)
{
	config = "config\\" + config;

	ifstream stream;
	stream.open(config.c_str());

	string tmp,buff;
	stream >> tmp >> m_img;
	stream >> tmp >> m_roomCount;
	stream >> tmp >> buff;

	stream.close();

	loadAllRoooms();

	world.m_gameManager.m_camera.zoom_lvl = 1;

	m_roomFlow.push_back(m_rooms[0]);

	m_objectTexture = LoadTexture(m_img, world.m_main_renderer);


}

void Cave::update()
{
	
	m_roomFlow[m_roomFlow.size() - 1]->update();


	for (int i = 0; i < world.m_gameManager.m_players.size(); i++)
	{
		world.m_gameManager.m_players[i]->update();

		///Went trough right door check
		if (collRectRect(world.m_gameManager.m_players[i]->m_objRect, 
			m_roomFlow[m_roomFlow.size() - 1]->doors.m_rightRect))
		{
			int r = rand() % m_roomsLeft.size();
			//D(m_roomsLeft.size() - 1);
			D("Go Right");
			m_roomFlow.push_back(m_roomsLeft[r]);
			world.m_gameManager.m_players[i]->m_objRect.x = 1920 / 2;
			world.m_gameManager.m_players[i]->m_objRect.y = 1080 / 2;

		}
		///Went trough bottom door check
		if (collRectRect(world.m_gameManager.m_players[i]->m_objRect,
			m_roomFlow[m_roomFlow.size() - 1]->doors.m_bottomRect))
		{
			int r = rand() % m_roomsTop.size();
			//D(m_roomsTop.size() - 1);
			D("Go Bottom");
			m_roomFlow.push_back(m_roomsTop[r]);
			world.m_gameManager.m_players[i]->m_objRect.x = 1920 / 2;
			world.m_gameManager.m_players[i]->m_objRect.y = 1080 / 2;

		}
		///Went trough left door check
		if (collRectRect(world.m_gameManager.m_players[i]->m_objRect,
			m_roomFlow[m_roomFlow.size() - 1]->doors.m_leftRect))
		{
			int r = rand() % m_roomsRight.size();
			//D(m_roomsRight.size() - 1);
			D("Go Left");
			m_roomFlow.push_back(m_roomsRight[r]);
			world.m_gameManager.m_players[i]->m_objRect.x = 1920 / 2;
			world.m_gameManager.m_players[i]->m_objRect.y = 1080 / 2;

		}
		///Went trough top door check
		if (collRectRect(world.m_gameManager.m_players[i]->m_objRect,
			m_roomFlow[m_roomFlow.size() - 1]->doors.m_topRect))
		{
			int r = rand() % m_roomsBottom.size();
			//D(m_roomsBottom.size() - 1);
			D("Go Top");
			m_roomFlow.push_back(m_roomsBottom[r]);
			world.m_gameManager.m_players[i]->m_objRect.x = 1920 / 2;
			world.m_gameManager.m_players[i]->m_objRect.y = 1080 / 2;

		}
	}

	world.m_gameManager.m_userInterface.update();
}

void Cave::draw()
{
	SDL_RenderClear(world.m_main_renderer);

	SDL_RenderCopy(world.m_main_renderer, m_objectTexture, NULL, NULL);

	m_roomFlow[m_roomFlow.size()-1]->draw();

	for (int i = 0; i < world.m_gameManager.m_players.size(); i++)
	{
		world.m_gameManager.m_players[i]->draw();
	}

	if (world.m_gameManager.m_helper->SHOW_ALL_RECTS)
	{
		for (int i = 0; i < m_rooms.size(); i++)
		{
			world.m_gameManager.m_helper->drawCollision(m_rooms[i]->doors.m_bottomRect);
			world.m_gameManager.m_helper->drawCollision(m_rooms[i]->doors.m_topRect);
			world.m_gameManager.m_helper->drawCollision(m_rooms[i]->doors.m_rightRect);
			world.m_gameManager.m_helper->drawCollision(m_rooms[i]->doors.m_leftRect);

		}
	}


	SDL_RenderPresent(world.m_main_renderer);
}
#pragma endregion

#pragma region CAVE_ENTRANCE_ESSENTIALS

void Cave::initEntrance(string config)
{
	config = "config\\" + config;

	ifstream stream;
	stream.open(config.c_str());

	string tmp;
	stream >> tmp >> m_img;
	stream >> tmp >> m_entranceRect.x >> m_entranceRect.y >> m_entranceRect.w >> m_entranceRect.h;

	stream.close();

	m_entranceTexture = LoadTexture(m_img, world.m_main_renderer);


}

void Cave::updateEntrance()
{
	checkForCaveEnter(m_isInCave);
}

void Cave::drawEntrance()
{
	world.m_gameManager.drawObject(m_entranceRect, m_entranceTexture);
}
#pragma endregion

void Cave::checkForCaveEnter(bool& m_isInCave)
{
	for (int i = 0; i < world.m_gameManager.m_players.size(); i++)
	{
		if (collRectRect(world.m_gameManager.m_players[i]->m_objRect , m_entranceRect))
		{
			m_isInCave = true;
		}
	}
}

void Cave::loadAllRoooms()
{

	for (int i = 0; i < 15; i++)
	{
		
		if (m_rooms[i]->m_hasDoor.bottom)
		{
			m_roomsBottom.push_back(m_rooms[i]);

			m_rooms[i]->doors.m_bottomRect.w = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_bottomRect.h = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_bottomRect.x = (1920 - m_rooms[i]->doors.m_bottomRect.w)/2;
			m_rooms[i]->doors.m_bottomRect.y = (1080 - m_rooms[i]->doors.m_bottomRect.h);

			D(m_rooms[i]->doors.m_bottomRect.w);
			D(m_rooms[i]->doors.m_bottomRect.h);
			D(m_rooms[i]->doors.m_bottomRect.x);
			D(m_rooms[i]->doors.m_bottomRect.y);

			//D(m_rooms[i]->m_roomImg);
			D("Pushed in bottom");
		}
		if (m_rooms[i]->m_hasDoor.top)
		{
			m_roomsTop.push_back(m_rooms[i]);

			m_rooms[i]->doors.m_topRect.w = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_topRect.h = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_topRect.x = (1920 - m_rooms[i]->doors.m_topRect.w)/2;
			m_rooms[i]->doors.m_topRect.y = 0;

			D(m_rooms[i]->doors.m_topRect.w);
			D(m_rooms[i]->doors.m_topRect.h);
			D(m_rooms[i]->doors.m_topRect.x);
			D(m_rooms[i]->doors.m_topRect.y);

			//D(m_rooms[i]->m_roomImg);
			D("Pushed in top");
		}
		if (m_rooms[i]->m_hasDoor.left)
		{

			m_roomsLeft.push_back(m_rooms[i]);

			m_rooms[i]->doors.m_leftRect.w = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_leftRect.h = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_leftRect.x = 0 + (1920 - 1080) / 2;
			m_rooms[i]->doors.m_leftRect.y = (1080 - m_rooms[i]->doors.m_leftRect.h) / 2;

			D(m_rooms[i]->doors.m_leftRect.w);
			D(m_rooms[i]->doors.m_leftRect.h);
			D(m_rooms[i]->doors.m_leftRect.x);
			D(m_rooms[i]->doors.m_leftRect.y);

			//D(m_rooms[i]->m_roomImg);
			D("Pushed in left");
		}
		if (m_rooms[i]->m_hasDoor.right)
		{
			m_roomsRight.push_back(m_rooms[i]);

			m_rooms[i]->doors.m_rightRect.w = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_rightRect.h = m_rooms[i]->m_standartDoorWidth;
			m_rooms[i]->doors.m_rightRect.x = (1920 - m_rooms[i]->doors.m_rightRect.w) - (1920 - 1080) / 2;
			m_rooms[i]->doors.m_rightRect.y = (1080 - m_rooms[i]->doors.m_rightRect.h) / 2;

			D(m_rooms[i]->doors.m_rightRect.w);
			D(m_rooms[i]->doors.m_rightRect.h);
			D(m_rooms[i]->doors.m_rightRect.x);
			D(m_rooms[i]->doors.m_rightRect.y);

			//D(m_rooms[i]->m_roomImg);
			D("Pushed in right");
		}
		D("-----------------");
	}
}



