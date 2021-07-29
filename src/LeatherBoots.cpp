#include "LeatherBoots.h"
#include "ItemManager.h"
#include "World.h"
extern World world;

LeatherBoots::LeatherBoots()
{

}

LeatherBoots::LeatherBoots(const LeatherBoots* model)
{
	m_objectRect = model->m_objectRect;
	m_objectTexture = model->m_objectTexture;

	m_type = ITEM_TYPE::BOOTS;
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
	m_type = ITEM_TYPE::BOOTS;
}

void LeatherBoots::onPick(Player* player)
{
	applyEffect(player);

	ItemManager::equipItem(player, m_type, ITEM::LEATHER_BOOTS);
}

void LeatherBoots::applyEffect(Player* player)
{
	player->m_speed += m_movementBuff;
}