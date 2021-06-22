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


void Cave::initSession()
{
	world.addPlayer("player1.txt");
	//D("Player1");
	world.addPlayer("player2.txt");
	//D("Player2");


	world.m_userInterface.load("ui.txt");


	world.m_helper = new Helper(&world.m_players, world.m_main_renderer, &(world.m_camera.zoom_lvl), &(world.m_camera.camera_rect), &world.m_bullets);

}
void Cave::deleteSession()
{
	/*! After a session is used, delete all the objects in order to save memory.

	*/
	for (int i = 0; i < world.m_players.size(); i++)
	{
		delete  world.m_players[i];
	}
	world.m_players.clear();

	for (int i = 0; i < world.m_enemies.size(); i++)
	{
		delete  world.m_enemies[i];
	}
	world.m_enemies.clear();

	for (int i = 0; i < world.m_bullets.size(); i++)
	{
		delete  world.m_bullets[i];
	}
	world.m_bullets.clear();

	for (int i = 0; i < world.m_enemyBullets.size(); i++)
	{
		delete  world.m_enemyBullets[i];
	}
	world.m_enemyBullets.clear();


	for (int i = 0; i < world.m_ores.size(); i++)
	{
		delete  world.m_ores[i];
	}
	world.m_ores.clear();

	for (int i = 0; i < world.m_animator.m_animations.size(); i++)
	{
		delete   world.m_animator.m_animations[i];
	}
	world.m_animator.m_animations.clear();

	for (int i = 0; i < world.m_vfxs.size(); i++)
	{
		delete  world.m_vfxs[i];
	}
	world.m_vfxs.clear();

	for (int i = 0; i < world.m_powerUps.size(); i++)
	{
		delete  world.m_powerUps[i];
	}
	world.m_powerUps.clear();

	world.m_ironCollected = 0;
	world.m_chickenCollected = 0;
	world.m_aluminiumCollected = 0;
	world.m_titaniumCollected = 0;

	world.m_isPaused = false;
}

void Cave::initEntrance(string config)
{
	config = "config\\" + config;

	ifstream stream;
	stream.open(config.c_str());

	string tmp;
	stream >> tmp >> m_img;
	stream >> tmp >> m_entranceRect.x >> m_entranceRect.y >> m_entranceRect.w >> m_entranceRect.h;
	D(m_entranceRect.w);

	stream.close();

	m_entranceTexture = LoadTexture(m_img, world.m_main_renderer);


}

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


	m_objectTexture = LoadTexture(m_img, world.m_main_renderer);


}

void Cave::update()
{
	//cout << __LINE__ << endl;
	for (int i = 0; i < m_roomCount; i++)
	{
		m_rooms[i]->update();

	}

	for (int i = 0; i < world.m_players.size(); i++)
	{
		world.m_players[i]->update();
	}
	world.m_userInterface.update();
}

void Cave::draw()
{
	SDL_RenderClear(world.m_main_renderer);


	SDL_RenderCopy(world.m_main_renderer, m_objectTexture, NULL, NULL);

	for (int i = 0; i < m_roomCount; i++)
	{
		
		m_rooms[i]->draw();

	}


	for (int i = 0; i < world.m_players.size(); i++)
	{
		world.m_players[i]->draw();
	}



	SDL_RenderPresent(world.m_main_renderer);
}
void Cave::updateEntrance()
{
	checkForCaveEnter(m_isInCave);
	//D(m_entranceRect.x);
}
void Cave::drawEntrance()
{
	//SDL_RenderClear(world.m_main_renderer);


	SDL_RenderCopy(world.m_main_renderer, m_entranceTexture, NULL, &m_entranceRect);


	//SDL_RenderPresent(world.m_main_renderer);


}


void Cave::checkForCaveEnter(bool& m_isInCave)
{
	for (int i = 0; i < world.m_players.size(); i++)
	{
		if (collRectRect(world.m_players[i]->m_objRect , m_entranceRect))
		{
			m_isInCave = true;
		}
	}
}

void Cave::loadAllRoooms()
{

	CaveRoom* room;
	for (int i = 0; i < m_roomCount; i++)
	{
		room = new CaveRoom();
		room->load("cave_room.txt");
		room->randomiseExits();
		m_rooms.push_back(room);
		if (i + 1 < m_roomCount) {
			world.m_gameState = MENU;
			world.m_quitScene = true;
			/*m_rooms[i+1] =*/ room->getNextRoom();
			world.m_quitScene = true;
		}
	}

}

void Cave::getNextRoom()
{

		

}
