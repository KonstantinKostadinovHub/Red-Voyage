#pragma once

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
    NONE = 0, 
    MENU = 1, 
    GAME = 2, 
    CREDITS = 3, 
    EXIT = 4, 
    ENDGAME = 5, 
    TITLESCREEN = 6 ,
    CAVES = 7
}; ///< Game state enumerator defining game states to use

static string ENEMY_FOLDER = "enemy\\";
static string PLAYER_FOLDER = "player\\";
static string UI_FOLDER = "UI\\";
static string ORE_FOLDER = "ores\\";
static string MENU_FOLDER = "menu\\";
static string MAIN_FOLDER = "main\\";
static string ITEM_FOLDER = "item\\";
static string ICON_FOLDER = "icons\\";
static string HERO_FOLDER = "heroes\\";
static string WEAPON_FOLDER = "weapons\\";
static string ROOMS_FOLDER = "rooms\\";

struct coordinates
{
    int x = 0;
    int y = 0;
}; ///< A useful structure containing x and y axis of an object

static coordinates parseToCoordinates(SDL_Rect rect)
{
    return { rect.x , rect.y };
}

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

enum class ENEMY {
    NONE = 0,
    MELEE = 1,
    SHOOTER = 2
};

enum class ITEM {
    NONE = 0,
    LEATHER_BOOTS = 1
};

enum class HIT
{
    NOHIT = 0,
    LEFT = 1,
    TOP = 2,
    RIGHT = 3,
    BOT = 4
};

enum class WEAPON
{
    NONE = 0,
    PLASMA_GUN = 1,
    LASER_SWORD = 2
};

enum class HERO
{
    NONE = 0,
    JERRY = 1
};

enum class FONT {
    NONE = 0,
    ARCADE_CLASSIC = 1
};

enum class COLOR {
    NONE = 0,
    ORANGE = 1,
    LIGHT = 2,
    DARK = 3
};

struct UI_object
{
    SDL_Texture* objTexture = NULL;
    SDL_Rect objRect;
}; ///< An UI_Object object structure with its parameters

enum class ITEM_TYPE
{
    NONE = 0,
    HELMET = 1,
    CHESTPLATE = 2,
    LEGGINGS = 3,
    BOOTS = 4,
    WEAPON = 5,
    COLLECTABLE = 6
};