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

#pragma region CAVEROOM_ESSENTIALS
void CaveRoom::load(string configFile)
{
	configFile = "config\\" + ROOMS_FOLDER + configFile;

	ifstream stream;
	stream.open(configFile.c_str());

	string tmp;
	stream >> tmp >> m_roomImg;
	stream >> tmp >> m_hasDoor.top >> m_hasDoor.right >> m_hasDoor.bottom >> m_hasDoor.left;

	m_roomImg = ROOMS_FOLDER + m_roomImg;

	m_objRect.w = 1080;
	m_objRect.h = 1080;
	m_objRect.x = (1920 - 1080) / 2;
	m_objRect.y = 0;

	m_standartDoorWidth = 200;


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
#pragma endregion