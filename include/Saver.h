#pragma once

#include <fstream>
#include <istream>

#include "Player.h"

using namespace std;

class Saver
{
public:
	Saver();
	Saver(string location, string playerInventoryLocation);
	~Saver();
	string m_location;
	string m_playerInventoryLocation;
	void saveSession();
	void loadSession();
	void savePlayerStats(Player* player);
	void loadPlayerStats(Player* player);
};