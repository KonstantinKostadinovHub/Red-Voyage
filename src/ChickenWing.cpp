#include "ChickenWing.h"
#include "World.h"
#include <fstream>
#include <iostream>

using namespace std;
extern World world;
ChickenWing::ChickenWing()
{
    //ctor
}

ChickenWing::~ChickenWing()
{
    //dtor
}

void ChickenWing::init(string config_file){
    config_file = "config\\" + config_file;
    fstream stream;
    string tmp;
    stream.open(config_file);
    stream >> tmp >> wing_image;
    stream >> tmp >> wing_rect.w;
    stream >> tmp >> wing_rect.h;
    stream >> tmp >> regen_amount;
    stream.close();

    wing_texture = LoadTexture(wing_image, world.m_main_renderer);
}

void ChickenWing::draw()
{
    world.m_gameManager.drawObject(wing_rect, wing_texture);
}
