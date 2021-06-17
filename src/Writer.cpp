#include "Writer.h"

Writer::Writer()
{

}

Writer::Writer(SDL_Renderer* renderer)
{
	m_renderer = renderer;
}

Writer::~Writer()
{

}

void Writer::init(string configFile)
{
	///In this function we create the main color values
	configFile = "config\\" + MAIN_FOLDER + configFile;

	string tmp;
	fstream stream(configFile);
	
	stream >> tmp >> m_orange.r >> m_orange.g >> m_orange.b;
	stream >> tmp >> m_light.r >> m_light.g >> m_light.b;
	stream >> tmp >> m_dark.r >> m_dark.g >> m_dark.b;

	stream.close();
}

SDL_Texture* Writer::getText(string text, FONT fontName, COLOR colorName, Uint8 fontSize)
{
	TTF_Font* font;
	SDL_Color color;

	switch (fontName)
	{
	case FONT::ARCADE_CLASSIC:
		font = TTF_OpenFont(text.c_str(), fontSize);
		break;
	default:
		font = TTF_OpenFont(text.c_str(), fontSize);
	}

	if (font == nullptr) 
	{
		fprintf(stderr, "error: font not found\n");
		exit(EXIT_FAILURE);
	}

	switch (colorName)
	{
	case COLOR::ORANGE:
		color = m_orange;
		break;
	case COLOR::LIGHT:
		color = m_light;
		break;
	case COLOR::DARK:
		color = m_dark;
		break;
	default:
		color = m_light;
	}

	const char* t = text.c_str();
	SDL_Surface* surface = TTF_RenderText_Solid(font, t, color);
	SDL_Texture* texture = SDL_CreateTextureFromSurface(m_renderer, surface);

	SDL_FreeSurface(surface);
	return texture;
}