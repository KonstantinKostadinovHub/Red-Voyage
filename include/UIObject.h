#ifndef UIOBJECT_H
#define UIOBJECT_H


#include <SDL.h>
#include <string>


#include "defines.h"
/// \brief An basic class that is used for simple images in the user interface 
class UIObject
{
    public:
        UIObject();
        virtual ~UIObject();

        SDL_Texture* m_objectTexture;

        SDL_Rect m_objectRect;

        virtual void load(string config);

    protected:

    private:
};

#endif // UIOBJECT_H
