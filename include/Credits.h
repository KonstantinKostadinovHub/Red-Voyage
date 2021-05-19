#ifndef CREDITS_H
#define CREDITS_H
#include <SDL.h>
#include<string>
using namespace std;

/// \brief A class used to initialize and draw the credits screen 
class Credits
{
    public:
        Credits(); ///\fn The class constructor
        virtual ~Credits(); ///\fn The class destructor

        string m_credits_image; ///< The credits image that we use
        SDL_Texture* m_credits_texture; 
        void init(string config); ///\fn A function used to read and initialize the basic variables for the credits screen
        void update(); ///\fn A function used to update the credits screen
        void draw(); ///\fn A function used to draw the credits screen

    protected:

    private:
};

#endif // CREDITS_H
