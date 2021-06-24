#include "IconManager.h"

IconManager::IconManager()
{

}

IconManager::~IconManager()
{

}

void IconManager::init(string configFile, SDL_Renderer* renderer)
{
	//m_noTexture = LoadTexture("textureNotLoaded.bmp", renderer);
	
	configFile = "config\\" + UI_FOLDER + configFile;
	fstream stream(configFile);

	string tmp;

	/// Heroes' Textures 
	stream >> tmp;
	tmp = UI_FOLDER + HERO_FOLDER + tmp;
	m_jerryTexture = LoadTexture(tmp, renderer);

	/// Weapons' Textures
	stream >> tmp;
	tmp = UI_FOLDER + WEAPON_FOLDER + tmp;
	m_plasmaGunTexture = LoadTexture(tmp, renderer);

	stream >> tmp;
	tmp = UI_FOLDER + WEAPON_FOLDER + tmp;
	m_laserSwordTexture = LoadTexture(tmp, renderer);

	stream.close();
}

SDL_Texture* IconManager::returnTexture(HERO type)
{
	SDL_Texture* returnTexture = nullptr; 
	//m_noTexture;

	switch (type)
	{
	case HERO::JERRY:
		returnTexture = m_jerryTexture;
	}

	return returnTexture;
}

SDL_Texture* IconManager::returnTexture(WEAPON type)
{
	SDL_Texture* returnTexture = nullptr;

	//returnTexture = m_noTexture;

	switch (type)
	{
	case WEAPON::LASER_SWORD:
		return returnTexture = m_laserSwordTexture;
	case WEAPON::PLASMA_GUN:
		return returnTexture = m_plasmaGunTexture;
	}

	return returnTexture;
}