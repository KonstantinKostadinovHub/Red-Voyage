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

void Cave::initEntrance(string config)
{
	config = "config\\" + config;

	ifstream stream;
	stream.open(config.c_str());

	string tmp;
	stream >> tmp >> m_img;
	stream >> tmp >> m_entranceRect.x >> m_entranceRect.y >> m_entranceRect.w >> m_entranceRect.h;

	stream.close();

	m_objectTexture = LoadTexture(m_img, world.m_main_renderer);


}

void Cave::init(string config)
{
	config = "config\\" + config;

	ifstream stream;
	stream.open(config.c_str());

	string tmp;
	stream >> tmp >> m_img;
	stream >> tmp >> m_entranceRect.x >> m_entranceRect.y >> m_entranceRect.w >> m_entranceRect.h;

	stream.close();

	m_objectTexture = LoadTexture(m_img, world.m_main_renderer);


}

void Cave::update()
{
	//cout << __LINE__ << endl;
}

void Cave::draw()
{
	SDL_RenderClear(world.m_main_renderer);
	//cout << __LINE__ << endl;
	SDL_RenderCopy(world.m_main_renderer, m_objectTexture, NULL, NULL);
	SDL_RenderPresent(world.m_main_renderer);
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
