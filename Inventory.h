#ifndef INVENTORY_H
#define INVENTORY_H
#include "Engine.h"
using namespace std;

/*

*/

class Inventory
{
    public:

        int spawn_cooldown;
        int wings_currently_waiting = 0;
        int max_wings_waiting;
        coordinates spawn_points_kitchen[6];

        Inventory();
        virtual ~Inventory();

    protected:

    private:
};

#endif // INVENTORY_H
