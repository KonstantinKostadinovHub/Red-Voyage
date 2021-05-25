#ifndef CHICKENBUFF_H
#define CHICKENBUFF_H

#include <SDL.h>
#include <iostream>
#include <fstream>
#include <ctime>

#include "PowerUp.h"
#include "Player.h"

using namespace std;

class ChickenBuff : public PowerUp
{
public:
	ChickenBuff();
	ChickenBuff(const ChickenBuff* model);
	virtual ~ChickenBuff();

	void init(string config);
	void applyEffect();

	int healPerSecond;
	int duration;

	bool checkForApply();

	Player* player;

	time_t m_startEffect, m_lastHealthAdded;

};

#endif