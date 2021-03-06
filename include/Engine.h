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
bool MouseIsInRect(Vector2 coor , SDL_Rect rect);
bool collRectRect(SDL_Rect a, SDL_Rect b);
bool checkInOffBounds(SDL_Rect rect, int screenWidth, int screenHeight);
int lerp(float start, float target, float f);
void restrict(SDL_Rect* rect, int zone_x, int zone_y, int zone_w, int zone_h);
void write(string text, Vector2 coor, SDL_Renderer* renderer, int FONT_SIZE);
pair<SDL_Texture*, SDL_Rect> writeRed(string text, Vector2 coor, SDL_Renderer* renderer, int FONT_SIZE);
pair<SDL_Texture*, SDL_Rect>  writeGreen(string text, Vector2 coor, SDL_Renderer* renderer, int FONT_SIZE);
float returnAngleByCoordinates(Vector2 direction);
void drawRectCollision(SDL_Rect rect, SDL_Renderer* renderer);
void var_shake(float* a, float magnitude);
struct Vector2 returnCoordinatesByAngle(float angle);

#endif // ENGINE_H
