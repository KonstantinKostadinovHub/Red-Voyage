#include "Task.h"
#include "World.h"
#include <windows.h>

extern World world;

Task::Task(const Task& model, int m_iron, int m_titanium, int m_aluminium)
{
    m_ironNeeded = m_iron;
    m_titaniumNeeded = m_titanium;
    m_aluminiumNeeded = m_aluminium;
    m_workingOnTask = false;
    m_objRect = model.m_objRect;
    m_camera_rect = model.m_camera_rect;
    m_zoom_lvl = model.m_zoom_lvl;
    m_taskName = model.m_taskName;
    m_taskTexture = model.m_taskTexture;

    hasTitanium = false;
    hasIron = false;
    hasAluminium = false;

    coor.x = m_objRect.x + 20;
    coor.y = m_objRect.y + 100;

    string tmp = to_string(m_ironNeeded);

    pair<SDL_Texture*, SDL_Rect> myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

    m_ironNumber = myPair.first;
    m_ironNumberRect = myPair.second;

    coor.x = m_objRect.x + 60;
    coor.y = m_objRect.y + 100;

    tmp = to_string(m_aluminiumNeeded);

    myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

    m_aluminiumNumber = myPair.first;
    m_aluminiumNumberRect = myPair.second;

    coor.x = m_objRect.x + 100;
    coor.y = m_objRect.y + 100;
    tmp = to_string(m_titaniumNeeded);

    myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

    m_titaniumNeededNumber = myPair.first;
    m_titaniumNumberRect = myPair.second;

    m_doneTask = false;
}

Task::Task()
{

}

Task::~Task()
{
    //dtor
}

void Task::init(string configFile)
{
    configFile = "config\\" + configFile;

    fstream stream;
    string tmp, m_img;

    stream.open(configFile.c_str());

    stream >> tmp >> m_objRect.x >> m_objRect.y >> m_objRect.w >> m_objRect.h;
    stream >> tmp >> m_img;
    stream >> tmp >> m_taskName;

    stream.close();

    m_taskTexture = LoadTexture(m_img, world.m_main_renderer);

    m_camera_rect = &world.m_camera.camera_rect;
    m_zoom_lvl = &world.m_camera.zoom_lvl;

    coor.x = m_objRect.x + 20;
    coor.y = m_objRect.y + 100;

    tmp = to_string(m_ironNeeded);

    pair<SDL_Texture*, SDL_Rect> myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

    m_ironNumber = myPair.first;
    m_ironNumberRect = myPair.second;

    coor.x = m_objRect.x + 60;
    coor.y = m_objRect.y + 100;

    tmp = to_string(m_aluminiumNeeded);

    myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

    m_aluminiumNumber = myPair.first;
    m_aluminiumNumberRect = myPair.second;

    coor.x = m_objRect.x + 100;
    coor.y = m_objRect.y + 100;

    tmp = to_string(m_titaniumNeeded);

    myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

    m_titaniumNeededNumber = myPair.first;
    m_titaniumNumberRect = myPair.second;
}

void Task::update()
{
    string tmp;
    m_presentRect = {
        (int)((*m_zoom_lvl) * (double)(m_objRect.x - m_camera_rect -> x)),
        (int)((*m_zoom_lvl) * (double)(m_objRect.y - m_camera_rect -> y)),
        (int)((*m_zoom_lvl) * m_objRect.w),
        (int)((*m_zoom_lvl) * m_objRect.h),
    };

    bool buff = false;

    chrono::time_point<chrono::steady_clock> buffTime = chrono::steady_clock::now();

    bool resetTime = true;
    SDL_RenderCopy(world.m_main_renderer, m_taskTexture, NULL, &m_presentRect);

    if(m_ironNeeded > world.m_ironCollected)
    {
        if(hasIron)
        {
            hasIron = false;

            string tmp = to_string(m_ironNeeded);

            pair<SDL_Texture*, SDL_Rect> myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

            m_ironNumber = myPair.first;
        }
    }else{
        if(!hasIron)
        {
            hasIron = true;

            string tmp = to_string(m_ironNeeded);

            pair<SDL_Texture*, SDL_Rect> myPair = writeGreen(tmp, coor, world.m_main_renderer, 36);

            m_ironNumber = myPair.first;
        }
    }

    if(m_aluminiumNeeded > world.m_aluminiumCollected)
    {
        if(hasAluminium)
        {
            hasAluminium = false;

            tmp = to_string(m_aluminiumNeeded);

            pair<SDL_Texture*, SDL_Rect> myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

            m_aluminiumNumber = myPair.first;
        }
    }else{
        if(!hasAluminium)
        {
            hasAluminium = true;

            tmp = to_string(m_aluminiumNeeded);

            pair<SDL_Texture*, SDL_Rect> myPair = writeGreen(tmp, coor, world.m_main_renderer, 36);

            m_aluminiumNumber = myPair.first;

        }
    }

    if(m_titaniumNeeded > world.m_titaniumCollected)
    {
        if(hasTitanium)
        {
            hasTitanium = false;

            tmp = to_string(m_titaniumNeeded);

            pair<SDL_Texture*, SDL_Rect> myPair = writeRed(tmp, coor, world.m_main_renderer, 36);

            m_titaniumNeededNumber = myPair.first;
        }
    }else{
        if(!hasTitanium)
        {
            hasTitanium = true;

            tmp = to_string(m_titaniumNeeded);

            pair<SDL_Texture*, SDL_Rect> myPair = writeGreen(tmp, coor, world.m_main_renderer, 36);

            m_titaniumNeededNumber = myPair.first;
        }
    }

    for(int i = 0; i < world.m_players.size(); i ++)
    {
        x = abs(world.m_players[i] -> m_objRect.x + world.m_players[i] -> m_objRect.w / 2 - m_objRect.x - m_objRect.w / 2);
        y = abs(world.m_players[i] -> m_objRect.y + world.m_players[i] -> m_objRect.h / 2 - m_objRect.y - m_objRect.h / 2);

        distance = sqrt(x * x + y * y);


        if(distance < 200)
        {

            if(world.m_players[i] -> craftIsPressed)
            {
                resetTime = false;
            }
        }
    }

    if(resetTime)
    {
        m_lastButtonPressed = chrono::steady_clock::now();
    }

    m_duration = chrono::steady_clock::now() - m_lastButtonPressed;

    if(m_duration.count() >= 5)
    {
        if(hasIron && hasAluminium && hasTitanium) {
            m_doneTask = true;
            m_lastButtonPressed = chrono::steady_clock::now();
            world.m_soundManager -> play("Finished_Task.mp3");

            world.m_ironCollected -= m_ironNeeded;
            world.m_aluminiumCollected -= m_aluminiumNeeded;
            world.m_titaniumCollected -= m_titaniumNeeded;
        }
    }
}

void Task::draw()
{
    world.drawObject(m_objRect, m_taskTexture);

    world.drawObject(m_ironNumberRect, m_ironNumber);

    world.drawObject(m_aluminiumNumberRect, m_aluminiumNumber);

    world.drawObject(m_titaniumNumberRect, m_titaniumNeededNumber);
}
