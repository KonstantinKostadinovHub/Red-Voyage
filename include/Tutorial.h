#ifndef TUTORIAL_H
#define TUTORIAL_H

#include <SDL.h>

#include <string>

using namespace std;

class Tutorial
{
    public:
        Tutorial();
        virtual ~Tutorial();

        SDL_Texture* m_texture;

        string dataInfo;

        bool play;

        void init(string configFile);

        void update();
        void draw();

    protected:

    private:
};

#endif // TUTORIAL_H
