#include "SoundManager.h"

SoundManager::SoundManager()
{
    //ctor
}

SoundManager::~SoundManager()
{
    //dtor
}

void SoundManager::init(string configFile)
{
    configFile = "config\\" + configFile;

    fstream stream;
    string tmp;

    stream.open(configFile.c_str());

    stream >> tmp >> Background_Music_str;
    stream >> tmp >> Button_Click_str;
    stream >> tmp >> Finished_Task_str;
    stream >> tmp >> Mine_str;
    stream >> tmp >> Show_task_str;
    stream >> tmp >> Shoot_str;
    stream >> tmp >> Enemy_Death_str;
    stream >> tmp >> Food_str;
    stream >> tmp >> Lose_str;
    stream >> tmp >> Player_Death_str;
    stream >> tmp >> Win_str;

    stream.close();

    if(Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, MIX_DEFAULT_CHANNELS, 1024) == - 1)
    {
        printf("s", Mix_GetError());
    }

    Background_Music = Mix_LoadWAV(("music\\" + Background_Music_str).c_str());
    Button_Click = Mix_LoadWAV(("music\\" + Button_Click_str).c_str());
    Finished_Task = Mix_LoadWAV(("music\\" + Finished_Task_str).c_str());
    Mine = Mix_LoadWAV(("music\\" + Mine_str).c_str());
    Show_task = Mix_LoadWAV(("music\\" + Show_task_str).c_str());
    Shoot = Mix_LoadWAV(("music\\" + Shoot_str).c_str());
    Enemy_Death = Mix_LoadWAV(("music\\" + Enemy_Death_str).c_str());
    Food = Mix_LoadWAV(("music\\" + Food_str).c_str());
    Lose = Mix_LoadWAV(("music\\" + Lose_str).c_str());
    Player_Death = Mix_LoadWAV(("music\\" + Player_Death_str).c_str());
    Win = Mix_LoadWAV(("music\\" + Win_str).c_str());
}

void SoundManager::play(string sound)
{
    Mix_AllocateChannels(16);

    if(sound == Background_Music_str)
    {
        Mix_PlayChannel(1, Background_Music, 100000000);
        Mix_Volume(1, 50);
    }
    else if(sound == Button_Click_str)
    {
        Mix_PlayChannel(2, Button_Click, 1);
        Mix_Volume(2, 50);
    }
    else if(sound == Finished_Task_str)
    {
        Mix_PlayChannel(3, Finished_Task, 0);
        Mix_Volume(3, 50);
    }
     else if(sound == Mine_str)
    {
        Mix_PlayChannel(4, Mine, 0);
        Mix_Volume(4, 50);
    }
     else if(sound == Show_task_str)
    {
        Mix_PlayChannel(5, Show_task, 0);
        Mix_Volume(5, 50);
    }
    else if(sound == Shoot_str)
    {
        Mix_PlayChannel(6, Shoot, 0);
        Mix_Volume(6, 50);
    }
    else if(sound == Enemy_Death_str)
    {
        Mix_PlayChannel(7, Enemy_Death, 0);
        Mix_Volume(7, 50);
    }
    else if(sound == Food_str)
    {
        Mix_PlayChannel(8, Food, 0);
        Mix_Volume(8, 50);
    }
    else if(sound == Lose_str)
    {
        Mix_PlayChannel(9, Lose, 0);
        Mix_Volume(9, 50);
    }
    else if(sound == Player_Death_str)
    {
        Mix_PlayChannel(10, Player_Death, 0);
        Mix_Volume(10, 50);
    }
    else if(sound == Win_str)
    {
        Mix_PlayChannel(11, Win, 0);
        Mix_Volume(11, 60);
    }
}

void SoundManager::destroyChunks()
{
    Mix_FreeChunk(Background_Music);
    Background_Music = NULL;

    Mix_FreeChunk(Button_Click);
    Button_Click = NULL;

    Mix_FreeChunk(Finished_Task);
    Finished_Task = NULL;

    Mix_FreeChunk(Food);
    Food = NULL;

    Mix_FreeChunk(Lose);
    Lose = NULL;

    Mix_FreeChunk(Player_Death);
    Player_Death = NULL;

    Mix_FreeChunk(Enemy_Death);
    Enemy_Death = NULL;

    Mix_FreeChunk(Win);
    Win = NULL;

    Mix_FreeChunk(Shoot);
    Shoot = NULL;

    Mix_FreeChunk(Show_task);
    Show_task = NULL;

    Mix_FreeChunk(Mine);
    Mine = NULL;
}
