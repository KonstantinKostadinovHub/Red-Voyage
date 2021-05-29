#include "Saver.h"

#include "World.h"

extern World world;

Saver::Saver()
{
}


Saver::~Saver()
{
}

void Saver::saveSession()
{
	fstream stream;
	int i;
	stream.open(m_location.c_str());

	for (i = 0; i < world.m_players.size(); i++)
	{
		stream << world.m_players[i]->m_configFile << " " << world.m_players[i]->m_health << " " << world.m_players[i]->m_maxHealth << " " << world.m_players[i]->m_objRect.x << " " << world.m_players[i]->m_objRect.y << endl;
	}
	//TO-DO finish the saveSession function
	stream.close();
}