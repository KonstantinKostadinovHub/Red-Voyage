#include "Food.h"
#include "World.h"
#include "Engine.h"
#include <iostream>
using namespace std;
extern World world;
Food::Food()
{
    //ctor
}

Food::~Food()
{
    //dtor
}

void Food::init(string config_file){
    config_file = "config\\" + config_file;

    fstream stream;
    string tmp;

    stream.open(config_file);
    stream >> tmp >> spawn_cooldown;
    stream >> tmp >> max_wings_waiting;
    stream >> spawn_points_kitchen[0].x >> spawn_points_kitchen[0].y;
    stream >> spawn_points_kitchen[1].x >> spawn_points_kitchen[1].y;
    stream >> spawn_points_kitchen[2].x >> spawn_points_kitchen[2].y;
    stream >> spawn_points_kitchen[3].x >> spawn_points_kitchen[3].y;
    stream >> spawn_points_kitchen[4].x >> spawn_points_kitchen[4].y;
    stream >> spawn_points_kitchen[5].x >> spawn_points_kitchen[5].y;
    stream.close();
}
void Food::update_kitchen(){
    m_duration = chrono::steady_clock::now() - last_spawned;
    if(m_duration.count() > spawn_cooldown || wings_currently_waiting <= max_wings_waiting){
        for(int i = 0; i < 4; i++){
            if(world.chicken_wings[i] == nullptr){

                world.chicken_wings[i] = new ChickenWing;
                world.chicken_wings[i]->wing_rect.x = spawn_points_kitchen[i].x;
                world.chicken_wings[i]->wing_rect.y = spawn_points_kitchen[i].y;
                world.chicken_wings[i]->init("food_object.txt");
                last_spawned = chrono::steady_clock::now();
                wings_currently_waiting++;
                break;
            }
        }
    }
}
