#pragma once
#include<SDL.h>
#include<string>

#include "Engine.h"

using namespace std;

struct hasDoors{

	bool top;
	bool right;
	bool bottom;
	bool left;
};
struct DoorRect {

	SDL_Rect m_topRect;
	SDL_Rect m_rightRect;
	SDL_Rect m_bottomRect;
	SDL_Rect m_leftRect;

};
struct mapcoordinates {

	short x;
	short y;
};

class CaveRoom
{
public:

	CaveRoom();
	virtual ~CaveRoom();

	int m_standartDoorWidth;

	string m_roomImg;
	string m_doors;

	bool isLinked;
	bool m_isUsed;
	bool m_isDefeated;

	hasDoors m_hasDoor;
	DoorRect doors;
	mapcoordinates m_mapCoor;

	SDL_Rect m_objRect;
	SDL_Texture* m_objTexture;

	void load(string configFile);
	void update();
	void draw();

};

