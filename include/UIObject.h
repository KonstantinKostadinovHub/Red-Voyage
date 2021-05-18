#ifndef UIOBJECT_H
#define UIOBJECT_H


#include <SDL.h>
#include <string>


#include "defines.h"

class UIObject
{
    public:
        UIObject();
        virtual ~UIObject();

        int m_distance;
        int m_startPos;
        int m_pos;
        string m_img;
        string str;

        coordinates coor;

        SDL_Texture* m_objectTexture;

        SDL_Rect m_objectRect;

        void load(string config);
        void update();
        void draw();

    protected:

    private:
};

#endif // UIOBJECT_H
