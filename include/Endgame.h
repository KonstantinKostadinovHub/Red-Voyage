#ifndef ENDGAME_H
#define ENDGAME_H
#include <SDL.h>
#include<string>
using namespace std;
class Endgame
{
    public:
        string m_winImage;
        string m_lossImage;
        string m_poceedImage;

        SDL_Texture* m_win_texture;
        SDL_Texture* m_loss_texture;
        SDL_Texture* m_proceed_texture;

        SDL_Rect m_win_rect;
        SDL_Rect m_loss_rect;
        SDL_Rect m_proceed_button;
        SDL_Rect m_start_proceed_button;
        void init(string config);
        void update();
        void draw();
        Endgame();
        virtual ~Endgame();

    protected:

    private:
};

#endif // ENDGAME_H
