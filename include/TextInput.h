#pragma once

#include <fstream>

#include <SDL.h>

#include "Engine.h"
#include "defines.h"

using namespace std;

class TextInput
{
public:
	TextInput();
	virtual ~TextInput();

	void init(string configFile,SDL_Renderer* renderer, SDL_Event* event, Vector2* mouseCoor, bool* mouseIsPressed);
	void update();
	void draw();

	string getValue();
private:
	string m_container;
	SDL_Rect m_imgRect;
	SDL_Rect m_inputBox;
	SDL_Texture* m_texture;
	SDL_Renderer* m_renderer;
	bool m_typing;

	SDL_Event* m_event;
	Vector2* m_mouseCoor;
	bool* m_mouseIsPressed;
	time_t inputDelay, timeFromLastInput, startTime;

};