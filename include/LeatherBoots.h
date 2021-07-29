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


	virtual void onPick(Player* player);
	virtual void init(string configFile);
protected:
	friend class ItemManager;
	void applyEffect(Player* player);
	short m_movementBuff;
};