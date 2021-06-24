#ifndef ITEM_H
#define ITEM_H
#include "Engine.h"
#include "Player.h"
#include <SDL.h>
#include <string>

using namespace std;

/*
* 
*/

class Item
{
    public:
        string name;
        Player owner;

        SDL_Rect item_rect;
        SDL_Texture* item_texture;
        string item_image;

        void init(string config_file);
        void draw();

        Item();
        virtual ~Item();

    protected:

    private:
};

#endif // ITEM_H
