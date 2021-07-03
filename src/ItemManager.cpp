#include "ItemManager.h"
#include "World.h"
extern World world;

void ItemManager::equipItem(Player* player, ITEM_TYPE type, ITEM item)
{
	player->equipItem(type, item);
}

void ItemManager::applyItemEffect(Player* player, ITEM item)
{
	switch (item)
	{
	case ITEM::NONE:
		break;
	case ITEM::LEATHER_BOOTS:
		world.m_gameManager.m_configManager.m_leatherBoots.applyEffect(player);
		break;
	default:
		break;
	}
}