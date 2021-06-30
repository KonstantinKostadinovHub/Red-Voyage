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
struct mapcoordinates {

	short x;
	short y;
};

class CaveRoom
{
public:

	CaveRoom();
	virtual ~CaveRoom();

	string m_roomImg;
	string m_doors;

	bool isLinked;
	bool m_isUsed;

	hasDoors m_hasDoor;
	mapcoordinates m_mapCoor;

	SDL_Rect m_objRect;
	SDL_Texture* m_objTexture;

	void load(string configFile);
	void update();
	void draw();

	void encodeDoors();

	void changeX(int i);

	CaveRoom getNextRoom(CaveRoom &nextRoom);



};

