#include "Menu.h"
#include <fstream>
#include "Engine.h"

#include "World.h"

extern World world;

Menu::Menu()
{
    //ctor
    m_sizeMultiplier = 4.5;
}

Menu::~Menu()
{
    //dtor
}

void Menu::load(string config)
{
    config = "config\\"  + MENU_FOLDER + config;

    ifstream stream;
    stream.open(config.c_str());

    ///Read the variables from a configuration file
    string tmp;
    stream >> tmp >> m_img;

    stream >> tmp >> m_startImg;
    stream >> tmp >> m_startRect.w;
    stream >> tmp >> m_startRect.h;

    stream >> tmp >> m_exitImg;
    stream >> tmp >> m_exitRect.w;
    stream >> tmp >> m_exitRect.h;

    stream >> tmp >> m_logoImg;
    stream >> tmp >> m_logoRect.w;
    stream >> tmp >> m_logoRect.h;

    stream.close();

    ///Apply multiplier to change images to fit the screen
    /**
    *   Example:
    *   @code
    *   m_startRect.w *= m_sizeMultiplier;
    *   m_startRect.h *= m_sizeMultiplier;
    *   @endcode
    *
    */

    m_startRect.w *= m_sizeMultiplier;
    m_startRect.h *= m_sizeMultiplier;

    m_exitRect.w *= m_sizeMultiplier;
    m_exitRect.h *= m_sizeMultiplier;

    m_logoRect.w *= m_sizeMultiplier;
    m_logoRect.h *= m_sizeMultiplier;

    ///Perform mathematical formulas to set the position of the buttons
    /**
    *   Example:
    *   @code
    *   m_startRect.x = (1920 - m_startRect.w) / 2 - 10;
    *   m_startRect.y = 700;
    *   @endcode
    *
    */

    m_startRect.x = (1920 - m_startRect.w) / 2 - 10;
    m_startRect.y = 700;

    m_exitRect.x = 1920 - 10 - m_exitRect.w;
    m_exitRect.y = 10;

    m_logoRect.x = (1920 - m_logoRect.w) / 2 - 10;
    m_logoRect.y = -100;

    m_startStartRect = m_startRect;
    m_startExitRect = m_exitRect;

    ///Load textures from the input images so that they appear on the screen

    m_img = "\\menu\\" + m_img;
    m_startImg = "\\menu\\" + m_startImg;
    m_exitImg = "\\menu\\" + m_exitImg;
    m_logoImg = "\\menu\\" + m_logoImg;

    m_objectTexture = LoadTexture(m_img,world.m_main_renderer);

    m_startTexture = LoadTexture(m_startImg,world.m_main_renderer);
    m_exitTexture = LoadTexture(m_exitImg,world.m_main_renderer);

    m_logoTexture = LoadTexture(m_logoImg,world.m_main_renderer);

}

void Menu::update()
{

    ///Check if the mouse is pressed and then if it is on(inside) the buttons and perform their assigned actions e.g. *Go in a game or close it*

    if(world.m_mouseIsPressed){

        if(MouseIsInRect(world.m_mouseCoordinates, m_exitRect)){ 
            world.m_soundManager->play("Button_Click.mp3");
            world.m_gameState = EXIT;
            world.m_quitScene = true;
        }

        if(MouseIsInRect(world.m_mouseCoordinates, m_startRect)){
            world.m_soundManager->play("Button_Click.mp3");
            world.m_gameState = GAME;
            world.m_quitScene = true;
        }
    }
    /// If needed perform the EnlargeButtons function
    /**
    *   Example:
    *   @code 
    *   EnlargeButtons(world.m_mouseCoordinates,m_startRect,m_startStartRect);
    *   EnlargeButtons(world.m_mouseCoordinates,m_exitRect,m_startExitRect);
    *   @endcode
    *
    */

}

void Menu::draw()
{
    ///Copying the textures and handing them to the renderer a.k.a. drawing them on our window
    SDL_RenderClear(world.m_main_renderer);

    SDL_RenderCopy(world.m_main_renderer, m_objectTexture , NULL , NULL);

    SDL_RenderCopy(world.m_main_renderer, m_startTexture , NULL , &m_startRect);
    SDL_RenderCopy(world.m_main_renderer, m_exitTexture , NULL , &m_exitRect);
    SDL_RenderCopy(world.m_main_renderer, m_logoTexture , NULL , &m_logoRect);

    SDL_RenderPresent(world.m_main_renderer);
}

void Menu::EnlargeButtons(coordinates coor ,SDL_Rect &rect ,SDL_Rect startRect)
{
    ///The function accepts 3 parameters
    /**
    *   @param coordinates coor - coordinates of the mouse
    *   @param SDL_Rect &rect - the Rect we are going to modify (that's why its passed by reference)
    *   @param SDL_Rect startRect - the starting Rect that we can always come back to
    *
    */
    ///Defines:
    double currentBW = 0; /// \param currentBW A variable that shows how much a button has grown until now on his width*/
    double currentBH = 0; /// \param currentBH A variable that shows how much a button has grown until now on his height

    double bonusW = 5;  /// \param bonusW A variable that shows how much a button can grown on his width per update
    double bonusH = 5;  /// \param bonusH A variable that shows how much a button can grown on his height per update

    double maxWidth = startRect.w + 40;  /// \param maxWidth A variable that shows how much a button is allowed to grow on his width
    double maxHeight = startRect.h + 40; /// \param maxHeight A variable that shows how much a button is allowed to grow on his height

    if(MouseIsInRect(coor, rect))
    {
        if(rect.w <= maxWidth)
        {
            ///After checking if the mouse is over a button and it is within the allowed width and height we perform the enlargement formulas
            currentBW += bonusW;
            currentBH += bonusH;

            rect.w = startRect.w + currentBW;
            rect.h = startRect.h + currentBH;
            rect.x = startRect.x - currentBW / 2;
            rect.y = startRect.y - currentBH / 2;
        }
    }else{
        /// If the mouse doesnt hover over a button we return it to its original size
        currentBW = 0;
        currentBH = 0;

        rect = startRect;
    }
}
