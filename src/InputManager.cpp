#include "InputManager.h"
#include "World.h";

extern World world;

InputManager::InputManager()
{

}

InputManager::~InputManager()
{
	delete m_keyboardState;
}

void InputManager::setMouseMultiply(Vector2f multiplier)
{
    world.m_mouseMultiply.x = multiplier.x;
    world.m_mouseMultiply.y = multiplier.y;
}

void startDrag(void* handleInput)
{
    InputManager* inputManager = (InputManager*)handleInput;
    inputManager->m_drag = true;
}

void stopDrag(void* handleInput)
{
    InputManager* inputManager = (InputManager*)handleInput;
    inputManager->m_drag = false;
}

void InputManager::init(string path)
{
    path = "config\\" + path;

    fstream stream;
    string tmp;

    stream.open(path);

    stream >> tmp >> move_up;
    stream >> tmp >> move_down;
    stream >> tmp >> move_left;
    stream >> tmp >> move_right;
    stream >> tmp >> craft;

    stream.close();

    m_up.second = (SDL_Scancode)move_up;
    m_down.second = (SDL_Scancode)move_down;
    m_left.second = (SDL_Scancode)move_left;
    m_right.second = (SDL_Scancode)move_right;
    m_craft.second = (SDL_Scancode)craft;
}

void InputManager::handleInput()
{
    m_keyboardState = SDL_GetKeyboardState(NULL);

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
        m_mouseCoor.x *= world.m_mouseMultiply.x;
        m_mouseCoor.y *= world.m_mouseMultiply.y;
    }

    if (m_keyboardState != NULL)
    {
        if (m_keyboardState[m_up.second])
        {
            m_up.first = true;
        }
        else
        {
            m_up.first = false;
        }
        if (m_keyboardState[m_down.second])
        {
            m_down.first = true;
        }
        else
        {
            m_down.first = false;
        }
        if (m_keyboardState[m_left.second])
        {
            m_left.first = true;
        }
        else
        {
            m_left.first = false;
        }
        if (m_keyboardState[m_right.second])
        {
            m_right.first = true;
        }
        else
        {
            m_right.first = false;
        }
        if (m_keyboardState[m_craft.second])
        {
            m_craft.first = true;
        }
        else
        {
            m_craft.first = false;
        }
        if (m_mouseIsClicked)
        {
            m_shootIsPressed = true;
        }
        else
        {
            m_shootIsPressed = false;
        }
    } 
}
