#ifndef CREDITS_H
#define CREDITS_H
#include <SDL.h>
#include<string>
using namespace std;
class Credits
{
    public:
        string m_credits_image;
        SDL_Texture* m_credits_texture;
        void init(string config);
        void update();
        void draw();
        Credits();
        virtual ~Credits();

    protected:

    private:
};

#endif // CREDITS_H
