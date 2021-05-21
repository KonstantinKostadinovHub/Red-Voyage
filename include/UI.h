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

        string m_img; ///< The image of the UI

        SDL_Texture* m_objectTexture; ///<The Texture of the UI

        SDL_Rect m_objectRect; ///< The Rect of the UI

        UIObject* object = NULL; ///<A new UIObject

        vector<UIObject*> m_uiSelectables; ///< A vector of UIObject pointers

        void load(string config); ///<Initializing function
        void update(); ///< Updating function
        void draw(); ///<Drawing function

    protected:

    private:
};

#endif // UI_H
