#ifndef INVENTORY_H
#define INVENTORY_H
#include "Engine.h"
#include "Item.h"
#include <iostream>
using namespace std;

/*
* 
*/

class Inventory
{
    public:

        int curr_amount = 0;
        int capacity = 10;
        Item items[10];
        void addItem(Item item);

        Inventory();
        virtual ~Inventory();

    protected:

    private:
};

#endif // INVENTORY_H
