#pragma once

#include <utility>

#include <SDL.h>

#include "defines.h"

/*
* \brief input handler
* In order to use this class first you must init it from the World
* if you need any variable you can pass it by reference
* don't call SDL_PollEvent or SDL_GetKeyboardState anywhere else
*/

class InputManager
{
public:
	InputManager();
	~InputManager();

	bool m_mouseIsClicked;
	bool m_mouseIsDoubleClicked;
	Vector2 m_mouseCoor;
	Uint8* m_keyboardState;
	
	pair<bool, SDL_Scancode> m_up;
	pair<bool, SDL_Scancode> m_down;
	pair<bool, SDL_Scancode> m_left;
	pair<bool, SDL_Scancode> m_right;
protected:
	friend class World; //< this class should only be initialized by the world
	void setMouseMultiply(Vector2f multiplier); //< multiply the mouseCoor corespondingly to the screen resolution
	void handleInput(); //< call the SDL_PollEvent fnc and update all variables
	void init(string path); //< read the pre-set controlls in a configFile 
private:
	SDL_Event m_event;
	Vector2f m_mouseMultiply;
};