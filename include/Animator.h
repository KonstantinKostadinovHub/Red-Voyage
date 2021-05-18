#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include <chrono>
#include <vector>

#include "Animator.h"

using namespace std;

struct animation{
    unsigned short frames;
    unsigned short currFrame = 0;
    unsigned short widthOfFrame;
    SDL_Rect* srcRect;
    // ms
    chrono::duration<float> timePerFrame;
    chrono::high_resolution_clock::time_point lastFrameUpdate;
    bool doAnimation = true;
};

/*! \class Animator
    \brief Class used for animating the objects
*/
class Animator
{
    public:
        Animator();
        virtual ~Animator();

        vector<animation*> m_animations;

        chrono::duration<float> m_duration;

        void updateFrames();

    protected:

    private:
};

#endif // ANIMATOR_H
