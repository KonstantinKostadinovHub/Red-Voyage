#include "Player.h"
#include "ItemManager.h"
#include "World.h"

extern World world;

Player::Player()
{
    m_oldvelocity.x = 1;
    m_inSpaceship = true;
}

Player::~Player()
{
    //dtor
}

void Player::init(SDL_Renderer* renderer, string configFile)
{
    m_healthBar = new HealthBar();

    m_configFile = "config\\player\\" + configFile;
    fstream stream;
    string tmp, m_flipImg;

    stream.open(m_configFile.c_str());

    stream >> tmp >> m_objRect.w >> m_objRect.h >> m_objRect.x >> m_objRect.y;
    stream >> tmp >> m_playerImg;
    stream >> tmp >> m_speed;
    stream >> tmp >> m_health;
    stream >> tmp >> HP;
    stream >> tmp >> m_shootCooldown;
    stream >> tmp >> m_animRect.x >> m_animRect.y >> m_animRect.w >> m_animRect.h;
    stream >> tmp >> m_widthOfFrame;
    stream >> tmp >> m_flipImg;
    stream >> tmp >> m_distance;
    stream >> tmp >> m_dmg;
	stream >> tmp >> m_timeBetweenDustEffects;

    stream.close();

    /*! After we read the configFile we check the controls of the player and then load it
    */

    m_gun = new Gun;
    m_gun -> init(200);
    m_gun->setPlayerRect(&m_objRect);
    m_shootingPoint = m_gun->getShootingPoint();

    m_elapsed_engage = chrono::high_resolution_clock::now();
    m_engagementRate = chrono::milliseconds(m_shootCooldown);

    m_playerImg = PLAYER_FOLDER + m_playerImg;
    m_flipImg = PLAYER_FOLDER + m_flipImg;

    playerTexture = LoadTexture(m_playerImg, world.m_main_renderer);
    flipTexture = LoadTexture(m_flipImg, world.m_main_renderer);

    m_coor.x = m_objRect.x;
    m_coor.y = m_objRect.y;

    m_maxHealth = m_health;

    m_healthBar -> init(HP, &m_health, &m_maxHealth, &m_shield);
    m_camera_rect = &world.m_gameManager.m_camera.camera_rect;
    m_zoom_lvl = &world.m_gameManager.m_camera.zoom_lvl;

    m_shield = 100;
    
    anim = new animation;
    anim -> frames = 4;
    anim -> lastFrameUpdate = chrono::high_resolution_clock::now();
    anim -> timePerFrame = chrono::milliseconds((int)100);
    anim -> widthOfFrame = m_widthOfFrame;
    anim -> srcRect = &m_srcRect;
    anim -> srcRect -> x = m_animRect.x;
    anim -> srcRect -> y = m_animRect.y;
    anim -> srcRect -> w = m_animRect.w;
    anim -> srcRect -> h = m_animRect.h;
    world.m_gameManager.m_animator.m_animations.push_back(anim);

    m_oldvelocity.x = m_speed;

    m_inSpaceship = true;

    m_helmet = ITEM::NONE;
    m_chestplate = ITEM::NONE;
    m_leggings = ITEM::NONE;
    m_boots = ITEM::NONE;
    
    m_primaryWeapon = ITEM::NONE;
    m_secondaryWeapon = ITEM::NONE;
}

bool Player::checkForShooting()
{
    /* If the cooldown is expired, the player can shoot */

    if(chrono::duration_cast<chrono::milliseconds>(chrono::high_resolution_clock::now() - m_elapsed_engage) > m_engagementRate)
    {
        m_canShoot = true;
        return true;
    }

    return false;
}

void Player::update()
{
    /*! Check if the player has pressed a button, then we shoot or move or do tasks.
    *   Also check for collision and animation
    */

    m_velocity.x = 0;
    m_velocity.y = 0;

    checkForShooting();
    
    if (world.m_inputManager->m_shootIsPressed && !m_canShoot)
    {
        m_gun->m_canShoot = true;

        m_elapsed_engage = chrono::high_resolution_clock::now();
        m_canShoot = false;
    }
    if (world.m_inputManager->m_up.first)
    {
        m_velocity.y = -1;
    }
    else if (world.m_inputManager->m_down.first)
    {
        m_velocity.y = 1;
    }
    if (world.m_inputManager->m_left.first)
    {
        m_velocity.x = -1;
    }
    else if (world.m_inputManager->m_right.first)
    {
        m_velocity.x = 1;
    }

    m_objRect.x += m_velocity.x * m_speed;

    if (world.m_gameState == GAME)
    {
        if (world.m_gameManager.collisionWithShip(m_objRect))
        {
            m_objRect.x -= m_velocity.x * m_speed;
        }
        else
        {
            for (int i = 0; i < world.m_gameManager.m_ores.size(); i++)
            {
                if (collRectRect(m_objRect, world.m_gameManager.m_ores[i]->m_rect))
                {
                    m_objRect.x -= m_velocity.x * m_speed;
                    break;
                }
            }
        }
    }

    m_objRect.y += m_velocity.y * m_speed;

    if(world.m_gameManager.collisionWithShip(m_objRect))
    {
        m_objRect.y -= m_velocity.y * m_speed;
    }
    else
    {
        for(int i = 0; i < world.m_gameManager.m_ores.size(); i++)
        {
            if(collRectRect(m_objRect, world.m_gameManager.m_ores[i]->m_rect))
            {
                m_objRect.y -= m_velocity.y * m_speed;
                break;
            }
        }
    }
  
    Vector2 playerCoor;
    playerCoor.x = m_objRect.x + m_objRect.w / 2;
    playerCoor.y = m_objRect.y + m_objRect.h / 2;
    m_gun -> update(m_velocity, playerCoor, world.m_inputManager->m_shootIsPressed);
    
    if(m_health > m_maxHealth)
    {
        m_health = m_maxHealth;
    }

    m_healthBar -> update();
    //! if the player is not moving than don't play the moving animation
    if(m_velocity.x == 0 && m_velocity.y == 0)
    {
        anim->pause = true;
		m_lastDustEffect = time(NULL);
    }
    else
    {
        if(m_velocity.x != 0)
            m_oldvelocity.x = m_velocity.x;
        if (m_velocity.y != 0)
            m_oldvelocity.y = m_velocity.y;
        anim->pause = false;
    }

	if(time(NULL) - m_lastDustEffect >= m_timeBetweenDustEffects)
	{
        Vector2 coor;
		coor.x = m_objRect.x + m_objRect.w / 2;
		coor.y = m_objRect.y + m_objRect.h * 8 / 10;
		VisualEffect* dust = new VisualEffect(&(world.m_gameManager.m_configManager.m_dust), coor);
		world.m_gameManager.m_vfxs.push_back(dust);
		m_lastDustEffect = time(NULL);
	}

    // Check if the player is inside or outside the ship
    top.start.x = m_objRect.x;
    top.start.y = m_objRect.y;
    top.finish.x = m_objRect.x + m_objRect.w;
    top.finish.y = m_objRect.y;

    bot.start.x = m_objRect.x;
    bot.start.y = m_objRect.y + m_objRect.h;
    bot.finish.x = m_objRect.x + m_objRect.w;
    bot.finish.y = m_objRect.y + m_objRect.h;

    left.start = top.start;
    left.finish = bot.start;

    right.start = top.finish;
    right.finish = bot.finish;

    if(collLineRect(world.m_gameManager.m_door, top, bot, left, right))
    {
        m_collWithDoor = true;
    }
    else
    {
        if(m_collWithDoor)
        {
            if(world.m_gameManager.m_door.start.y > m_objRect.y)
            {
                m_inSpaceship = true;
            }
            else
            {
                m_inSpaceship = false;
            }
        }
        m_collWithDoor = false;
    }

    // restrict the player from moving outside of the bounds
    restrict(&m_objRect, world.m_gameManager.m_backgroundRect.x, world.m_gameManager.m_backgroundRect.y, world.m_gameManager.m_backgroundRect.w, world.m_gameManager.m_backgroundRect.h);
}

void Player::draw()
{
    m_presentRect =
    {
        (int)((*m_zoom_lvl) * (double)(m_objRect.x - m_camera_rect->x)),
        (int)((*m_zoom_lvl) * (double)(m_objRect.y - m_camera_rect->y)),
        (int)((*m_zoom_lvl) * m_objRect.w),
        (int)((*m_zoom_lvl) * m_objRect.h)
    };

    if(m_oldvelocity.x > 0)
    {
        world.m_gameManager.drawObjectWithSrc(m_objRect, m_srcRect, playerTexture);
    }
    else if(m_oldvelocity.x < 0)
    {
        world.m_gameManager.drawObjectWithSrc(m_objRect, m_srcRect, flipTexture);
    }

    m_healthBar -> draw(world.m_main_renderer);
}

void Player::takeDamage(float damage)
{
    damage -= m_armor;
    if (damage > 0)
    {
        if (m_shield <= 0)
        {
            m_health -= damage;
        }
        else
        {
            m_shield -= damage;
            D(m_shield);
            if (m_shield < 0)
            {
                m_shield = 0;
            }
        }
    }
}

void Player::saveItems(fstream& stream)
{
    cout << "Save armor \n";
    /// Save the armor
    stream << "H " << int(m_helmet) << endl;
    stream << "C " << int(m_chestplate) << endl;
    stream << "L " << int(m_leggings) << endl;
    stream << "B " << int(m_boots) << endl;


    cout << "SAVE WEAPONS \n";
    /// Save the weapons
    stream << "P " << int(m_primaryWeapon) << endl;
    stream << "S " << int(m_secondaryWeapon) << endl;
}

void Player::equipItem(ITEM_TYPE type , ITEM item)
{
    switch (type)
    {
    case ITEM_TYPE::NONE:
        cout << "ERROR: Trying to equip item with unknown type \n";
        break;
    case ITEM_TYPE::HELMET:
        m_helmet = item;
        break;
    case ITEM_TYPE::CHESTPLATE:
        m_chestplate = item;
        break;
    case ITEM_TYPE::LEGGINGS:
        m_leggings = item;
        break;
    case ITEM_TYPE::BOOTS:
        m_boots = item;
        break;
    case ITEM_TYPE::WEAPON:
        m_primaryWeapon = item;
        break;
    case ITEM_TYPE::COLLECTABLE:
        m_collectable.push_back(item);
        break;
    default:
        break;
    }
}

void Player::loadItems(fstream& stream)
{
    string tmp;
    int buff;

    stream >> tmp >> buff;
    m_helmet = ITEM(buff);
    stream >> tmp >> buff;
    m_chestplate = ITEM(buff);
    stream >> tmp >> buff;
    m_leggings = ITEM(buff);
    stream >> tmp >> buff;
    m_boots = ITEM(buff);

    stream >> tmp >> buff;
    m_primaryWeapon = ITEM(buff);
    stream >> tmp >> buff;
    m_secondaryWeapon = ITEM(buff);

    if (m_helmet != ITEM::NONE)
    {
        ItemManager::applyItemEffect(this, m_helmet);
    }
    if (m_chestplate != ITEM::NONE)
    {
        ItemManager::applyItemEffect(this, m_chestplate);
    }
    if (m_leggings != ITEM::NONE)
    {
        ItemManager::applyItemEffect(this, m_leggings);
    }
    if (m_boots != ITEM::NONE)
    {
        ItemManager::applyItemEffect(this, m_boots);
    }
    if (m_primaryWeapon != ITEM::NONE)
    {
        ItemManager::applyItemEffect(this, m_primaryWeapon);
    }
    if (m_secondaryWeapon != ITEM::NONE)
    {
        ItemManager::applyItemEffect(this, m_secondaryWeapon);
    }
}

Vector2 Player::getShootingPoint()
{
    return *m_shootingPoint;
}