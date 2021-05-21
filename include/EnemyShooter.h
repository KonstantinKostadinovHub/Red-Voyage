#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include <Enemy.h>

/*! \brief Used to create enemies that shoot bullets (AI) and define their actions

    This class initializes enemy shooters and generates projectiles.
*/

class EnemyShooter : public Enemy
{
    public:
        EnemyShooter();
        EnemyShooter(const EnemyShooter& model);
        virtual ~EnemyShooter();

        string m_bulletConfig;

        virtual void draw();

        virtual void load(string stream);
        virtual void attack();

    protected:

    private:
};

#endif // ENEMYSHOOTER_H
