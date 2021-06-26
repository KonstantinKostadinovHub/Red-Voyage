#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <fstream>

#include "Ore.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyShooter.h"
#include "EnemyBullet.h"
#include "VisualEffect.h"
#include "ChickenBuff.h"
#include "LeatherBoots.h"
#include "Cave.h"
#include "CaveRoom.h"

using namespace std;

/// \brief Creates models of all the objects that are later used in the session
/** That is achieved by loading the objects from the config file once and then 
* passing the parameters forward instead of opening files every time when we create a new instanse.
*/
class ConfigManager
{
    public:
        ConfigManager(); ///<The class constructor
        virtual ~ConfigManager(); ///<The class destructor

        Ore m_ironOre; ///< Ore object wich is assigned for iron
        Ore m_titaniumOre; ///< Ore object wich is assigned for titanium
        Ore m_aluminiumOre; ///< Ore object wich is assigned for aluminium

        Bullet m_bullet; ///<A Bullet object
        EnemyBullet m_enemyBullet; ///< An EnemyBullet object

        Enemy m_meleeEnemy; ///< A Enemy object
        EnemyShooter m_rangedEnemy; ///< A EnemyShooter object

		VisualEffect m_bulletExplosion;
		VisualEffect m_dust;

        ChickenBuff m_chickenBuff;

        LeatherBoots m_leatherBoots;

        void init(string configFile); ///<Initializating function

    protected:

    private:
};

#endif // CONFIGMANAGER_H
