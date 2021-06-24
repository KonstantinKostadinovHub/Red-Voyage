#include "Item.h"
#include "World.h"
#include <fstream>

using namespace std;
extern World world;

Item::Item()
{
    //ctor
}

Item::~Item()
{
    //dtor
}

void Item::init(string config_file) {
    config_file = "config\\" + config_file;
    fstream stream;
    string tmp;
    stream.open(config_file);
    stream >> tmp >> item_image;
    stream >> tmp >> item_rect.w;
    stream >> tmp >> item_rect.h;
    stream.close();

    item_texture = LoadTexture(item_image, world.m_main_renderer);
}

void Item::draw()
{
    world.drawObject(item_rect, item_texture);
}