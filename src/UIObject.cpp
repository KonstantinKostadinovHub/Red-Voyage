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
    ///
    ///   ###Example 
    ///   @code
    ///   m_objectRect.x = m_startPos + (m_pos-1)*(m_objectRect.w + m_distance);
    ///   @endcode
    ///   Doing a mathematical ecuation to determine a UIObject's coordinates
    ///
    m_objectRect.x = m_startPos + (m_pos-1)*(m_objectRect.w + m_distance);

    stream.close();

    m_img = "\\ores\\" + m_img;

    m_objectTexture = LoadTexture(m_img, world.m_main_renderer);

    ///Making a string to write on the screen e.g. "x4"
    /** @code
    *   count = "x" + to_string(0);
    *   @endcode
    */
    count = "x" + to_string(0);
    ///Setting the coordinates of the text.
    /** @code
    *       coor.x = m_objectRect.x + m_objectRect.w + 5;
    *       coor.y = m_objectRect.y;
    *   @endcode
    */
    coor.x = m_objectRect.x + m_objectRect.w + 5;
    coor.y = m_objectRect.y;
}
void UIObject::update()
{



}
void UIObject::draw()
{

    SDL_RenderCopy(world.m_main_renderer, m_objectTexture , NULL , &m_objectRect);

    ///Based on the type of a UIObject we determine witch count string to show , write and copy to the renderer.
    /** For Example:
    *   @code
    *       if(m_img == "Chicken_UI.bmp"){
    *           count = "x" + to_string(world.m_chickenCollected);
    *       }
    *   @endcode
    *
    *
    */
    if(m_img == "\\ores\\Chicken_UI.bmp"){
        count = "x" + to_string(world.m_chickenCollected);
    }
    if(m_img == "\\ores\\Aluminium_Ore_UI.bmp"){
        count = "x" + to_string(world.m_aluminiumCollected);
    }
    if(m_img == "\\ores\\Titanium_Ore_UI.bmp"){
        count = "x" + to_string(world.m_titaniumCollected);
    }
    if(m_img == "\\ores\\Iron_Ore_UI.bmp"){
        count = "x" + to_string(world.m_ironCollected);
    }

    write(count,coor,world.m_main_renderer,30);
}
