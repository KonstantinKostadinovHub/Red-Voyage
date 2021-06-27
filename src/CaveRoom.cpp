#include "CaveRoom.h"

#include <fstream>

#include "World.h"
extern World world;

CaveRoom::CaveRoom()
{
	isLinked = false;
}

CaveRoom::~CaveRoom()
{
}

void CaveRoom::load(string configFile)
{
	configFile = "config\\" + ROOMS_FOLDER + configFile;

	ifstream stream;
	stream.open(configFile.c_str());

	string tmp;
	stream >> tmp >> m_roomImg;
	stream >> tmp >> m_hasDoor.top >> m_hasDoor.right >> m_hasDoor.bottom >> m_hasDoor.left;

	m_roomImg = ROOMS_FOLDER + m_roomImg;

	m_objRect.w = 108;
	m_objRect.h = 108;
	m_objRect.x = 300;
	m_objRect.y = 300;

	stream.close();

	m_objTexture = LoadTexture(m_roomImg, world.m_main_renderer);

}

void CaveRoom::update()
{
}

void CaveRoom::draw()
{
	SDL_RenderCopy(world.m_main_renderer, m_objTexture, NULL, &m_objRect);
}

void CaveRoom::encodeDoors()
{
	int r = rand() % 20;
	if (r >= 10) 
	{
		m_hasDoor.bottom = true;
	}
	else
	{
		m_hasDoor.bottom = false;
	}

	r = rand() % 20;
	if (r >= 10)
	{
		m_hasDoor.left = true;
	}
	else 
	{
		m_hasDoor.left = false;
	}

	r = rand() % 20;
	if (r >= 10)
	{
		m_hasDoor.right = true;
	}
	else 
	{
		m_hasDoor.right = false;
	}

	r = rand() % 20;
	if (r >= 10)
	{
		m_hasDoor.top = true;
	}
	else 
	{
		m_hasDoor.top = false;
	}

	if (!m_hasDoor.bottom && !m_hasDoor.left && !m_hasDoor.right && !m_hasDoor.top)
	{
		encodeDoors();
	}

	m_doors = "_" + to_string(m_hasDoor.top) + to_string(m_hasDoor.right) + to_string(m_hasDoor.bottom) + to_string(m_hasDoor.left);
	D(m_doors);
}

void CaveRoom::changeX(int i)
{
	m_objRect.x += i * m_objRect.w;
}

CaveRoom CaveRoom::getNextRoom(CaveRoom& nextRoom)
{
	isLinked = false;

	if (m_hasDoor.right && nextRoom.m_hasDoor.left)
	{
		nextRoom.m_objRect.x = m_objRect.x + m_objRect.w;
		isLinked = true;

	}else if (m_hasDoor.left && nextRoom.m_hasDoor.right)
	{

		nextRoom.m_objRect.x = m_objRect.x - nextRoom.m_objRect.w;
		isLinked = true;

	}else if(m_hasDoor.top && nextRoom.m_hasDoor.bottom)
	{

		nextRoom.m_objRect.y = m_objRect.y - nextRoom.m_objRect.h;
		isLinked = true;

	}
	else if (m_hasDoor.bottom && nextRoom.m_hasDoor.top)
	{

		nextRoom.m_objRect.y = m_objRect.y + m_objRect.h;
		isLinked = true;

	}

	return nextRoom;

}

