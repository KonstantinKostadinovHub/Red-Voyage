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

    /** Reading the parameters from a file using a stream
    * @param    fstream stream; ///< defining the file stream
    * @param    string tmp; ///< A temporary variable used for better structuring in the configuration files e.g. ParameterName: param( tmp: name)
    *
    * 
    */
    fstream stream; 
    string tmp; 
    stream.open("config\\menu\\" + config);

    stream >> tmp >> m_credits_image;

    stream.close();

    m_credits_image = "\\menu\\" + m_credits_image;

    m_credits_texture = LoadTexture(m_credits_image, world.m_main_renderer);
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
