#ifndef CREDITS_H
#define CREDITS_H
#include <SDL.h>
#include<string>
using namespace std;

/// \brief A class used to initialize and draw the credits screen. 
class Credits
{
    public:
        ///<The class constructor
        Credits();
        ///<The class destructor
        virtual ~Credits();

        string m_credits_image; ///< The credits image that we use
        SDL_Texture* m_credits_texture; 
        /// A function used to read and initialize the basic variables for the credits screen
        void init(string config); 
        /// A function used to update the credits screen
        void update(); 
        /// A function used to draw the credits screen
        void draw(); 

    protected:

    private:
};

#endif // CREDITS_H
