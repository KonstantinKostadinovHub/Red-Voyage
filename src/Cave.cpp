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
	world.m_gameManager.addPlayer("player1.txt");
	//D("Player1");
	world.m_gameManager.addPlayer("player2.txt");
	//D("Player2");


	world.m_gameManager.m_userInterface.load("ui.txt");


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

void Cave::initEntrance(string config)
{
	config = "config\\" + config;

	ifstream stream;
	stream.open(config.c_str());

	string tmp;
	stream >> tmp >> m_img;
	stream >> tmp >> m_entranceRect.x >> m_entranceRect.y >> m_entranceRect.w >> m_entranceRect.h;
	D(m_entranceRect.w);
	D(m_entranceRect.x);

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
	D(m_roomCount);

	stream.close();

	loadAllRoooms();


	m_objectTexture = LoadTexture(m_img, world.m_main_renderer);


}

void Cave::update()
{
	//cout << __LINE__ << endl;
	for (int i = 0; i < m_roomFlow.size(); i++)
	{
		m_roomFlow[i]->update();

	}

	for (int i = 0; i < world.m_gameManager.m_players.size(); i++)
	{
		world.m_gameManager.m_players[i]->update();
	}
	world.m_gameManager.m_userInterface.update();
}

void Cave::draw()
{
	SDL_RenderClear(world.m_main_renderer);


	SDL_RenderCopy(world.m_main_renderer, m_objectTexture, NULL, NULL);

	
	for (int i = 0; i < m_roomFlow.size(); i++)
	{

		m_roomFlow[i]->draw();
		coordinates coor;
		coor.x = m_roomFlow[i]->m_objRect.x + m_roomFlow[i]->m_objRect.w / 3;
		coor.y = m_roomFlow[i]->m_objRect.y + m_roomFlow[i]->m_objRect.h / 3;
		D(coor.x);
		D(coor.y);
		write(to_string(i), coor, world.m_main_renderer, 50);
		D(i);

	}

	for (int i = 0; i < m_roomCount; i++)
	{

		m_rooms[i]->draw();
		coordinates coor;
		coor.x = m_rooms[i]->m_objRect.x + m_rooms[i]->m_objRect.w/3;
		coor.y = m_rooms[i]->m_objRect.y + m_rooms[i]->m_objRect.h/3;
		write(to_string(i), coor, world.m_main_renderer , 50);

	}


	for (int i = 0; i < world.m_gameManager.m_players.size(); i++)
	{
		world.m_gameManager.m_players[i]->draw();
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

	CaveRoom* room;
	for (int i = 0; i < m_roomCount; i++)
	{
		room = new CaveRoom();
		room->load("cave_room.txt");

		room->randomiseExits();
		m_rooms.push_back(room);

		if (room->m_hasDoor.bottom)
		{
			m_roomsBottom.push_back(room);
		}
		if (room->m_hasDoor.top)
		{
			m_roomsTop.push_back(room);
		}
		if (room->m_hasDoor.left)
		{
			m_roomsLeft.push_back(room);
		}
		if (room->m_hasDoor.right)
		{
			m_roomsRight.push_back(room);
		}

	}

	vector<CaveRoom*> m_suitableRooms;

	for (int i = 0; i < m_roomCount; i++)
	{
		if (m_rooms[i]->m_hasDoor.right)
		{
			int r = rand() % m_roomsRight.size();

			m_roomFlow.push_back(m_roomsRight[r]);
		}
		if (m_rooms[i]->m_hasDoor.left)
		{
			int r = rand() % m_roomsLeft.size();
			m_roomFlow.push_back(m_roomsLeft[r]);
		}
		if (m_rooms[i]->m_hasDoor.top)
		{
			int r = rand() % m_roomsTop.size();

			m_roomFlow.push_back(m_roomsTop[r]);
		}
		if (m_rooms[i]->m_hasDoor.bottom)
		{
			int r = rand() % m_roomsBottom.size();
			m_roomFlow.push_back(m_roomsBottom[r]);
		}

		

	}

}

