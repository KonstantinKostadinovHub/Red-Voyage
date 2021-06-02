#pragma once

#include <iostream>
#include <string>
#include <SDL.h>

#include "defines.h"
#include "Engine.h"

using namespace std;

class Cave
{

	public:

		Cave();
		~Cave();
		
		string m_img;

		SDL_Rect m_objectRect;
		SDL_Rect m_entranceRect;
		SDL_Texture* m_objectTexture;

		bool m_isInCave;

		void init(string config);
		void update();
		void draw();

		void checkForCaveEnter( bool& m_isInCave);

		


};

