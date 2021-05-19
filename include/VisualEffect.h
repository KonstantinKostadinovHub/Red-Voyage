#pragma once

#include <iostream>
#include <fstream>

#include <SDL.h>

#include "Animator.h"

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
	virtual ~VisualEffect();

	SDL_Rect m_objectRect;
	SDL_Rect m_srcRect;
	SDL_Texture* m_texture;

	void init(string configFile, SDL_Renderer* renderer);
};

