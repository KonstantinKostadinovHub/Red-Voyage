#include "VisualEffect.h"

#include "World.h"

extern World world;

VisualEffect::VisualEffect()
{
}


VisualEffect::VisualEffect(const VisualEffect* model, SDL_Rect rect)
{
	anim = new animation;
	anim->currFrame = 0;
	anim->lastFrameUpdate = chrono::steady_clock::now();
	anim->frames = model->anim->frames;
	anim->timePerFrame = model->anim->timePerFrame;
	anim->widthOfFrame = model->anim->widthOfFrame;
	anim->srcRect->w = model->anim->srcRect->w;
	anim->srcRect->h = model->anim->srcRect->h;
	anim->srcRect->x = 0;
	anim->srcRect->y = 0;
	world.m_animator.m_animations.push_back(anim);
	
	m_texture = model->m_texture;
	m_objectRect = rect;
	m_objectRect.w = m_inGameWidth;
	m_objectRect.h = m_inGameHeight;
}

VisualEffect::~VisualEffect()
{
}

void VisualEffect::init(string configFile, SDL_Renderer* renderer)
{
	/*! \brief inits the model visual effect
		
		we use model to take the needed parameters of a vfx.
		we pass the config file, which must be put in the vfx folder.
	*/
	configFile = "config\\vfx\\" + configFile;

	string tmp, textureString;

	ifstream stream(configFile.c_str());

	short timePerFrame;

	if(stream.is_open())
	{
		anim = new animation;
		stream >> tmp >> textureString;
		anim->srcRect = &m_srcRect;
		stream >> tmp >> anim->frames;
		stream >> tmp >> timePerFrame;
		anim->timePerFrame = chrono::milliseconds(timePerFrame);
		stream >> tmp >> anim->widthOfFrame;
		stream >> tmp >> anim->srcRect->w >> anim->srcRect->h;
		stream >> tmp >> m_inGameWidth >> m_inGameHeight;
		anim->srcRect->x = 0;
		anim->srcRect->y = 0;
	
		m_texture = LoadTexture(textureString, renderer);

		stream.close();
	}

}
