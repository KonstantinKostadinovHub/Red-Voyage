#include "ConfigManager.h"

#include "World.h"
extern World world;

ConfigManager::ConfigManager()
{
    //ctor
}

ConfigManager::~ConfigManager()
{
    //dtor
}

void ConfigManager::init(string configFile)
{
    ///Opening a stream and calling the load function for every object and configuration file found.
    configFile = "config\\" + configFile;

    fstream stream;
    string tmp;
    stream.open(configFile);

    stream >> tmp;
    tmp = ORE_FOLDER + tmp;
    m_ironOre.load(tmp);

    stream >> tmp;
    tmp = ORE_FOLDER + tmp;
    m_titaniumOre.load(tmp);

    stream >> tmp;
    tmp = ORE_FOLDER + tmp;
    m_aluminiumOre.load(tmp);

    stream >> tmp;
    tmp = PLAYER_FOLDER + tmp;
    m_bullet.load(tmp);

    stream >> tmp;
    m_meleeEnemy.load(tmp);

    stream >> tmp;
    m_rangedEnemy.load(tmp);

    stream >> tmp;
    tmp = ENEMY_FOLDER + tmp;
    m_enemyBullet.load(tmp);

	stream >> tmp;
	m_bulletExplosion.init(tmp);

	stream >> tmp;
	m_dust.init(tmp);

    stream >> tmp;
    m_chickenBuff.init(tmp);

    stream.close();
}
