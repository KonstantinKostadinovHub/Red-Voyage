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
	configFile = "config\\" + configFile;

	ifstream stream;
	stream.open(configFile.c_str());

	string tmp;
	stream >> tmp >> m_roomImg;
	stream >> tmp >> m_objRect.w >> m_objRect.h >> m_objRect.x >> m_objRect.y;

	stream.close();

	m_objTexture = LoadTexture(m_roomImg, world.m_main_renderer);

}

void CaveRoom::update()
{
}

void CaveRoom::draw()
{
	//SDL_RenderClear(world.m_main_renderer);
	SDL_RenderCopy(world.m_main_renderer, m_objTexture, NULL, &m_objRect);
	//SDL_RenderPresent(world.m_main_renderer);
}

void CaveRoom::randomiseExits()
{
	//cout << "----------------------------\n";
	int r = rand() % 20;
	if (r >= 10) 
	{
		m_hasDoor.bottom = true;
	}
	else {
		m_hasDoor.bottom = false;
	}
	//D(m_hasDoor.bottom);

	r = rand() % 20;
	if (r >= 10)
	{
		m_hasDoor.left = true;
	}
	else {
		m_hasDoor.left = false;
	}
	//D(m_hasDoor.left);

	r = rand() % 20;
	if (r >= 10)
	{
		m_hasDoor.right = true;
	}
	else {
		m_hasDoor.right = false;
	}
	//D(m_hasDoor.right);

	r = rand() % 20;
	if (r >= 10)
	{
		m_hasDoor.top = true;
	}
	else {
		m_hasDoor.top = false;
	}
	///D(m_hasDoor.top);

	if (!m_hasDoor.bottom && !m_hasDoor.left && !m_hasDoor.right && !m_hasDoor.top)
	{
		randomiseExits();
	}

}

void CaveRoom::changeX(int i)
{

	m_objRect.x += i * m_objRect.w;

}

CaveRoom CaveRoom::getNextRoom(CaveRoom& nextRoom)
{
	//CaveRoom* nullRoom = NULL;
	/*D(m_objRect.x);
	D(m_objRect.y);

	D(m_hasDoor.right);
	D(m_hasDoor.left);
	D(m_hasDoor.top);
	D(m_hasDoor.bottom);


	D(nextRoom.m_hasDoor.right);
	D(nextRoom.m_hasDoor.left);
	D(nextRoom.m_hasDoor.top);
	D(nextRoom.m_hasDoor.bottom);*/

	isLinked = false;

	nextRoom.m_objRect.x = m_objRect.x + m_objRect.w;
	nextRoom.m_objRect.y = m_objRect.y + m_objRect.h;

	if (m_hasDoor.right && nextRoom.m_hasDoor.left)
	{

		nextRoom.m_objRect.x = m_objRect.x + m_objRect.w;
		isLinked = true;
		//D("RIGHT");

	}else if (m_hasDoor.left && nextRoom.m_hasDoor.right)
	{

		nextRoom.m_objRect.x = m_objRect.x - nextRoom.m_objRect.w;
		isLinked = true;
		//D("LEFT");

	}else if(m_hasDoor.top && nextRoom.m_hasDoor.bottom)
	{

		nextRoom.m_objRect.y = m_objRect.y - nextRoom.m_objRect.h;
		isLinked = true;
		//D("TOP");

	}
	else if (m_hasDoor.bottom && nextRoom.m_hasDoor.top)
	{

		nextRoom.m_objRect.y = m_objRect.y + m_objRect.h;
		isLinked = true;
		//D("BOTTOM");

	}
	//cout << " -----------------------------\n ";
	//D(isLinked);
	/*cout << " -----------------------------\n ";
	D(nextRoom.m_objRect.x);
	D(nextRoom.m_objRect.y);*/
	return nextRoom;

}

