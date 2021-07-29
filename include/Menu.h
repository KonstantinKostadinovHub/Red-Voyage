#ifndef MENU_H
#define MENU_H

#include <SDL.h>

#include <string>
#include "defines.h"

using namespace std;
/// \brief A class used to initialize and draw the main menu of Red Voyage and the containing buttons and logos.

class Menu
{
    public:

        Menu(); ///<The class constructor
        virtual ~Menu(); ///<The class destructor

        string m_img; ///< Menu image
        string m_startImg; ///< Start button imagwe
        string m_exitImg; ///< Exit button image
        string m_logoImg; ///< Logo image

        float m_sizeMultiplier; ///< A variable which determines how much a sertain object should be scaled.

        SDL_Texture* m_objectTexture; ///< Menu texture
        SDL_Texture* m_startTexture; ///< Start button texture
        SDL_Texture* m_exitTexture; ///< Exit button texture
        SDL_Texture* m_logoTexture; ///< Logo texture

        SDL_Rect m_startRect; ///< Start button rect
        SDL_Rect m_exitRect; ///< Exit button rect
        SDL_Rect m_logoRect; ///< Logo rect


        SDL_Rect m_startStartRect; ///<Starting rect for Star button used to remember last position when scaling said button
        SDL_Rect m_startExitRect;  ///<Starting rect for Exit button used to remember last position when scaling said button

        void load(string config); ///< Initializing function
        void update(); ///<Updating function
        void draw(); ///<Drawing function

        void EnlargeButtons(Vector2 coor ,SDL_Rect &rect ,SDL_Rect startRect); ///<Function used to create a enlargment effect when the mouse hovers over a button

    protected:

    private:
};

#endif // MENU_H
