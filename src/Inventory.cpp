#include "Inventory.h"
using namespace std;
Inventory::Inventory()
{
    //ctor
}

Inventory::~Inventory()
{
    //dtor
}

void Inventory::addItem(Item item) 
{
    if (curr_amount >= capacity) return;
    items[curr_amount] = item;
    cout << "An item " << item.name << " was added to the inventory at index " << curr_amount;
    curr_amount++;
}