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
    config = "config//" + config;


    ifstream stream;
    stream.open(config.c_str());

    string tmp;
    stream >> tmp >> m_img;
    stream >> tmp >> m_objectRect.w;
    stream >> tmp >> m_objectRect.h;
    stream >> tmp >> m_startPos;
    stream >> tmp >> m_distance;
    stream >> tmp >> m_pos;


    m_distance = 65;
    m_objectRect.y = 20;
    m_objectRect.x = m_startPos + (m_pos-1)*(m_objectRect.w + m_distance);

    stream.close();


    m_objectTexture = LoadTexture(m_img, world.m_main_renderer);

    str = "x" + to_string(0);

    coor.x = m_objectRect.x + m_objectRect.w + 5;
    coor.y = m_objectRect.y;
}
void UIObject::update()
{



}
void UIObject::draw()
{

    SDL_RenderCopy(world.m_main_renderer, m_objectTexture , NULL , &m_objectRect);


    if(m_img == "Chicken_UI.bmp"){
        str = "x" + to_string(world.m_chickenCollected);
    }
    if(m_img == "Aluminium_Ore_UI.bmp"){
        str = "x" + to_string(world.m_aluminiumCollected);
    }
    if(m_img == "Titanium_Ore_UI.bmp"){
        str = "x" + to_string(world.m_titaniumCollected);
    }
    if(m_img == "Iron_Ore_UI.bmp"){
        str = "x" + to_string(world.m_ironCollected);
    }

    write(str,coor,world.m_main_renderer,30);


}
