#ifndef TASK_H
#define TASK_H

#include <SDL.h>

#include <cmath>
#include <iostream>
#include <fstream>
#include <chrono>
#include <utility>

#include "Engine.h"

using namespace std;

class Task
{
public:
    Task();
    Task(const Task& model, int m_iron, int m_titanium, int m_aluminium);
    virtual ~Task();

    SDL_Rect m_objRect;

    SDL_Texture* m_taskTexture;
    string m_taskName;

    int m_ironNeeded;
    int m_titaniumNeeded;
    int m_aluminiumNeeded;
    int x, y, distance;
	unsigned short m_fontSize = 32;

    float* m_zoom_lvl;
    SDL_Rect* m_camera_rect;
    SDL_Rect m_presentRect;

    SDL_Rect m_ironNumberRect;
    SDL_Rect m_aluminiumNumberRect;
    SDL_Rect m_titaniumNumberRect;

    SDL_Texture* m_ironNumber;
    SDL_Texture* m_aluminiumNumber;
    SDL_Texture* m_titaniumNumber;

    bool hasIron;
    bool hasAluminium;
    bool hasTitanium;

    bool m_workingOnTask;
    bool m_doneTask;

    coordinates coor;

    void update();
    void draw();
    void init(string configFile);

    chrono::duration<double> m_duration;
    chrono::time_point<chrono::steady_clock> m_lastButtonPressed;

protected:

private:
};

#endif // TASK_H
