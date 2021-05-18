#ifndef FOOD_H
#define FOOD_H
#include "Player.h"
#include "Engine.h"
#include <chrono>
#include <fstream>
using namespace std;

class Food
{
    public:

        int spawn_cooldown;
        int wings_currently_waiting = 0;
        int max_wings_waiting;
        coordinates spawn_points_kitchen[6];

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
