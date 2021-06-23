#ifndef GENERATOR_H
#define GENERATOR_H

#include <fstream>
#include <stdlib.h>
#include <chrono>
#include <vector>

#include "Ore.h"
#include "Enemy.h"
#include "Task.h"

using namespace std;

/*! \brief Generate the ores, enemies and tasks
	We choose a good position for every object that we generate and then we initiate it.
*/

class Generator
{
    public:
        Generator();
        virtual ~Generator();
		
		// Cooldowns
        short m_oreSpawnCooldown;
        short m_enemySpawnCooldown;
		short m_TaskSpawnCooldown;

		// Max objects of type
        short m_maxOre;
        short m_maxEnemies;
        short m_maxTasks;

		// Spawn zones
        SDL_Rect m_ironSpawnZone;
        SDL_Rect m_aluminumSpawnZone;
        SDL_Rect m_titaniumSpawnZone;
        SDL_Rect m_EnemySpawnZone;

        chrono::duration<double> m_duration;

		// Track the last time point when we created an object
        chrono::time_point<chrono::steady_clock> m_lastOreCreation;
        chrono::time_point<chrono::steady_clock> m_lastEnemyCreation;
        chrono::time_point<chrono::steady_clock> m_lastTaskCreation;

        vector<Task*> m_modelTasks;

        void initOre();

        void init(string configFile);

        void generateTask();
        void generateOre();
        void generateEnemy();
        void generateEnemy(ENEMY type, coordinates coor, short health);

		void giveOreCoordinates(Ore* ore);

    protected:

    private:
};

#endif // GENERATOR_H
