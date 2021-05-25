#include "Endgame.h"
#include "Engine.h"
#include "Menu.h"
#include "World.h"
#include<fstream>
extern World world;
Endgame::Endgame()
{
    //ctor
}

Endgame::~Endgame()
{
    //dtor
}

void Endgame::init(string config)
{
    /// Getting the values of some variables from a configuration file and doing some basic math to give values to others.
    fstream stream;
    string tmp;
    stream.open("config\\menu\\" + config);
    stream >> tmp >> m_winImage;
    stream >> tmp >> m_lossImage;
    stream >> tmp >> m_poceedImage >> m_proceed_button.w >> m_proceed_button.h;

    stream.close();

    m_proceed_button.x = (1920 - m_proceed_button.w)/2;
    m_proceed_button.y = (1920 - m_proceed_button.h)/2;

    m_start_proceed_button = m_proceed_button;

    m_winImage = "\\menu\\" + m_winImage;
    m_lossImage = "\\menu\\" + m_lossImage;
    m_poceedImage = "\\menu\\" + m_poceedImage;

    m_win_texture = LoadTexture(m_winImage, world.m_main_renderer);
    m_loss_texture = LoadTexture(m_lossImage, world.m_main_renderer);
    m_proceed_texture = LoadTexture(m_poceedImage, world.m_main_renderer);
}

void Endgame::update()
{
    if(world.m_mouseIsPressed)
    {
        if(MouseIsInRect(world.m_mouseCoordinates, m_proceed_button))
        {
            /// We check if the mouse is pressed on a certain button and than we redirect the 
            /// player/players either to the win screen or the loss screen depending on if he/they won or not.
            if(world.win == 1)
            {
                world.m_gameState = CREDITS;
            }else{
                world.m_gameState = MENU;
            }
            world.m_quitScene = true;
        }
    }
}

void Endgame::draw()
{
    /// We draw a certain screen depending on the win/loss screen
    SDL_RenderClear(world.m_main_renderer);

    if(world.win == -1)
    {
        SDL_RenderCopy(world.m_main_renderer, m_loss_texture , NULL , NULL);

    }else if(world.win == 1)
    {
        SDL_RenderCopy(world.m_main_renderer, m_win_texture , NULL , NULL);
    }
    SDL_RenderCopy(world.m_main_renderer, m_proceed_texture , NULL , &m_proceed_button);

    SDL_RenderPresent(world.m_main_renderer);
}
