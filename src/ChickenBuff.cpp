#include "ChickenBuff.h"
#include "World.h"

extern World world;

ChickenBuff::ChickenBuff()
{

}

ChickenBuff::ChickenBuff(const ChickenBuff* model)
{
    healPerSecond = model->healPerSecond;
    duration = model->duration;

    m_startEffect = time(NULL);
    m_lastHealthAdded = time(NULL);
}

ChickenBuff::~ChickenBuff()
{
    //dtor
}

void ChickenBuff::init(string configFile)
{
    configFile = "config\\" + configFile;

    fstream stream;
    string tmp;

    stream.open(configFile.c_str());

    stream >> tmp >> healPerSecond;
    stream >> tmp >> duration;

    stream.close();
}

bool ChickenBuff::checkForApply()
{
    /* Calculate if the duration is expired and if it is we can add health.
    *  Then we set the last health added to be now.
    */

    if (time(NULL) - m_lastHealthAdded > 0)
    {
        if (time(NULL) - m_startEffect >= duration)
        {
            m_destroyEffect = true;
            return false;
        }
        m_applyEffect = true;
        m_lastHealthAdded = time(NULL);
        return true;
    }
    else
    {
        return false;
    }
}

void ChickenBuff::applyEffect()
{
    /* If checkForApply is true, we apply the effect;
    */

    if (m_applyEffect)
    {
        player->m_health += healPerSecond;
    }
}