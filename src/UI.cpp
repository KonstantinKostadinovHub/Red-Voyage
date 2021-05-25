#include "UI.h"

#include "World.h"
extern World world;

UI::UI()
{
    //ctor
}

UI::~UI()
{
    //dtor
}

void UI::load(string config)
{
    config = "config\\menu\\" + config;

    fstream stream;
    stream.open(config.c_str());

    string tmp;
    stream >> tmp >> m_img;
    stream >> tmp >> m_objectRect.w;
    stream >> tmp >> m_objectRect.h;

    stream.close();

    m_img = "\\UI\\" + m_img;

    m_objectRect.x = 0;
    m_objectRect.y = 0;

    m_objectTexture = LoadTexture(m_img, world.m_main_renderer);

    for(int i = 0 ; i < 4;i++)
    {
        /// Creating a new UIObject and checking what type it is so we can draw it on the UI
        /**
        *   @code
        *       case 0:
        *       object->load("iron_selectable.txt");
        *       break;
        *
        *   @endcode
        *
        */
        object = new UIObject();
        switch(i){

            case 0:
                object->load("iron_selectable.txt");
                break;
            case 1:
                object->load("titanium_selectable.txt");
                break;
            case 2:
                object->load("aluminium_selectable.txt");
                break;
            case 3:
                object->load("chicken_selectable.txt");
                break;

        }
        m_uiSelectables.push_back(object);

    }


}
void UI::update()
{
    /// Used to update all of the UIObjects in the vector
    for(int i =0 ; i < m_uiSelectables.size();i++){

        m_uiSelectables[i] -> update();

    }


}
void UI::draw()
{
    /// Drawing the UI and the vector of UIObjects aswell
    SDL_RenderCopy(world.m_main_renderer, m_objectTexture , NULL , &m_objectRect);

    for(int i =0 ; i < m_uiSelectables.size();i++){

        m_uiSelectables[i] -> draw();

    }

}
