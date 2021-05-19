#include "Credits.h"

#include"World.h"
extern World world;

Credits::Credits()
{
    //ctor
}

Credits::~Credits()
{
    //dtor
}

void Credits::init(string config){

    /// Reading the parameters from a file using a stream
    fstream stream; ///< defining the file stream
    string tmp; ///< A temporary variable used for better structuring in the configuration files e.g. ParameterName: param( tmp: name)
    
    stream.open("config\\" + config);

    stream >> tmp >> m_credits_image;
    /// Creating a SDL_Texture with the user-defined function LoadTexture in Engine.cpp
    m_credits_texture = LoadTexture(m_credits_image, world.m_main_renderer);

    stream.close()
}

void Credits::update(){
    /// Doing a 8 second delay(8000 miliseconds) before going back to the menu 
    SDL_Delay(8000);
    world.m_gameState = MENU; ///Going back to the menu
    world.m_quitScene = true;
}

void Credits::draw(){

    /// Drawing the credits screen
    SDL_RenderClear(world.m_main_renderer);
    SDL_RenderCopy(world.m_main_renderer, m_credits_texture , NULL , NULL);
    SDL_RenderPresent(world.m_main_renderer);
}
