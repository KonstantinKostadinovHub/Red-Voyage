#ifndef ENGINE_H
#define ENGINE_H

#define PI 3.14

#include <cmath>
#include <string>
#include <float.h>
#include <utility>

#include <SDL.h>
#include <SDL_TTF.h>

#include "defines.h"

using namespace std;


SDL_Texture* LoadTexture(string configFile, SDL_Renderer* renderer);
bool collLineLine(line a, line b);
bool collLineRect(line a, line top, line bot, line left, line right);
bool MouseIsInRect(coordinates coor , SDL_Rect rect);
bool collRectRect(SDL_Rect a, SDL_Rect b);
bool checkInOffBounds(SDL_Rect rect, int screenWidth, int screenHeight);
int lerp(float start, float target, float f);
void restrict(SDL_Rect* rect, int zone_x, int zone_y, int zone_w, int zone_h);
void write(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE);
pair<SDL_Texture*, SDL_Rect> writeRed(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE);
pair<SDL_Texture*, SDL_Rect>  writeGreen(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE);

#endif // ENGINE_H
