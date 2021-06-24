#include "UI.h"

#include "World.h"
extern World world;

UI::UI()
{
    //ctor
}

UI::~UI()
{
    //dtor
}

void UI::load(string config)
{
    config = "config\\" + UI_FOLDER + config;

    UIObject* playerUI = new UIObject();
    UIObject* heroImg = new UIObject();
    UIObject* primaryWeapon = new UIObject();
    UIObject* secondaryWeapon = new UIObject();

    string tmp, img;
    
    fstream stream;
    stream.open(config.c_str());

    stream >> tmp >> img;
    img = UI_FOLDER + img;
    playerUI->m_objectTexture = LoadTexture(img, world.m_main_renderer);
    stream >> tmp >> playerUI->m_objectRect.x >> playerUI->m_objectRect.y >> playerUI->m_objectRect.w >> playerUI->m_objectRect.h;
    stream >> tmp >> heroImg->m_objectRect.x >> heroImg->m_objectRect.y >> heroImg->m_objectRect.w >> heroImg->m_objectRect.h;
    stream >> tmp >> primaryWeapon->m_objectRect.x >> primaryWeapon->m_objectRect.y >> primaryWeapon->m_objectRect.w >> primaryWeapon->m_objectRect.h;
    stream >> tmp >> secondaryWeapon->m_objectRect.x >> secondaryWeapon->m_objectRect.y >> secondaryWeapon->m_objectRect.w >> secondaryWeapon->m_objectRect.h;

    stream.close();

    m_playerUI = playerUI;
    m_heroImg = heroImg;
    m_primaryWeaponPhoto = primaryWeapon;
    m_secondaryWeaponPhoto = secondaryWeapon;

    m_heroImg->m_objectTexture = world.m_iconManager->returnTexture(HERO::JERRY);
    m_primaryWeaponPhoto->m_objectTexture = world.m_iconManager->returnTexture(WEAPON::LASER_SWORD);
    m_secondaryWeaponPhoto->m_objectTexture = world.m_iconManager->returnTexture(WEAPON::PLASMA_GUN);
}

void UI::update()
{
    
}

void UI::draw()
{
    /// Drawing the UI, the healthBar and the weapons that are in hand
    SDL_RenderCopy(world.m_main_renderer, m_playerUI->m_objectTexture , NULL , &m_playerUI->m_objectRect);
    SDL_RenderCopy(world.m_main_renderer, m_heroImg->m_objectTexture, NULL , &m_heroImg->m_objectRect);
    SDL_RenderCopy(world.m_main_renderer, m_primaryWeaponPhoto->m_objectTexture, NULL , &m_primaryWeaponPhoto->m_objectRect);
    SDL_RenderCopy(world.m_main_renderer, m_secondaryWeaponPhoto->m_objectTexture, NULL , &m_secondaryWeaponPhoto->m_objectRect);
}
