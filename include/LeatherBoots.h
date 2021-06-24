#pragma once

#include "Item.h"

/* 
* \brief Item, giving the player small, but permanent movement boost
*/

class LeatherBoots : public Item
{
public:
	LeatherBoots();
	LeatherBoots(const LeatherBoots* model);
	~LeatherBoots();

	short m_movementBuff;

	virtual void onPick(Player* player);
	virtual void init(string configFile);
};