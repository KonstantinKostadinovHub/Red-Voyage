#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include <iostream>
#include <string>

using namespace std;

#define D(x) cerr << #x << " = " << (x) << " | " << __LINE__ << endl;
#define Dex(x) cerr << #x << " = " << (x) << " | " << __LINE__ << " " << __FILE__ << endl;

#define SPEED_FACTOR 1.2

/*! \class defines
    \brief A header that contains structures and enumerators

    They are used for the different type of game states, ores and more
*/

enum GAME_STATE
{
    NONE = 0,
    MENU = 1,
    GAME = 2,
    CREDITS = 3,
    EXIT = 4,
    ENDGAME = 5
};

struct coordinates
{
    int x = 0;
    int y = 0;
};

struct fcoordinates
{
    float x = 0;
    float y = 0;
};

struct line
{
    fcoordinates start;
    fcoordinates finish;
};

enum ORE
{
    NOORE = 0,
    IRON = 1,
    TITANIUM = 2,
    ALUMINIUM = 3
};

struct Button
{

    SDL_Rect startRect;
    SDL_Rect objectRect;

    SDL_Texture* objTexture = nullptr;

    double currentBonusW = 0;
    double currentBonusH = 0;

    double bonusW = 0;
    double bonusH = 0;

    double maxWidth = 0;
    double maxHeight = 0;


};

struct UI_object
{
    SDL_Texture* objTexture = NULL;
    SDL_Rect objRect;
};

#endif // DEFINES_H_INCLUDED
