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
	applyEffect(player); /// Don't forget to call this function when inhereting
	/// The action that will be performed then the item is picked
	/// Overwrite this function when inheriting
}

SDL_Rect Item::getRect()
{
	return m_objectRect;
}

void Item::setPos(Vector2 coor)
{
	m_objectRect.x = coor.x;
	m_objectRect.y = coor.y;
}

void Item::draw()
{
	world.m_gameManager.drawObject(m_objectRect, m_objectTexture);
}

void Item::applyEffect(Player* player)
{
	/// Here you should type the effect that is applied to the player
}