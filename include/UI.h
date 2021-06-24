#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <string>
#include <vector>


#include "defines.h"
#include "UIObject.h"

/// \brief A class used to initialize and draw the User Interface block where the healthbars and UIObjects are placed.
class UI
{
    public:
        UI(); ///<The class constructor
        virtual ~UI(); ///<The class destructor

        UIObject* m_playerUI; ///< The background of the player's UI

        UIObject* m_heroImg; //< The img that shows the hero that is beeing played
        UIObject* m_primaryWeaponPhoto;
        UIObject* m_secondaryWeaponPhoto;

        void load(string config); ///<Initializing function
        void update(); ///< Updating function
        void draw(); ///<Drawing function

    protected:

    private:
};

#endif // UI_H
