#ifndef TITLESCREEN_H
#define TITLESCREEN_H

#include <fstream>

#include "World.h"

class TitleScreen
{
public:
    TitleScreen();
    virtual ~TitleScreen();

    SDL_Rect m_objectRect;
    SDL_Texture* m_objectTexture;

    string m_img;
    string m_imgCurr;

    short int m_numberOfStates;
    short int m_currState;
    void load(string configFile, SDL_Renderer* renderer);
    void update();
    void draw(SDL_Renderer* renderer);

protected:

private:
};

#endif // TITLESCREEN_H
