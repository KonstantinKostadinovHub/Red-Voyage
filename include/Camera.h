#ifndef CAMERA_H
#define CAMERA_H

#include<cmath>
#include <SDL.h>

#include "Engine.h"

class Camera
{
    public:
        Camera();
        virtual ~Camera();
        SDL_Rect camera_rect;
        SDL_Rect* player1;
        SDL_Rect* player2;
        fcoordinates fcamera_rect;
        int following_speed = 5;
        float zoom_lvl = 2;
        float zoomMulti = 2;
        float dis_between;
        void init(SDL_Rect* player_rect1, SDL_Rect* player_rect2);
        void update();
        void follow();
        void zoom();

    protected:

    private:
};

#endif // CAMERA_H
