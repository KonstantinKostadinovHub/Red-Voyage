#include "Camera.h"
#include"World.h"
extern World world;

Camera::Camera()
{
    //ctor
    camera_rect.x = 0;
    camera_rect.y = 0;
    fcamera_rect.x = 0;
    fcamera_rect.y = 0;
    camera_rect.w = 1920;
    camera_rect.h = 1080;
}

Camera::~Camera()
{
    //dtor
}
void Camera::init(SDL_Rect* p1_rect, SDL_Rect* p2_rect){
    player1 = p1_rect;
    player2 = p2_rect;
}

void Camera::update(){
    dis_between = sqrt(abs(player1->x - player2->x) * abs(player1->x - player2->x) + abs(player1->y - player2->y) * abs(player1->y - player2->y));
    if(camera_rect.w >= 2880){camera_rect.w = 2880; camera_rect.h = 1620;}
    zoom_lvl = world.m_SCREEN_WIDTH / (0.0 + camera_rect.w);
    if(fcamera_rect.x <= world.m_backgroundRect.x) fcamera_rect.x = world.m_backgroundRect.y;
    if(fcamera_rect.y <= world.m_backgroundRect.x) fcamera_rect.y = world.m_backgroundRect.y;
    if(fcamera_rect.x + camera_rect.w >= world.m_backgroundRect.w) fcamera_rect.x = world.m_backgroundRect.w - camera_rect.w;
    if(fcamera_rect.y + camera_rect.h >= world.m_backgroundRect.h) fcamera_rect.y = world.m_backgroundRect.h - camera_rect.h;
    follow();
}

void Camera::follow(){
    float dx, dy;
    if(world.m_players.size() > 1){
        dx = (player1->x + player2->x) / 2 - camera_rect.w / 2 + player1->w / 3 + player2->w / 3;
        dy = (player1->y + player2->y) / 2 - camera_rect.h / 2 + player1->h / 3 + player2->w / 3;
    }else{
        dx = world.m_players[0]->m_objRect.x - 684 + world.m_players[0]->m_objRect.w / 3;
        dy = world.m_players[0]->m_objRect.y - 384 + world.m_players[0]->m_objRect.h / 3;
    }
    fcamera_rect.x = lerp(fcamera_rect.x, dx, 0.01 * following_speed);
    fcamera_rect.y = lerp(fcamera_rect.y, dy, 0.01 * following_speed);
    camera_rect.x = fcamera_rect.x;
    camera_rect.y = fcamera_rect.y;
}

void Camera::zoom(){
    if(world.m_players.size() > 1)
    {
        if(dis_between < 700) dis_between = 700;
        camera_rect.w = dis_between * 16 / 8;
        camera_rect.h = dis_between * 9 / 8;
    }else{
        camera_rect.w = 1366;
        camera_rect.h = 768;
    }
}
