#ifndef CONFIGMANAGER_H
#define CONFIGMANAGER_H

#include <fstream>

#include "Ore.h"
#include "Bullet.h"
#include "Enemy.h"
#include "EnemyShooter.h"
#include "EnemyBullet.h"

using namespace std;
///\brief A class used to achieve higher framerate and faster performance .
/** That is achieved by loading the objects from the config file once and then 
* passing the parameters forward instead of loading every time thei are needed.
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

        void init(string configFile); ///<Initializating function

    protected:

    private:
};

#endif // CONFIGMANAGER_H
