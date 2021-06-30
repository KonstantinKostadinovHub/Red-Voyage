#include <fstream>

#include <SDL.h>

#include "defines.h"
#include "Engine.h"

using namespace std;

class IconManager
{
public:
	IconManager();
	~IconManager();

	SDL_Texture* returnTexture(HERO type);
	SDL_Texture* returnTexture(WEAPON type);

	void init(string configFile, SDL_Renderer* renderer);

	SDL_Texture* m_noTexture;

	/// The textures of heroes
	SDL_Texture* m_jerryTexture;

	/// The textures of weapons
	SDL_Texture* m_plasmaGunTexture;
	SDL_Texture* m_laserSwordTexture;
};