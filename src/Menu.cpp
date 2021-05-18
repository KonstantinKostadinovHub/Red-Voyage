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
    config = "config//" + config;

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

    m_startRect.w *= m_sizeMultiplier;
    m_startRect.h *= m_sizeMultiplier;

    m_exitRect.w *= m_sizeMultiplier;
    m_exitRect.h *= m_sizeMultiplier;

    m_logoRect.w *= m_sizeMultiplier;
    m_logoRect.h *= m_sizeMultiplier;

    ///Perform mathematical formulas to set the position of the buttons

    m_startRect.x = (1920 - m_startRect.w) / 2 - 10;
    m_startRect.y = 700;

    m_exitRect.x = 1920 - 10 - m_exitRect.w;
    m_exitRect.y = 10;


    m_logoRect.x = (1920 - m_logoRect.w) / 2 - 10;
    m_logoRect.y = -100;

    m_startStartRect = m_startRect;
    m_startExitRect = m_exitRect;

    ///Load textures from the input images so that they appear on the screen

    m_objectTexture = LoadTexture(m_img,world.m_main_renderer);

    m_startTexture = LoadTexture(m_startImg,world.m_main_renderer);
    m_exitTexture = LoadTexture(m_exitImg,world.m_main_renderer);

    m_logoTexture = LoadTexture(m_logoImg,world.m_main_renderer);

}

void Menu::update()
{

    ///Check if the mouse is pressed and then if it is on(inside) the buttons and perform their assigned actions

    if(world.m_mouseIsPressed){

        if(MouseIsInRect(world.m_mouseCoordinates, m_exitRect)){

            world.m_gameState = EXIT;
            world.m_quitScene = true;
        }

        if(MouseIsInRect(world.m_mouseCoordinates, m_startRect)){

            world.m_gameState = GAME;
            world.m_quitScene = true;
        }
    }

    EnlargeButtons(world.m_mouseCoordinates,m_startRect,m_startStartRect);
    EnlargeButtons(world.m_mouseCoordinates,m_exitRect,m_startExitRect);

}

void Menu::draw()
{

    ///Copiing the textures and handing them to the renderer a.k.a. drawing them on our window
    SDL_RenderClear(world.m_main_renderer);

    SDL_RenderCopy(world.m_main_renderer, m_objectTexture , NULL , NULL);

    SDL_RenderCopy(world.m_main_renderer, m_startTexture , NULL , &m_startRect);
    SDL_RenderCopy(world.m_main_renderer, m_exitTexture , NULL , &m_exitRect);
    SDL_RenderCopy(world.m_main_renderer, m_logoTexture , NULL , &m_logoRect);


    SDL_RenderPresent(world.m_main_renderer);

}

void Menu::EnlargeButtons(coordinates coor ,SDL_Rect &rect ,SDL_Rect startRect)
{

    double currentBW = 0;
    double currentBH = 0;

    double bonusW = 5;
    double bonusH = 5;

    double maxWidth = startRect.w + 40;
    double maxHeight = startRect.h + 40;

    if(MouseIsInRect(coor, rect))
    {
        if(rect.w <= maxWidth)
        {
            currentBW += bonusW;
            currentBH += bonusH;

            rect.w = startRect.w + currentBW;
            rect.h = startRect.h + currentBH;
            rect.x = startRect.x - currentBW / 2;
            rect.y = startRect.y - currentBH / 2;
        }
    }else{

        currentBW = 0;
        currentBH = 0;

        rect = startRect;

    }


}


