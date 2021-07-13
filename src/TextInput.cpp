#include "TextInput.h"

TextInput::TextInput()
{
	m_container = " ";
	m_texture = nullptr;
	m_typing = false;
}

TextInput::~TextInput()
{
	SDL_DestroyTexture(m_texture);
}

void TextInput::init(string configFile, SDL_Renderer* renderer, SDL_Event* event, Vector2* mouseCoor, bool* mouseIsPressed)
{
	m_event = event;
	m_mouseIsPressed = mouseIsPressed;
	m_mouseCoor = mouseCoor;
	m_renderer = renderer;

	string tmp, img;

	int m_padding;

	configFile = "config\\" + UI_FOLDER + configFile;
	
	m_typing = false;

	fstream stream(configFile);

	stream >> tmp >> m_imgRect.x >> m_imgRect.y >> m_imgRect.w >> m_imgRect.h;
	stream >> tmp >> m_padding;
	stream >> tmp >> img;

	m_inputBox.x = m_imgRect.x + m_padding;
	m_inputBox.y = m_imgRect.y + m_padding;
	m_inputBox.w = m_imgRect.w - m_padding;
	m_inputBox.h = m_imgRect.h - m_padding;

	stream.close();

	img = UI_FOLDER + img;

	m_texture = LoadTexture(img, m_renderer);
}

void TextInput::update()
{
	SDL_StartTextInput();

	if (*m_mouseIsPressed)
	{
		if (MouseIsInRect(*m_mouseCoor, m_inputBox))
		{
			m_typing = true;
		}
		else
		{
			m_typing = false;
		}
	}
	if (m_typing)
	{
		if (m_event->type == SDL_TEXTINPUT || m_event->type == SDL_KEYDOWN)
		{
			if (m_event->type == SDL_KEYDOWN && m_event->key.keysym.sym == SDLK_BACKSPACE && m_container.length() > 0)
			{
				m_container = m_container.substr(0, m_container.length() - 1);
			}
			else if (m_event->type == SDL_TEXTINPUT)
			{
				m_container += m_event->text.text;
			}
		}
		D(m_container);
	}
}

void TextInput::draw()
{
	SDL_RenderCopy(m_renderer, m_texture, NULL, &m_imgRect);
}