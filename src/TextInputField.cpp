#include "TextInputField.h"
#include "World.h"
#include "Engine.h"
extern World world;

TextInputField::TextInputField() 
{
	
}

TextInputField::~TextInputField()
{

}

string TextInputField::getContaier()
{
	return m_container;
}

void TextInputField::init(string configFile)
{
	fstream stream(configFile);

	string tmp, img;

	stream >> tmp >> m_objectRect.x >> m_objectRect.y >> m_objectRect.w >> m_objectRect.h;
	stream >> tmp >> img;

	stream.close();

	m_backgroundTexture = LoadTexture(img, world.m_main_renderer);

	img = UI_FOLDER + img;

	m_clickedTheField = false;
}

void TextInputField::update()
{
	if (world.m_mouseIsPressed)
	{
		if (MouseIsInRect(world.m_mouseCoordinates, m_objectRect))
		{
			m_clickedTheField = true;
		}
		else
		{
			m_clickedTheField = false;
		}
	}

	const Uint8* state = SDL_GetKeyboardState(NULL);

	if (m_clickedTheField)
	{
		if (world.m_event.key.keysym.sym == SDLK_BACKSPACE && m_container.size() > 0 && world.m_event.type != SDL_KEYDOWN)
		{
			m_container = m_container.substr(0, m_container.length() - 1);
			return;
		}

		if (world.m_event.type == SDL_TEXTINPUT)
		{
			m_container += world.m_event.text.text;
		}
	}
}