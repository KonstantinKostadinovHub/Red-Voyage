#include "InputManager.h"

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	delete m_keyboardState;
}

void InputManager::setMouseMultiply(Vector2f multiplier)
{
    m_mouseMultiply.x = multiplier.x;
    m_mouseMultiply.y = multiplier.y;
}

void InputManager::handleInput()
{
    m_mouseIsClicked = false;
    m_mouseIsDoubleClicked = false;

    SDL_PollEvent(&m_event);

    if (m_event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (m_event.button.clicks >= 2)
        {
            m_mouseIsDoubleClicked = true;
        }

        m_mouseIsClicked = true;
    }

    if (m_event.type == SDL_MOUSEMOTION)
    {
        SDL_GetGlobalMouseState(&(m_mouseCoor.x), &(m_mouseCoor.y));
        m_mouseCoor.x *= m_mouseMultiply.x;
        m_mouseCoor.y *= m_mouseMultiply.y;
    }
}

void InputManager::init(string path)
{
}