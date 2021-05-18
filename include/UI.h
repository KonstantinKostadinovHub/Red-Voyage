#ifndef UI_H
#define UI_H

#include <SDL.h>
#include <string>
#include <vector>


#include "defines.h"
#include "UIObject.h"


class UI
{
    public:
        UI();
        virtual ~UI();

        string m_img;

        SDL_Texture* m_objectTexture;

        SDL_Rect m_objectRect;

        UIObject* object = NULL;

        vector<UIObject*> m_uiSelectables;

        void load(string config);
        void update();
        void draw();

    protected:

    private:
};

#endif // UI_H
