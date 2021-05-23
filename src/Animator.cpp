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
        if(!m_animations[i]->finished && !m_animations[i]->pause && chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_animations[i]->lastFrameUpdate) > m_animations[i]->timePerFrame)
        {
            m_animations[i]->currFrame ++;
            if(m_animations[i]->currFrame >= m_animations[i]->frames)
            {
				if(!m_animations[i]->loop)
				{
					m_animations[i]->finished = true;
				}
				else
				{
					m_animations[i]->currFrame = 0;
				}
            }
			if(m_animations[i]->srcRect != nullptr)
			{
				m_animations[i]->srcRect->x = m_animations[i]->widthOfFrame * m_animations[i]->currFrame;
			}
			else
			{
				cout << "MEMORY LEAK: AN ANIMATION HAS NOT BEEN CLEANED, BUT IT'S OBJECT HAS BEEN DELETED \n";
			}

            m_animations[i]->lastFrameUpdate = chrono::high_resolution_clock::now();
        }else if(m_animations[i]->pause)
        {
            m_animations[i]->currFrame = 0;
            m_animations[i]->srcRect->x = 0;
        }
    }
}
