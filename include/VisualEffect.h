#pragma once

#include <iostream>
#include <fstream>

#include <SDL.h>

#include "Animator.h"
#include "Engine.h"

using namespace std;

/*! \brief Used for creating particle effects after certain events
	
	A class used for explosions, steps after walking, dust effexts when 
	destroying an ore and many more!

	If You want to create a new VFX You want to create a new pointer to a new Visual Effect
	After that, call the init function, as parameters pass the configFile (check the void init  description)
	and also the m_main_renderer, which is in the world.
*/

class VisualEffect
{
public:
	VisualEffect();
	VisualEffect(const VisualEffect* model, Vector2 coor);
	virtual ~VisualEffect();

	SDL_Rect m_objectRect; //< The position of the vfx in the world
	SDL_Rect m_srcRect;
	SDL_Texture* m_texture;

	unsigned short m_inGameWidth, m_inGameHeight;

	animation* anim; //< The animation variable that changes the srcRect

	void init(string configFile);

	void draw();
};

