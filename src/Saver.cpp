#include "Saver.h"

#include "World.h"

extern World world;

Saver::Saver()
{
}

Saver::Saver(string location)
{
	m_location = location;
}

Saver::~Saver()
{
}

void Saver::saveSession()
{
	int i;
	ofstream stream(m_location);
	
	for (i = 0; i < world.m_players.size(); i++)
	{
		stream << "Player "  << world.m_players[i]->m_health << " " << world.m_players[i]->m_maxHealth << " " << world.m_players[i]->m_objRect.x << " " << world.m_players[i]->m_objRect.y << endl;
		cout << "Player " << world.m_players[i]->m_health << " " << world.m_players[i]->m_maxHealth << " " << world.m_players[i]->m_objRect.x << " " << world.m_players[i]->m_objRect.y << endl;

	}
	for (i = 0; i < world.m_enemies.size(); i++)
	{
		stream << "Enemy " << (int)world.m_enemies[i]->m_type << " " << world.m_enemies[i]->m_health << " " << world.m_enemies[i]->m_objectRect.x << " " << world.m_enemies[i]->m_objectRect.y << endl;
		cout << "Enemy " << (int)world.m_enemies[i]->m_type << " " << world.m_enemies[i]->m_health << " " << world.m_enemies[i]->m_objectRect.x << " " << world.m_enemies[i]->m_objectRect.y << endl;
	}
	for (i = 0; i < 6; i++)
	{
		if (world.chicken_wings[i] != nullptr)
		{
			stream << "Chicken_wing " << i << endl;
			cout << "Chicken_wing " << i << endl;
		}
	}

	stream << "EOF";

	stream.close();
}

void Saver::loadSession()
{
	fstream stream(m_location);

	string type;
	coordinates buffCoor;
	int buffInt;
	ENEMY buffEnemy;
	
	while (stream >> type)
	{
		if (type != "EOF")
		{
			if (type == "Player")
			{
				// TODO: when we figure out the player architecture after the multiplayer update
			}
			else if (type == "Enemy")
			{
				stream >> buffInt;
				buffEnemy = static_cast<ENEMY>(buffInt);
				stream >> buffCoor.x >> buffCoor.y;
				stream >> buffInt;

				world.m_generator.generateEnemy(buffEnemy, buffCoor, buffInt);
			}
			else if (type == "Chicken_wing")
			{
				// TODO: rewrite the chicken wing class
			}
		}
		else
		{
			break;
		}
	}

	stream.close();
}