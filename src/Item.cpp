#include "Item.h"

#include "World.h"
extern World world;

Item::Item()
{

}

Item::Item(const Item* model)
{
	/// Read the common params from the model
	m_objectRect = model->m_objectRect;
	m_objectTexture = model->m_objectTexture;
}

Item::~Item()
{

}

void Item::init(string configFile)
{
	/// Initalize the model
}

void Item::onPick(Player* player)
{
	/// The action that will be performed then the item is picked
	/// Overwrite this function when inheriting
}

void Item::setPos(coordinates coor)
{
	m_objectRect.x = coor.x;
	m_objectRect.y = coor.y;
}

void Item::draw()
{
	world.m_gameManager.drawObject(m_objectRect, m_objectTexture);
}