#pragma once

#include <vector>

#include "Engine.h"
#include "Player.h"
#include "Bullet.h"

using namespace std;

/*! \brief Helps for debugging. Give us much resources, health, damage speed and more

	This class can help for debbuging. It is made to draw hitboxes, give us health, damage and speed if needed.
	
	If you want to use it, go to the constructor and make the bools, that you need, true
*/

class Helper
{
public:
	Helper();
	Helper(vector<Player*>* players, SDL_Renderer* renderer, float* zoom, SDL_Rect* camera, vector<Bullet*>* bullets);
	
	virtual ~Helper();

	void update();

	void drawCollision(SDL_Rect rect); //< Draw the collision box of an object by passing it's rect

	bool SHOW_ALL_RECTS;
	bool MAX_ORES;

private:
	SDL_Renderer* m_renderer;

	vector<Player*>* m_players; //< Pointer to the vector with players in the World
	vector<Bullet*>* m_bullets; //< Pointer to the vector with bullets in the World

	bool MAX_HEALTH;
	bool MAX_DAMAGE;
	bool MAX_SPEED;

	SDL_Rect* cameraRect;
	float* zoom_lvl;
};

