#pragma once

#include "Player.h"

class ItemManager
{
public:
protected:
	friend class LeatherBoots;
	static void equipItem(Player* player, ITEM_TYPE type, ITEM item);
	friend class Player;
	static void applyItemEffect(Player* player, ITEM item);
};