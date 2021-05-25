#pragma once

#include <SDL.h>
#include <fstream>

using namespace std;

/*!
	\brief The main class for all buffs and items

	A class that is responsible for applying positive and negative effects to the player or the enemies.
	
	If you want to make a new item or effect:
	- make sure that your class inherits this one
	- add all the parameters that you need
	- change the checkForApply() and applyEffect() functions
*/

class PowerUp
{
public:
	PowerUp();
	~PowerUp();

	bool m_applyEffect; //< Check if the effect should be applied or not
	bool m_destroyEffect; //< Check if we should remove the effect

	string m_effectName; 

	virtual void load(string configFile);
	virtual bool checkForApply(); //< Change the m_applyEffect variable if needed
	virtual void applyEffect(); //< Apply the effect of the powerUp
	void update();
	void draw();
};

