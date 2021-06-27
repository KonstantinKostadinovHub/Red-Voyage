#ifndef CHICKENWING_H
#define CHICKENWING_H
#include <SDL.h>
#include <string>
using namespace std;

class ChickenWing
{
    public:
        SDL_Rect wing_rect;
        SDL_Texture* wing_texture;
        string wing_image;
        int regen_amount;
        void init(string config_file);
        void draw();

        ChickenWing();
        virtual ~ChickenWing();

    protected:

    private:
};

#endif // CHICKENWING_H
