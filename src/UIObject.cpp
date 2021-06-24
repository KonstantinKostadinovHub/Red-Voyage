#include "UIObject.h"

#include "World.h"
#include "Engine.h"
extern World world;

UIObject::UIObject()
{
    //ctor
}

UIObject::~UIObject()
{
    //dtor
}

void UIObject::load(string config)
{
    ///Modifying the inputed config file so we can make the actual path
    config = "config\\" + UI_FOLDER + config;

    ifstream stream;
    stream.open(config.c_str());

    string tmp, img;
    stream >> tmp >> img;
    stream >> tmp >> m_objectRect.x >> m_objectRect.y >> m_objectRect.w >> m_objectRect.h;

    stream.close();

    m_objectTexture = LoadTexture(img, world.m_main_renderer);
}
