#ifndef ENDGAME_H
#define ENDGAME_H
#include <SDL.h>
#include<string>
using namespace std;

/// \brief A class used to initialize and draw the endgame events - **win** or **loss** 
class Endgame
{
    public:

        Endgame(); ///< The class construct
        virtual ~Endgame(); ///< The class destructor

        string m_winImage;    ///< The win screen image
        string m_lossImage;   ///< The loss screen image
        string m_poceedImage; ///< The proceed button image

        SDL_Texture* m_win_texture;    ///< The win screen texture
        SDL_Texture* m_loss_texture;   ///< The loss screen texture
        SDL_Texture* m_proceed_texture;///< The proceed button texture

        SDL_Rect m_win_rect;             ///< The win screen rect
        SDL_Rect m_loss_rect;            ///< The loss screen rect
        SDL_Rect m_proceed_button;       ///< The proceed button rect
        SDL_Rect m_start_proceed_button; ///< The start proceed button rect

        void init(string config); ///< The initialization function
        void update(); ///< The update function
        void draw(); ///< The draw function

    protected:

    private:
};

#endif // ENDGAME_H
