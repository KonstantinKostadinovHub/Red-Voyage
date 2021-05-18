#ifndef ENEMYSHOOTER_H
#define ENEMYSHOOTER_H

#include <Enemy.h>



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
