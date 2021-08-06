#ifndef FOOD_H
#define FOOD_H
#include "Player.h"
#include "Engine.h"
#include <chrono>
#include <fstream>
using namespace std;

/*! \brief a class that is used for healing the player

    With this class we create chicken nuggets that spawn on the table.

*/

class Food
{
    public:

        int spawn_cooldown;
        int wings_currently_waiting = 0;
        int max_wings_waiting;
        Vector2 spawn_points_kitchen[6];

        chrono::duration<double> m_duration;
        chrono::time_point<chrono::steady_clock> last_spawned;

        void init(string config_file);
        void update_kitchen();

        Food();
        virtual ~Food();

    protected:

    private:
};

#endif // FOOD_H
