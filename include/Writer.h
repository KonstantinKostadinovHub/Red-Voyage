#pragma once

#include <fstream>

#include <SDL.h>
#include <SDL_TTF.h>

#include "defines.h"

using namespace std;

/**
* \class Get SDL_Texture* from string
* \brief Get SDL_Texture* form string by giving color, font size, font and more
* The class must be initialized with the init fnc in the World class.
* Use the getText fnc to get the SDL_Texture* that you need
* TIP: Use only for changing values, for static:
* use a software to create it and load it like a normal Texture
*/
class Writer
{
public:

	Writer();
	Writer(SDL_Renderer* renderer);
	~Writer();

	SDL_Renderer* m_renderer;

	SDL_Color m_orange;
	SDL_Color m_light;
	SDL_Color m_dark;

	string m_arcadeClassicLocation;

	void init(string config);

	SDL_Texture* getText(string text, FONT fontName, COLOR colorName, Uint8 fontSize);
};