#include "VisualEffect.h"

#include "World.h"

extern World world;

VisualEffect::VisualEffect()
{
}


VisualEffect::~VisualEffect()
{
}

void VisualEffect::init(string configFile, SDL_Renderer* renderer)
{
	configFile = "config\\" + configFile;

	string tmp, textureString;

	ifstream stream(configFile.c_str());

	short timePerFrame;

	int a = 10;
	a++;
	cout << a << endl;

	if(stream.is_open())
	{
		// Test 2
		animation* anim = new animation;
		stream >> tmp >> textureString;
		anim->lastFrameUpdate = chrono::high_resolution_clock::now();
		anim->srcRect = &m_srcRect;
		stream >> tmp >> anim->frames;
		stream >> tmp >> timePerFrame;
		anim->timePerFrame = chrono::milliseconds(timePerFrame);
		stream >> tmp >> anim->widthOfFrame;
		stream >> tmp >> anim->srcRect->x >> anim->srcRect->y >> anim->srcRect->w >> anim->srcRect->h;
		world.m_animator.m_animations.push_back(anim);
	
		m_texture = LoadTexture(textureString, renderer);

		stream.close();
	}

}
