#ifndef DEFINES_H_INCLUDED
#define DEFINES_H_INCLUDED

#include <iostream>
#include <string>

/*! \class defines
    \brief A header that contains structures and enumerators

    They are used for the different type of game states, ores and more
*/
using namespace std;
///A user-defined function similar to std::cout but giving more information
/**
*   @code
*   #define D(x) cerr << #x << " = " << (x) << " | " << __LINE__ << endl;
*   @endcode
*/
///A user-defined function similar to D(x) but more advanced
/**
*   @code
*   #define Dex(x) cerr << #x << " = " << (x) << " | " << __LINE__ << " " << __FILE__ << endl;
*   @endcode
*/
#define D(x) cerr << #x << " = " << (x) << " | " << __LINE__ << endl;
#define Dex(x) cerr << #x << " = " << (x) << " | " << __LINE__ << " " << __FILE__ << endl;

#define SPEED_FACTOR 1.2


enum GAME_STATE
{
    NONE = 0, ///< NONE
    MENU = 1, ///< MENU
    GAME = 2, ///< GAME
    CREDITS = 3, ///< CREDITS
    EXIT = 4, ///< EXIT
    ENDGAME = 5 ///< ENDGAME
}; ///< Game state enumerator defining 5 game states to use

struct coordinates
{
    int x = 0;
    int y = 0;
}; ///< A useful structure containing x and y axis of an object

struct fcoordinates
{
    float x = 0;
    float y = 0;
}; ///< A useful structure similar to coordinates but containing the x and y axis of an object in float 


struct line
{
    fcoordinates start;
    fcoordinates finish;
}; ///< A useful structure creating a line from coordinates

enum ORE
{
    NOORE = 0,
    IRON = 1,
    TITANIUM = 2,
    ALUMINIUM = 3
}; ///< Ore enumerator used to determine what ore are we using or checking for

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


}; ///< An Button object structure with its parameters

struct UI_object
{
    SDL_Texture* objTexture = NULL;
    SDL_Rect objRect;
}; ///< An UI_Object object structure with its parameters

#endif // DEFINES_H_INCLUDED
