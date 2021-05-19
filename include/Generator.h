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

class Generator
{
    public:
        Generator();
        virtual ~Generator();

        short m_oreSpawnCooldown;
        short m_enemySpawnCooldown;
		short m_TaskSpawnCooldown;

        short m_maxOre;
        short m_maxEnemies;
        short m_maxTasks;

        SDL_Rect m_ironSpawnZone;
        SDL_Rect m_aluminumSpawnZone;
        SDL_Rect m_titaniumSpawnZone;
        SDL_Rect m_EnemySpawnZone;
        chrono::duration<double> m_duration;

        chrono::time_point<chrono::steady_clock> m_lastOreCreation;
        chrono::time_point<chrono::steady_clock> m_lastEnemyCreation;
        chrono::time_point<chrono::steady_clock> m_lastTaskCreation;

        vector<Task*> m_modelTasks;

        void initOre();

        void init(string configFile);

        void generateTask();
        void generateOre();
        void generateEnemy();

		void giveOreCoordinates(Ore* ore);

    protected:

    private:
};

#endif // GENERATOR_H
