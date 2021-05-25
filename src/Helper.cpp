#include "Helper.h"

Helper::Helper()
{

}

Helper::Helper(vector<Player*>* players, SDL_Renderer* renderer, float* zoom, SDL_Rect* camera)
{
	// Change these values to true if you want any of these cheats
	MAX_HEALTH = true;
	MAX_DAMAGE = false;
	MAX_SPEED = true;
	SHOW_ALL_RECTS = false;

	m_renderer = renderer;

	m_players = players;

	zoom_lvl = zoom;
	cameraRect = camera;
}


Helper::~Helper()
{
}

void Helper::update()
{
	if (MAX_DAMAGE || MAX_HEALTH || MAX_SPEED)
	{
		if(MAX_HEALTH)
		{
			for (short i = 0; i < m_players->size(); i++)
			{
				(*m_players)[i]->m_health = (*m_players)[i]->m_maxHealth;
			}
		}
		if (MAX_DAMAGE)
		{
			for (short i = 0; i < m_players->size(); i++)
			{
				(*m_players)[i]->m_dmg = 10000;
			}
		}
		if (MAX_SPEED)
		{
			for (short i = 0; i < m_players->size(); i++)
			{
				(*m_players)[i]->m_speed = 30;
			}
		}
	}
}

void Helper::drawCollision(SDL_Rect rect)
{
	SDL_Rect presentRect = {
		(int)((*zoom_lvl) * (rect.x - cameraRect->x)),
		(int)((*zoom_lvl) * (rect.y - cameraRect->y)),
		(int)((*zoom_lvl) * rect.w),
		(int)((*zoom_lvl) * rect.h)
	};
	drawRectCollision(presentRect, m_renderer);
}