#include "VisualEffect.h"

#include "World.h"

extern World world;

VisualEffect::VisualEffect()
{

}

VisualEffect::VisualEffect(const VisualEffect* model, Vector2 coor)
{
	anim = new animation;
	anim->currFrame = 0;
	anim->lastFrameUpdate = chrono::steady_clock::now();
	anim->frames = model->anim->frames;
	anim->timePerFrame = model->anim->timePerFrame;
	anim->widthOfFrame = model->anim->widthOfFrame;
	anim->srcRect = &m_srcRect;
	anim->srcRect->w = model->anim->srcRect->w;
	anim->srcRect->h = model->anim->srcRect->h;
	anim->srcRect->x = 0;
	anim->srcRect->y = 0;
	anim->loop = model->anim->loop;
	world.m_gameManager.m_animator.m_animations.push_back(anim);
	
	m_texture = model->m_texture;
	m_objectRect.x = coor.x - model->m_inGameWidth / 2;
	m_objectRect.y = coor.y - model->m_inGameHeight / 2;
	m_objectRect.w = model->m_inGameWidth;
	m_objectRect.h = model->m_inGameHeight;
}

VisualEffect::~VisualEffect()
{
}

void VisualEffect::init(string configFile)
{
	/*! \brief inits the model visual effect
		
		we use model to take the needed parameters of a vfx.
		we pass the config file, which must be put in the vfx folder.
		if you want the animation to loop change the parameter after initialization
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
		stream >> tmp >> anim->srcRect->h;
		stream >> tmp >> m_inGameWidth >> m_inGameHeight;
		anim->srcRect->w = anim->widthOfFrame;
		anim->srcRect->x = 0;
		anim->srcRect->y = 0;
		anim->loop = false;

		textureString = "vfx\\" + textureString;

		m_texture = LoadTexture(textureString, world.m_main_renderer);

		stream.close();
	}

}

void VisualEffect::draw()
{
	world.m_gameManager.drawObjectWithSrc(m_objectRect, m_srcRect, m_texture);
}