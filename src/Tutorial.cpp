#include "Tutorial.h"
#include "World.h"

#include <fstream>

extern World world;

Tutorial::Tutorial()
{
    //ctor
}

Tutorial::~Tutorial()
{
    //dtor
}

void Tutorial::init(string configFile)
{
    configFile = "config//" + configFile;

    fstream stream;

    string tmp, img;

    stream.open(configFile);

    stream >> tmp >> img;
    stream >> tmp >> dataInfo;

    stream.close();

    m_texture = LoadTexture(img, world.m_main_renderer);

    fstream dataInput;

    dataInfo = "data//" + dataInfo;

    dataInput.open(dataInfo);

    dataInput >> play;

    dataInput.close();
}

void Tutorial::update()
{
    if(!play)
    {
        const Uint8* state = SDL_GetKeyboardState(NULL);

        if(state[SDL_SCANCODE_SPACE])
        {
            play = true;

            fstream dataInput;

            dataInput.open(dataInfo);

            dataInput << "1" << endl;

            dataInput.close();
        }
    }
}

void Tutorial::draw()
{
    if(!play) SDL_RenderCopy(world.m_main_renderer, m_texture, NULL, NULL);
}
