#include "PowerUp.h"



PowerUp::PowerUp()
{
}


PowerUp::~PowerUp()
{
}

void PowerUp::load(string configFile)
{
	// load the information, required for the powerUp
}

bool PowerUp::checkForApply()
{
	// check if all the requirements for applying the effect are fulfilled
	return false;
}

void PowerUp::applyEffect()
{
	// apply the effect
}

void PowerUp::update()
{
	m_applyEffect = checkForApply();
	if (m_applyEffect)
	{
		applyEffect();
	}
}

void PowerUp::draw()
{
	// draw
}