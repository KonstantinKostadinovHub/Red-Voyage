#ifndef SOUNDMANAGER_H
#define SOUNDMANAGER_H

#include <SDL_mixer.h>
#include <SDL.h>
#include <fstream>
#include <string>
#include <iostream>

using namespace std;

/*! \brief Used to play sound effect and music
*/

class SoundManager
{
public:
    SoundManager();
    virtual ~SoundManager();

    void init(string configFile);
    void destroyChunks();
    void play(string sound);

    string Background_Music_str;
    string Button_Click_str;
    string Finished_Task_str;
    string Mine_str;
    string Show_task_str;
    string Shoot_str;
    string Enemy_Death_str;
    string Food_str;
    string Lose_str;
    string Player_Death_str;
    string Win_str;

    Mix_Chunk* Background_Music;
    Mix_Chunk* Button_Click;
    Mix_Chunk* Finished_Task;
    Mix_Chunk* Mine;
    Mix_Chunk* Show_task;
    Mix_Chunk* Shoot;
    Mix_Chunk* Enemy_Death;
    Mix_Chunk* Food;
    Mix_Chunk* Lose;
    Mix_Chunk* Player_Death;
    Mix_Chunk* Win;

protected:

private:
};

#endif // SOUNDMANAGER_H
