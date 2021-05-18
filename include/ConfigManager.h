#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <fstream>

#include "Ore.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyShooter.h"
#include "EnemyBullet.h"

using namespace std;

class ConfigManager
{
    public:
        ConfigManager();
        virtual ~ConfigManager();

        Ore m_ironOre;
        Ore m_titaniumOre;
        Ore m_aluminiumOre;

        Bullet m_bullet;
        EnemyBullet m_enemyBullet;

        Enemy m_meleeEnemy;
        EnemyShooter m_rangedEnemy;

        void init(string configFile);

    protected:

    private:
};

#endif // CONFIGMANAGER_H
