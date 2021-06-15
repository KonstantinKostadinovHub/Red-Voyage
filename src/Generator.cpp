#include "Generator.h"

#include "World.h"

extern World world;

Generator::Generator()
{
    //ctor
}

Generator::~Generator()
{
    //dtor
}

void Generator::init(string configFile)
{
    configFile = "config\\" + configFile;

    fstream stream;
    string tmp;

    int tasks;

    stream.open(configFile);
    stream >> tmp >> m_enemySpawnCooldown >> m_oreSpawnCooldown >> m_TaskSpawnCooldown;
    stream >> tmp >> m_maxEnemies >> m_maxOre >> m_maxTasks;
    stream >> tmp >> m_ironSpawnZone.x >> m_ironSpawnZone.y >> m_ironSpawnZone.w >> m_ironSpawnZone.h;
    stream >> tmp >> m_aluminumSpawnZone.x >> m_aluminumSpawnZone.y >> m_aluminumSpawnZone.w >> m_aluminumSpawnZone.h;
    stream >> tmp >> m_titaniumSpawnZone.x >> m_titaniumSpawnZone.y >> m_titaniumSpawnZone.w >> m_titaniumSpawnZone.h;
    stream >> tmp >> m_EnemySpawnZone.x >> m_EnemySpawnZone.y >> m_EnemySpawnZone.w >> m_EnemySpawnZone.h;
    stream >> tmp >> tasks;

    for(int i = 0; i < tasks; i ++)
    {
        stream >> tmp;
        tmp = "\\task\\" + tmp;
        Task* task = new Task;
        task -> init(tmp);
        m_modelTasks.push_back(task);
    }

    stream.close();

    m_lastOreCreation = chrono::steady_clock::now();
    m_lastTaskCreation = chrono::steady_clock::now();
}

void Generator::generateOre()
{
    m_duration = chrono::steady_clock::now() - m_lastOreCreation;
    if(m_duration.count() > m_oreSpawnCooldown)
    {
        if(world.m_ores.size() < m_maxOre)
        {
            m_lastOreCreation = chrono::steady_clock::now();

            coordinates coor;
            coor.x = 0;
            coor.y = 0;

            Ore* ore = nullptr;

            if(rand() % 100 >= 60){
                ore = new Ore(&world.m_configManager.m_ironOre, world.m_main_renderer, coor);
            }else if(rand() % 100 >= 15){
                ore = new Ore(&world.m_configManager.m_aluminiumOre, world.m_main_renderer, coor);
            }else if(rand() % 100 >= 0){
                ore = new Ore(&world.m_configManager.m_titaniumOre, world.m_main_renderer, coor);
            }
            /*switch (rand() % 3)
            {
            case 0:
                ore = new Ore(&world.m_configManager.m_ironOre, world.m_main_renderer, coor);
                break;
            case 1:
                ore = new Ore(&world.m_configManager.m_titaniumOre, world.m_main_renderer, coor);
                break;
            case 2:
                ore = new Ore(&world.m_configManager.m_aluminiumOre, world.m_main_renderer, coor);
                break;
            }*/

			bool goodCase = false;

			while (!goodCase)
			{
				goodCase = true;
				for (int i = 0; i < world.m_ores.size() && goodCase; i++)
				{
					if (collRectRect(ore->m_rect, world.m_ores[i]->m_rect))
					{
						giveOreCoordinates(ore);
						goodCase = false;
					}
				}
				for (int i = 0; i < world.m_players.size() && goodCase; i++)
				{
					if (collRectRect(ore->m_rect, world.m_players[i]->m_objRect))
					{
						giveOreCoordinates(ore);
						goodCase = false;
						break;
					}
				}
			}

            world.m_ores.push_back(ore);
        }
    }
}

void Generator::generateTask()
{
    m_duration = chrono::steady_clock::now() - m_lastTaskCreation;

    if(m_duration.count() > m_TaskSpawnCooldown)
    {
        if(world.m_tasks.size() < m_maxTasks)
        {
            int taskNumber;
            bool taskChosen = false;

            while(!taskChosen)
            {
                taskNumber = rand() % m_modelTasks.size();
                taskChosen = true;

                for(int i = 0; i < world.m_tasks.size(); i++)
                {
                    if(m_modelTasks[taskNumber]->m_taskName == world.m_tasks[i]->m_taskName)
                    {
                        taskChosen = false;
                    }
                }
                if(world.m_tasks.size() == 0)
                {
                    taskChosen = true;
                }
            }

            int ironNeeded = rand() % 9 + 10;
            int titaniumNeeded = rand() % 9 + 1;
            int aluminiumNeeded = rand() % 9 + 8;
            
            Task* task = new Task((*m_modelTasks[taskNumber]), ironNeeded, titaniumNeeded, aluminiumNeeded);

            world.m_tasks.push_back(task);

            world.m_soundManager->play("Show_Task.mp3");

            m_lastTaskCreation = chrono::steady_clock::now();
        }
    }
}

void Generator::generateEnemy()
{
    m_duration = chrono::steady_clock::now() - m_lastEnemyCreation;
    
    if(m_duration.count() > m_enemySpawnCooldown)
    {
        if(world.m_enemies.size() < m_maxEnemies)
        {
            m_lastEnemyCreation= chrono::steady_clock::now();

            coordinates coor;
            coor.x = rand() % m_EnemySpawnZone.w + m_EnemySpawnZone.x;
            coor.y = rand() % m_EnemySpawnZone.h + m_EnemySpawnZone.y;

            int random = rand() % 2;
            
            if(random == 0)
            {
                Enemy* enemy = new Enemy(world.m_configManager.m_meleeEnemy);

                enemy->m_objectRect.x = coor.x;
                enemy->m_objectRect.y = coor.y;

                world.m_enemies.push_back(enemy);
            }
            else{
                EnemyShooter* enemy = new EnemyShooter(world.m_configManager.m_rangedEnemy);

                enemy->m_objectRect.x = coor.x;
                enemy->m_objectRect.y = coor.y;

                world.m_enemies.push_back(enemy);
            }
        }
    }
}

void Generator::giveOreCoordinates(Ore* ore)
{
	if(ore->m_type == IRON)
	{
		ore->m_rect.x = rand() % m_ironSpawnZone.w + m_ironSpawnZone.x;
		ore->m_rect.y = rand() % m_ironSpawnZone.h + m_ironSpawnZone.y;
	}
	else if (ore->m_type == ALUMINIUM)
	{
		ore->m_rect.x = rand() % m_aluminumSpawnZone.w + m_aluminumSpawnZone.x;
		ore->m_rect.y = rand() % m_aluminumSpawnZone.h + m_aluminumSpawnZone.y;
	}
	else if (ore->m_type == TITANIUM)
	{
		ore->m_rect.x = rand() % m_titaniumSpawnZone.w + m_titaniumSpawnZone.x;
		ore->m_rect.y = rand() % m_titaniumSpawnZone.h + m_titaniumSpawnZone.y;
	}
	else
	{
		string errorText = "error: trying to give coordinates to an ore with unknown type in line: " + to_string(__LINE__) + " in file " + __FILE__;
		fprintf(stderr, errorText.c_str());
		exit(EXIT_FAILURE);
	}
}

void Generator::generateEnemy(ENEMY type, coordinates coor, short health)
{
    if (type == ENEMY::MELEE)
    {
        Enemy* enemy = new Enemy(world.m_configManager.m_meleeEnemy);

        enemy->m_objectRect.x = coor.x;
        enemy->m_objectRect.y = coor.y;

        enemy->m_health = health;

        world.m_enemies.push_back(enemy);
    }
    else if(type == ENEMY::SHOOTER) 
    {
        EnemyShooter* enemy = new EnemyShooter(world.m_configManager.m_rangedEnemy);

        enemy->m_objectRect.x = coor.x;
        enemy->m_objectRect.y = coor.y;

        enemy->m_health = health;

        world.m_enemies.push_back(enemy);
    }
}