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
    fstream stream;
    string tmp;
    stream.open("config\\" + config);
    stream >> tmp >> m_credits_image;
    m_credits_texture = LoadTexture(m_credits_image, world.m_main_renderer);
}

void Credits::update(){
    SDL_Delay(8000);
    world.m_gameState = MENU;
    world.m_quitScene = true;
}

void Credits::draw(){
    SDL_RenderClear(world.m_main_renderer);
    SDL_RenderCopy(world.m_main_renderer, m_credits_texture , NULL , NULL);
    SDL_RenderPresent(world.m_main_renderer);
}
