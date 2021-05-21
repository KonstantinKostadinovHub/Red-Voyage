#include "Animator.h"

#include "defines.h"

Animator::Animator()
{
    //ctor
}

Animator::~Animator()
{
    //dtor
}

void Animator::updateFrames()
{
    for(int i = 0; i < m_animations.size(); i ++)
    {
        if(m_animations[i]->doAnimation && chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_animations[i]->lastFrameUpdate) > m_animations[i]->timePerFrame)
        {
            m_animations[i]->currFrame ++;
            if(m_animations[i]->currFrame >= m_animations[i]->frames)
            {
                m_animations[i]->currFrame = 0;
            }
            m_animations[i]->srcRect->x = m_animations[i]->widthOfFrame * m_animations[i]->currFrame;

            m_animations[i]->lastFrameUpdate = chrono::high_resolution_clock::now();
        }else if(!m_animations[i]->doAnimation)
        {
            m_animations[i]->currFrame = 0;
            m_animations[i]->srcRect->x = m_animations[i]->widthOfFrame * m_animations[i]->currFrame;
        }
    }
}
