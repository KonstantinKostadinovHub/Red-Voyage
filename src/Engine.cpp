#include "Engine.h"
#include "defines.h"

#include <iostream>

SDL_Texture* LoadTexture(string configFile, SDL_Renderer* renderer)
{
    SDL_Texture* texture = nullptr;

    try
    {
        configFile = "img\\" + configFile;

        SDL_Surface* loadingSurface = SDL_LoadBMP(configFile.c_str());
        texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
        SDL_FreeSurface(loadingSurface);

        if(texture == nullptr)
        {
            throw (-1);
        }

    }catch (int i)
    {
        if(i < 0)
        {
            cout << "NO TEXTURE LOADED: " << configFile << endl;

            configFile = "img\\textureNotLoaded.bmp";
           
            SDL_Surface* loadingSurface = SDL_LoadBMP(configFile.c_str());
            texture = SDL_CreateTextureFromSurface(renderer, loadingSurface);
            SDL_FreeSurface(loadingSurface);

            cout << "HERE \n";
        }
    }
    return texture;
}

bool collLineLine(line a, line b)
{
    float uA = ((b.finish.x - b.start.x) * (a.start.y - b.start.y) - (b.finish.y - b.start.y) * (a.start.x - b.start.x)) / ((b.finish.y - b.start.y) * (a.finish.x - a.start.x) - (b.finish.x - b.start.x) * (a.finish.y - a.start.y));
    float uB = ((a.finish.x - a.start.x) * (a.start.y - b.start.y) - (a.finish.y - a.start.y) * (a.start.x - b.start.x)) / ((b.finish.y - b.start.y) * (a.finish.x - a.start.x) - (b.finish.x - b.start.x) * (a.finish.y - a.start.y));

    //cout << (b.finish.x - b.start.x) * (a.finish.y - a.start.y) << endl;

    if(uA >= 0 && uB >= 0 && uA <= 1 && uB <= 1)
    {
        return true;
    }
    return false;
}

bool collLineRect(line mainLine, line top, line bot, line left, line right)
{
    if(collLineLine(mainLine, top) ||
       collLineLine(mainLine, bot) ||
       collLineLine(mainLine, left) ||
       collLineLine(mainLine, right))
    {
        return true;
    }
    return false;
}

bool MouseIsInRect(coordinates coor , SDL_Rect rect)
{
    if(coor.x >= rect.x && coor.x <= rect.x + rect.w && coor.y >= rect.y && coor.y <= rect.y + rect.h)
    {
        return true;
    }
    return false;
}

bool collRectRect(SDL_Rect a, SDL_Rect b)
{
    if(a.x < b.x + b.w && a.x + a.w > b.x && a.y < b.y + b.h && a.y + a.h > b.y) return true;
    return false;
}

bool checkInOffBounds(SDL_Rect rect, int screenWidth, int screenHeight)
{
    if(rect.x + rect.w > screenWidth)
    {
        return true;
    }
    if(rect.x < 0)
    {
        return true;
    }
    if(rect.y + rect.h > screenHeight)
    {
        return true;
    }
    if(rect.y < 0)
    {
        return true;
    }
    return false;
}

int lerp(float start, float target, float f){
    return (start * (1.0 - f)) + (target * f);
}

void restrict(SDL_Rect* rect, int zx, int zy, int zw, int zh){
    if(rect->x < zx) rect->x = zx;
    if(rect->y < zy) rect->y = zy;
    if(rect->x + rect->w > zw) rect->x = zw - rect->w;
    if(rect->y + rect->h > zh) rect->y = zh - rect->h;
}


void write(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE)
{

    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect rect;
    SDL_Color fcolor;
    TTF_Font* font;

    string str = "ttf//ARCADECLASSIC.TTF";
    font = TTF_OpenFont(str.c_str(), FONT_SIZE);

    if(font == NULL){

        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    fcolor.r = 255;
    fcolor.g = 255;
    fcolor.b = 255;
    fcolor.a = 255;
    const char* t = text.c_str();
    surface = TTF_RenderText_Solid(font, t , fcolor);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = coor.x;
    rect.y = coor.y;
    SDL_RenderCopy(renderer, texture, NULL, &rect);
    SDL_FreeSurface(surface);
    SDL_DestroyTexture(texture);

}

pair<SDL_Texture*, SDL_Rect>  writeRed(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE)
{

    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect rect;
    SDL_Color fcolor;
    TTF_Font* font;

    string str = "ttf//ARCADECLASSIC.TTF";
    font = TTF_OpenFont(str.c_str(), FONT_SIZE);

    if(font == NULL){

        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    fcolor.r = 255;
    fcolor.g = 0;
    fcolor.b = 0;
    fcolor.a = 255;
    const char* t = text.c_str();
    surface = TTF_RenderText_Solid(font, t , fcolor);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = coor.x;
    rect.y = coor.y;
    SDL_FreeSurface(surface);
    pair<SDL_Texture*, SDL_Rect> myRect;
    myRect.first = texture;
    myRect.second = rect;
    return myRect;
}

pair<SDL_Texture*, SDL_Rect> writeGreen(string text, coordinates coor, SDL_Renderer* renderer, int FONT_SIZE)
{

    SDL_Texture* texture;
    SDL_Surface* surface;
    SDL_Rect rect;
    SDL_Color fcolor;
    TTF_Font* font;

    string str = "ttf//ARCADECLASSIC.TTF";
    font = TTF_OpenFont(str.c_str(), FONT_SIZE);

    if(font == NULL){

        fprintf(stderr, "error: font not found\n");
        exit(EXIT_FAILURE);
    }

    fcolor.r = 0;
    fcolor.g = 255;
    fcolor.b = 0;
    fcolor.a = 255;
    const char* t = text.c_str();
    surface = TTF_RenderText_Solid(font, t , fcolor);
    texture = SDL_CreateTextureFromSurface(renderer,surface);
    rect.w = surface->w;
    rect.h = surface->h;
    rect.x = coor.x;
    rect.y = coor.y;
    SDL_FreeSurface(surface);
    pair<SDL_Texture*, SDL_Rect> myRect;
    myRect.first = texture;
    myRect.second = rect;
    return myRect;
}

float returnAngleByCoordinates(coordinates direction)
{
    return atan2(direction.y, direction.x) * 180 / PI;
}

void drawRectCollision(SDL_Rect rect, SDL_Renderer* renderer)
{
	short x2 = rect.x + rect.w;
	short y2 = rect.y + rect.h;
	SDL_RenderDrawLine(renderer, rect.x, rect.y, x2, rect.y);
	SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, y2);
	SDL_RenderDrawLine(renderer, rect.x, y2, x2, y2);
	SDL_RenderDrawLine(renderer, x2, rect.y, x2, y2);
	/*
	if (
		!SDL_RenderDrawLine(renderer, rect.x, rect.y, x2, rect.y) ||
		!SDL_RenderDrawLine(renderer, rect.x, rect.y, rect.x, y2) ||
		!SDL_RenderDrawLine(renderer, rect.x, y2, x2, y2) ||
		!SDL_RenderDrawLine(renderer, x2, rect.y, x2, y2)
		)
	{
		string error = SDL_GetError();
		cout << "Error " << error << " in drawRectCollision() \n";
	}
	*/
}

void var_shake(float* a, float magnitude) {
    float b = ((static_cast<float> (rand()) / static_cast<float>(RAND_MAX)) * 2.0f - 1.0f) * magnitude;
    *a += b;
}