#pragma once

#include <SDL.h>

#include "Player.h"

/**
* \brief Pickable object that gives buff
* In order to use create new object, call the rewritten constructor and 
* set the coordinates with the setPos function
* Or just use the add item function in the GameManager
* 
* If you create a new class, that inherits Item simply overwrite onPick and init
* Add all the variables that you will need
* Add a new type to the enumerator in defines
*/

class Item
{
public: 
	Item();
	Item(const Item* modelItem);
	virtual ~Item();
	
	SDL_Rect getRect(); //< A getter that is used to protect the jectRect of the object
	virtual void onPick(Player* player); //< The impact of the item after it is picked
	virtual void init(string configFile);
	void setPos(coordinates pos); //< Use after the initialization of the object
	void draw();
protected:
	SDL_Rect m_objectRect;
	SDL_Texture* m_objectTexture;
};