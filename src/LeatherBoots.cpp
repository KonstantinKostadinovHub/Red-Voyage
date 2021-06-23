#include "LeatherBoots.h"
#include "World.h"
extern World world;

LeatherBoots::LeatherBoots()
{

}

LeatherBoots::LeatherBoots(const LeatherBoots* model)
{
	m_objectRect = model->m_objectRect;
	m_objectTexture = model->m_objectTexture;
}

LeatherBoots::~LeatherBoots()
{

}

void LeatherBoots::init(string configFile)
{
	configFile = "config\\" + ITEM_FOLDER + configFile;

	fstream stream(configFile.c_str());

	string tmp, img;

	stream >> tmp >> m_objectRect.w >> m_objectRect.h;
	stream >> tmp >> img;
	stream >> tmp >> m_movementBuff;

	stream.close();

	m_objectTexture = LoadTexture(img, world.m_main_renderer);
}

void LeatherBoots::onPick(Player* player)
{
	player->m_speed += m_movementBuff;
}