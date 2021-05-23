#ifndef ANIMATOR_H
#define ANIMATOR_H

#include <SDL.h>
#include <chrono>
#include <vector>

using namespace std;

struct animation{
    unsigned short frames; ///< The number of frames in the function
    unsigned short currFrame = 0; ///< A counter that tracks the current frame
    unsigned short widthOfFrame; ///< The width of frame in the source image (For example: If you have a sprite sheet with width of 800 and it has 40 frames, each frame equals 20)
    SDL_Rect* srcRect; ///< Pointer to the srcRect of the object that we want to animate
	
    chrono::duration<float> timePerFrame; ///< The miliseconds required for frame
    chrono::high_resolution_clock::time_point lastFrameUpdate;
	bool pause = false; ///< for example - the player should play the animation only when he walks
    bool loop = true; ///< If you want the animation to be loopable or unloopable, change this variable
	bool finished = false; ///< If the animation has finished, change this variable
};

/*! \class Animator
    \brief Class used for animating the objects
	
	It does so by taking the srcRect and updating it every frame. It takes each piece of the sprite sheet
*/
class Animator
{
    public:
        Animator();
        virtual ~Animator();

        vector<animation*> m_animations;

        chrono::duration<float> m_duration; ///< Buffer variable used for calculating the time difference between frames (used in update)

        void updateFrames();

    protected:

    private:
};

#endif // ANIMATOR_H
