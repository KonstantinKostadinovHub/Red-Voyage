#include "GameManager.h"
#include "World.h"

extern World world;

GameManager::GameManager()
{
    world.m_quitScene = false;
    m_saver = nullptr;
}

GameManager::~GameManager()
{

}

void GameManager::init()
{
    m_renderer = world.m_main_renderer;
    m_soundManager = world.m_soundManager;
    m_drag = &world.m_inputManager->m_drag;
    m_mouseIsPressed = &world.m_inputManager->m_mouseIsClicked;
    m_mouseIsDoubleClicked = &world.m_inputManager->m_mouseIsDoubleClicked;
    m_mouseCoordinates = &world.m_inputManager->m_mouseCoor;
    m_event = &world.m_event;

    m_backgroundRect = {
    0,
    0,
    1920 * 3,
    1080 * 3
    };

    string config = "config\\gameManager.txt";

    string shipInsideImg;

    ifstream file;

    file.open(config);

    SDL_StartTextInput();

    if (file.is_open())
    {
        string tmp;

        file >> tmp >> m_backgroundImg;
        file >> tmp >> shipInsideImg;
        file >> tmp >> m_resumeButtonImg;
        file >> tmp >> resumeButton.objRect.w;
        file >> tmp >> resumeButton.objRect.h;

        file >> tmp >> m_pausedBackgroundImg;
        file >> tmp >> m_pausedBackgroundRect.w;
        file >> tmp >> m_pausedBackgroundRect.h;

        file >> tmp >> m_exitButtonImg;
        file >> tmp >> exitButton.objRect.w;
        file >> tmp >> exitButton.objRect.h;

        file.close();
    }

    m_exitButtonImg = MENU_FOLDER + m_exitButtonImg;
    m_resumeButtonImg = MENU_FOLDER + m_resumeButtonImg;

    m_backgroundTexture = LoadTexture(m_backgroundImg, m_renderer);
    m_spaceshipInsideTexture = LoadTexture(shipInsideImg, m_renderer);

    resumeButton.objTexture = LoadTexture(m_resumeButtonImg, m_renderer);
    exitButton.objTexture = LoadTexture(m_exitButtonImg, m_renderer);
    m_pausedBackgroundTexture = LoadTexture(m_pausedBackgroundImg, m_renderer);

    resumeButton.objRect.x = 1920 / 2 - resumeButton.objRect.w - 10;
    resumeButton.objRect.y = 1080 / 2 - resumeButton.objRect.h / 2;

    exitButton.objRect.x = 1920 / 2 + 10;
    exitButton.objRect.y = 1080 / 2 - exitButton.objRect.h / 2;

    m_saver = new Saver("saves\\session1.txt", "saves\\player1.txt");

    m_configManager.init("configManager.txt");
    m_userInterface.load("playerUi.txt");
    m_generator.init("generator.txt");
    readCollisionPoints("collpoints.txt");
    m_tutorial.init("tutorial.txt");
    m_cave.init("cave.txt");
    m_cave.initEntrance("cave_entrance.txt");

}

#pragma region INIT

void GameManager::initSession()
{
    m_food_spawner.init("food.txt");
    addPlayer("player1.txt");
    addPlayer("player2.txt");
    m_saver->loadPlayerStats(m_players[0]);
    Vector2 buff;
    buff.x = 1000;
    buff.y = 1000;
    addItem(ITEM::LEATHER_BOOTS, buff);
 
    m_camera.init(&(m_players[0]->m_objRect), &(m_players[1]->m_objRect));
    
    int taskNumber = rand() % m_generator.m_modelTasks.size();

    int ironNeeded = rand() % 9 + 10;
    int aluminiumNeeded = rand() % 9 + 8;
    int titaniumNeeded = rand() % 9 + 1;

    Task* task = new Task((*m_generator.m_modelTasks[taskNumber]), ironNeeded, titaniumNeeded, aluminiumNeeded);

    m_tasks.push_back(task);

    m_generator.m_lastTaskCreation = chrono::steady_clock::now();

    m_helper = new Helper(&m_players, m_renderer, &(m_camera.zoom_lvl), &(m_camera.camera_rect), &m_bullets);

    if (m_helper->MAX_ORES)
    {
        m_ironCollected = 100;
        m_aluminiumCollected = 100;
        m_titaniumCollected = 100;
    }
}

void GameManager::readCollisionPoints(string configFile)
{
    configFile = "config\\" + configFile;
    ifstream file;
    file.open(configFile);

    Vector2f coor;
    Vector2f first;
    line buff;
    string img;
    file >> img;

    m_spaceshipTexture = LoadTexture(img, m_renderer);

    file >> img >> m_spaceshipRect.x >> m_spaceshipRect.y >> m_spaceshipRect.w >> m_spaceshipRect.h;
    m_spaceshipRect.w *= 1.5;
    m_spaceshipRect.h *= 1.5;
    file >> coor.x >> coor.y;
    coor.x *= 1.5;
    coor.y *= 1.5;
    first = coor;
    while (!file.eof())
    {
        buff.start = coor;
        file >> coor.x >> coor.y;
        coor.x *= 1.5;
        coor.y *= 1.5;
        buff.finish = coor;
        m_collLines.push_back(buff);
    }

    file.close();

    m_door.start = first;
    m_door.start.y = buff.finish.y;
    m_door.finish = buff.finish;
}

#pragma endregion

#pragma region MAIN

void GameManager::update()
{
    checkForPause();

    if (!m_isPaused)
    {
        m_helper->update();

        m_generator.generateOre();
        m_generator.generateEnemy();
        m_generator.generateTask();

        m_animator.updateFrames();

        for (int i = 0; i < m_players.size(); i++)
        {
            m_players[i]->update();
        }

        collision();

        for (int i = 0; i < m_bullets.size(); i++)
        {
            m_bullets[i]->update();
        }

        for (int i = 0; i < m_tasks.size(); i++)
        {
            m_tasks[i]->update();
        }

        for (auto enemy : m_enemies)
        {
            enemy->update();
        }

        for (auto bullet : m_enemyBullets)
        {
            bullet->update();
        }
        m_food_spawner.update_kitchen();

        shoot();

        for (int i = 0; i < m_powerUps.size(); i++)
        {
            m_powerUps[i]->update();
        }

        m_userInterface.update();

        m_tutorial.update();

        m_camera.update();

        for (int i = 0; i < m_players.size(); i++)
        {
            if (collRectRect(m_players[i]->m_objRect, m_cave.m_entranceRect))
            {
                world.m_quitScene = true;
                world.m_gameState = CAVES;
            }
        }

       /* if (world.m_gameState == CAVES)
        {
            m_cave.update();

        }*/

        m_cave.updateEntrance();

        cleaner();

        endGameCheck();  
    }

    m_camera.zoom();
}

void GameManager::draw()
{
    SDL_RenderClear(m_renderer);

    drawObject(m_backgroundRect, m_backgroundTexture);

    if (isPlayerInShip())
    {
        drawObject(m_spaceshipRect, m_spaceshipInsideTexture);
    }
    else
    {
        drawObject(m_spaceshipRect, m_spaceshipTexture);
    }

    for (int i = 0; i < m_tasks.size(); i++)
    {
        m_tasks[i]->draw();
    }

    for (int i = 0; i < 6; i++) {
        if (chicken_wings[i] != nullptr) {
            chicken_wings[i]->draw();
        }
    }
    ///CAVE ENTRANCE DRAW
    m_cave.drawEntrance();

    for (int i = 0; i < m_ores.size(); i++)
    {
        m_ores[i]->draw();
    }

    for (int i = 0; i < m_players.size(); i++)
    {
        m_players[i]->draw();
    }

    for (auto enemy : m_enemies) {
        enemy->draw();
    }

    for (int i = 0; i < m_bullets.size(); i++)
    {
        m_bullets[i]->draw(m_renderer);
    }

    for (auto bullet : m_enemyBullets) {
        bullet->draw(m_renderer);
    }

    for (int i = 0; i < m_items.size(); i++)
    {
        m_items[i]->draw();
    }

    for (int i = 0; i < m_vfxs.size(); i++)
    {
        m_vfxs[i]->draw();
    }

    if (m_helper->SHOW_ALL_RECTS)
    {
        drawShipCollision();

        for (int i = 0; i < 6; i++)
        {
            if (chicken_wings[i] != nullptr)
            {
                m_helper->drawCollision(chicken_wings[i]->wing_rect);
            }
        }

        for (int i = 0; i < m_ores.size(); i++)
        {
            m_helper->drawCollision(m_ores[i]->m_rect);
        }

        for (int i = 0; i < m_players.size(); i++)
        {
            m_helper->drawCollision(m_players[i]->m_objRect);
        }

        for (auto enemy : m_enemies) {
            m_helper->drawCollision(enemy->m_objectRect);
        }

        for (int i = 0; i < m_bullets.size(); i++)
        {
            m_helper->drawCollision(m_bullets[i]->m_objRect);
        }

        for (auto bullet : m_enemyBullets) {
            m_helper->drawCollision(bullet->m_objectRect);
        }

        for (auto item : m_items) {
            m_helper->drawCollision(item->getRect());
        }

        for (int i = 0; i < m_vfxs.size(); i++)
        {
            m_helper->drawCollision(m_vfxs[i]->m_objectRect);
        }

        m_helper->drawCollision(m_cave.m_entranceRect);
    }

    //m_userInterface.draw();

    for (int i = 0; i < m_players.size(); i++)
    {
        m_players[i]->m_healthBar->draw(m_renderer);
    }

    m_tutorial.draw();

    if (m_isPaused)
    {
        SDL_RenderCopy(m_renderer, m_pausedBackgroundTexture, NULL, NULL);
        SDL_RenderCopy(m_renderer, resumeButton.objTexture, NULL, &resumeButton.objRect);
        SDL_RenderCopy(m_renderer, exitButton.objTexture, NULL, &exitButton.objRect);
    }


    m_enterName->draw();

    SDL_RenderPresent(m_renderer);
}

#pragma endregion

bool GameManager::collisionWithShip(SDL_Rect rect)
{
    line top, bot, left, right;

    top.start.x = rect.x;
    top.start.y = rect.y;
    top.finish.x = rect.x + rect.w;
    top.finish.y = rect.y;

    bot.start.x = rect.x;
    bot.start.y = rect.y + rect.h;
    bot.finish.x = rect.x + rect.w;
    bot.finish.y = rect.y + rect.h;

    left.start = top.start;
    left.finish = bot.start;

    right.start = top.finish;
    right.finish = bot.finish;

    for (int i = 0; i < m_collLines.size(); i++)
    {
        if (collLineRect(m_collLines[i], top, bot, left, right)) return true;
    }
    return false;
}

bool GameManager::collisionWithShip(line collLine)
{
    for (int i = 0; i < m_collLines.size(); i++)
    {
        if (collLineLine(m_collLines[i], collLine)) return true;
    }
    return false;
}

bool GameManager::isPlayerInShip()
{
    SDL_Rect ship = { 0, 0, 2880, 1620 };

    bool isInside = false;

    for (int i = 0; i < m_players.size(); i++)
    {
        if (collRectRect(ship, m_players[i]->m_objRect))
        {
            isInside = true;
        }
    }
    return isInside;
}

void GameManager::addPlayer(string configFile)
{
    if (configFile == "player1.txt")
    {
        Player* player1 = new Player();
        player1->init(m_renderer, configFile);
        m_players.push_back(player1);
    }
    else if (configFile == "player2.txt")
    {
        Player* player2 = new Player();
        player2->init(m_renderer, configFile);
        m_players.push_back(player2);
    }
}

void GameManager::addBullet(Vector2 coor, float angle)
{
    Bullet* bullet = new Bullet(&m_configManager.m_bullet, m_renderer, angle);
    bullet->m_objRect.x = coor.x;
    bullet->m_objRect.y = coor.y;
    bullet->m_coor.x = bullet->m_objRect.x;
    bullet->m_coor.y = bullet->m_objRect.y;
    bullet->collLine.start.x = coor.x - 10;
    bullet->collLine.start.y = coor.y - 10;
    bullet->collLine.finish.x = coor.x;
    bullet->collLine.finish.y = coor.y;
    m_bullets.push_back(bullet);
}

void GameManager::shoot()
{
    for (int i = 0; i < m_players.size(); i++)
    {
        if (m_players[i]->m_gun->m_canShoot)
        {
            addBullet(m_players[i]->getShootingPoint(), m_players[i]->m_gun->m_rotationAngle);
            m_soundManager->play("Shoot.mp3");
            m_players[i]->m_gun->m_elapsed_engage = chrono::high_resolution_clock::now();
        }
    }
}

void GameManager::cleaner()
{
    /*! Cleans all the used/dead objects from the game
        It deletes the object, then removes it from the scene and from the vector
    */
    for (int i = 0; i < m_players.size(); i++)
    {
        if (m_players[i]->m_health <= 0)
        {
            m_soundManager->play("Player_Death.mp3");

            delete m_players[i];
            m_players.erase(m_players.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < m_enemies.size(); i++) {
        if (m_enemies[i]->m_health <= 0)
        {
            delete m_enemies[i];
            m_enemies.erase(m_enemies.begin() + i);
            i--;
            m_soundManager->play("Enemy_Death.mp3");
        }
    }

    for (int i = 0; i < m_bullets.size(); i++)
    {
        if (collisionWithShip(m_bullets[i]->collLine)) {
            m_bullets[i]->m_health = 0;
        }
        if (m_bullets[i]->m_health <= 0 || checkInOffBounds(m_bullets[i]->m_objRect, m_backgroundRect.w, m_backgroundRect.h))
        {
            m_bullets[i]->m_objRect.x = m_bullets[i]->collLine.finish.x;
            m_bullets[i]->m_objRect.y = m_bullets[i]->collLine.finish.y;
            Vector2 coorBuff;
            coorBuff.x = m_bullets[i]->m_objRect.x;
            coorBuff.y = m_bullets[i]->m_objRect.y;
            VisualEffect* explosion = new VisualEffect(&(m_configManager.m_bulletExplosion), coorBuff);
            m_vfxs.push_back(explosion);
            delete m_bullets[i];
            m_bullets.erase(m_bullets.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < m_ores.size(); i++) {
        if (m_ores[i]->m_health <= 0) {
            if (m_ores[i]->m_type == IRON)
            {
                m_ironCollected++;
            }
            else if (m_ores[i]->m_type == ALUMINIUM)
            {
                m_aluminiumCollected++;
            }
            else if (m_ores[i]->m_type == TITANIUM)
            {
                m_titaniumCollected++;
            }
            delete m_ores[i];
            m_ores.erase(m_ores.begin() + i);
            i--;
        }
    }

    for (int i = 0; i < m_tasks.size(); i++)
    {
        if (m_tasks[i]->m_doneTask)
        {
            delete m_tasks[i];
            m_tasks.erase(m_tasks.begin() + i);
            i--;
        }
    }

    for (short i = 0; i < m_vfxs.size(); i++)
    {
        if (m_vfxs[i]->anim->finished)
        {
            delete m_vfxs[i];
            m_vfxs.erase(m_vfxs.begin() + i);
            i--;
        }
    }

    for (short i = 0; i < m_animator.m_animations.size(); i++)
    {
        if (m_animator.m_animations[i]->finished)
        {
            delete m_animator.m_animations[i];
            m_animator.m_animations.erase(m_animator.m_animations.begin() + i);
            i--;
        }
    }

    for (short i = 0; i < m_powerUps.size(); i++)
    {
        if (m_powerUps[i]->m_destroyEffect)
        {
            delete m_powerUps[i];
            m_powerUps.erase(m_powerUps.begin() + i);
            i--;
        }
    }
}

void GameManager::deleteSession()
{
    /*! After a session is used, delete all the objects in order to save memory.

    */
    for (int i = 0; i < m_players.size(); i++)
    {
        delete m_players[i];
    }
    m_players.clear();

    for (int i = 0; i < m_enemies.size(); i++)
    {
        delete m_enemies[i];
    }
    m_enemies.clear();

    for (int i = 0; i < m_bullets.size(); i++)
    {
        delete m_bullets[i];
    }
    m_bullets.clear();

    for (int i = 0; i < m_enemyBullets.size(); i++)
    {
        delete m_enemyBullets[i];
    }
    m_enemyBullets.clear();

    for (int i = 0; i < m_tasks.size(); i++)
    {
        delete m_tasks[i];
    }
    m_tasks.clear();

    for (int i = 0; i < m_ores.size(); i++)
    {
        delete m_ores[i];
    }
    m_ores.clear();

    for (int i = 0; i < m_animator.m_animations.size(); i++)
    {
        delete  m_animator.m_animations[i];
    }
    m_animator.m_animations.clear();

    for (int i = 0; i < m_vfxs.size(); i++)
    {
        delete m_vfxs[i];
    }
    m_vfxs.clear();

    for (int i = 0; i < m_powerUps.size(); i++)
    {
        delete m_powerUps[i];
    }
    m_powerUps.clear();

    m_ironCollected = 0;
    m_chickenCollected = 0;
    m_aluminiumCollected = 0;
    m_titaniumCollected = 0;

    //delete &m_camera;

    m_isPaused = false;
}

void GameManager::endGameCheck()
{
    if (m_tasks.size() == 0) {
        win = 1;
        m_soundManager->play("Win.mp3");
        world.m_gameState = ENDGAME;
        world.m_quitScene = true;
    }

    if (m_players.size() == 0)
    {
        m_soundManager->play("Lose.mp3");

        win = -1;
        world.m_gameState = ENDGAME;
        world.m_quitScene = true;
    }
}

void GameManager::drawObject(SDL_Rect rect, SDL_Texture* texture)
{
    /*! Draw an object with camera view. It will take in consideration the camera's position and zoom level.
        This function doesn't work with animated objects
    */
    m_presentRect = {
        (int)(m_camera.zoom_lvl * (double)(rect.x - m_camera.camera_rect.x)),
        (int)(m_camera.zoom_lvl * (double)(rect.y - m_camera.camera_rect.y)),
        (int)(m_camera.zoom_lvl * rect.w),
        (int)(m_camera.zoom_lvl * rect.h),
    };

    SDL_RenderCopy(m_renderer, texture, NULL, &m_presentRect);
}

void GameManager::drawObjectWithSrc(SDL_Rect dstRect, SDL_Rect srcRect, SDL_Texture* texture)
{
    /*! Draw an object with camera view. It will take in consideration the camera's position and zoom level
        Pass the srcRect if the object has animation
    */
    m_presentRect = {
        (int)(m_camera.zoom_lvl * (double)(dstRect.x - m_camera.camera_rect.x)),
        (int)(m_camera.zoom_lvl * (double)(dstRect.y - m_camera.camera_rect.y)),
        (int)(m_camera.zoom_lvl * dstRect.w),
        (int)(m_camera.zoom_lvl * dstRect.h),
    };

    SDL_RenderCopy(m_renderer, texture, &srcRect, &m_presentRect);
}

void GameManager::collision()
{
    /*! Checks for collision and makes following decisions - taking health, sometimes marking the object for delete or deleting it
    */
    for (int j = 0; j < m_players.size(); j++)
    {
        for (int i = 0; i < m_items.size(); i++)
        {
            if (collRectRect(m_items[i]->getRect(), m_players[j]->m_objRect))
            {
                m_items[i]->onPick(m_players[i]);
                delete m_items[i];
                m_items.erase(m_items.begin() + i);
                i--;
            }
        }
        for (int i = 0; i < 4; i++) {
            if (chicken_wings[i] != nullptr) {
                if (collRectRect(chicken_wings[i]->wing_rect, m_players[j]->m_objRect)) {

                    m_soundManager->play("Food.mp3");
                    m_chickenCollected++;

                    ChickenBuff* chickenBuff = new ChickenBuff(&(m_configManager.m_chickenBuff));
                    chickenBuff->player = m_players[j];
                    m_powerUps.push_back(chickenBuff);

                    delete chicken_wings[i];
                    chicken_wings[i] = nullptr;
                    break;
                }
                else
                {
                    m_chickenCollected = false;
                }
            }
        }
    }

    for (int i = 0; i < m_bullets.size(); i++)
    {
        for (int j = 0; j < m_ores.size(); j++) {
            if (collRectRect(m_bullets[i]->m_objRect, m_ores[j]->m_rect)) {
                m_ores[j]->m_health -= m_bullets[i]->m_damage;
                m_bullets[i]->m_health--;
                m_soundManager->play("Mine.mp3");
            }
        }
        for (int j = 0; j < m_enemies.size(); j++) {
            if (collRectRect(m_bullets[i]->m_objRect, m_enemies[j]->m_objectRect)) {
                m_enemies[j]->m_health -= m_bullets[i]->m_damage;
                m_bullets[i]->m_health--;
                m_soundManager->play("Mine.mp3");
            }
        }
    }
    for (int i = 0; i < m_enemyBullets.size(); i++)
    {
        buffBool = true;
        if (collisionWithShip(m_enemyBullets[i]->m_objectRect)) {
            delete m_enemyBullets[i];
            m_enemyBullets.erase(m_enemyBullets.begin() + i);
            i--;
            buffBool = false;
        }
        for (int j = 0; j < m_players.size() && buffBool; j++)
        {
            if (collRectRect(m_enemyBullets[i]->m_objectRect, m_players[j]->m_objRect))
            {
                m_players[j]->takeDamage(m_enemyBullets[i]->m_damage);
                delete m_enemyBullets[i];
                m_enemyBullets.erase(m_enemyBullets.begin() + i);
                m_camera.shake();
                i--;
                buffBool = false;
            }
        }
        if (buffBool)
        {
            if (checkInOffBounds(m_enemyBullets[i]->m_objectRect, m_backgroundRect.w, m_backgroundRect.h))
            {
                buffBool = false;
                delete m_enemyBullets[i];
                m_enemyBullets.erase(m_enemyBullets.begin() + i);
                i--;
            }
        }
        if (buffBool)
        {
            for (int j = 0; j < m_ores.size(); j++) {
                if (collRectRect(m_enemyBullets[i]->m_objectRect, m_ores[j]->m_rect)) {
                    delete m_enemyBullets[i];
                    m_enemyBullets.erase(m_enemyBullets.begin() + i);
                    i--;
                    buffBool = false;
                    break;
                }
            }
        }
    }

    for (int i = 0; i < m_players.size(); i++)
    {
        if (world.m_inputManager->m_shootIsPressed)
        {
            for (int j = 0; j < m_enemies.size(); j++)
            {
                x = abs(m_players[i]->m_objRect.x + m_players[i]->m_objRect.w / 2 - m_enemies[j]->m_objectRect.x - m_enemies[j]->m_objectRect.w / 2);
                y = abs(m_players[i]->m_objRect.y + m_players[i]->m_objRect.h / 2 - m_enemies[j]->m_objectRect.y - m_enemies[j]->m_objectRect.h / 2);

                m_distance = sqrt(x * x + y * y);

                if (m_distance > m_players[i]->m_distance)
                {
                    continue;
                }
                else
                {
                    m_directionCoor.x = m_enemies[j]->m_objectRect.x - m_players[i]->m_objRect.x;
                    m_directionCoor.y = m_enemies[j]->m_objectRect.y - m_players[i]->m_objRect.y;

                    m_angle = returnAngleByCoordinates(m_directionCoor);

                    if (m_players[i]->m_gun->m_oldVelocity.x == 1 && m_players[i]->m_gun->m_oldVelocity.y == 0)
                    {
                        if (m_angle >= -67.5f && m_angle <= 67.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "right" << endl;
                        }
                    }
                    else if (m_players[i]->m_gun->m_oldVelocity.x == -1 && m_players[i]->m_gun->m_oldVelocity.y == 0)
                    {
                        if (m_angle <= -112.5 || m_angle >= 112.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "left" << endl;
                        }
                    }
                    else if (m_players[i]->m_gun->m_oldVelocity.x == 0 && m_players[i]->m_gun->m_oldVelocity.y == 1)
                    {
                        if (m_angle <= 157.5f && m_angle >= 22.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "down" << endl;
                        }
                    }
                    else if (m_players[i]->m_gun->m_oldVelocity.x == 0 && m_players[i]->m_gun->m_oldVelocity.y == -1)
                    {
                        if (m_angle >= -157.5f && m_angle <= -22.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "up" << endl;
                        }
                    }
                    else if (m_players[i]->m_gun->m_oldVelocity.x == 1 && m_players[i]->m_gun->m_oldVelocity.y == 1)
                    {
                        if (m_angle >= 22.5f && m_angle <= 112.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "down right" << endl;
                        }
                    }
                    else if (m_players[i]->m_gun->m_oldVelocity.x == -1 && m_players[i]->m_gun->m_oldVelocity.y == -1)
                    {
                        if (m_angle >= 157.5f || m_angle <= -67.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "up left" << endl;
                        }
                    }
                    else if (m_players[i]->m_gun->m_oldVelocity.x == -1 && m_players[i]->m_gun->m_oldVelocity.y == 1)
                    {
                        if (m_angle <= -157.5f || m_angle >= 67.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "down left" << endl;
                        }
                    }
                    else if (m_players[i]->m_gun->m_oldVelocity.x == 1 && m_players[i]->m_gun->m_oldVelocity.y == -1)
                    {
                        if (m_angle >= -112.5f && m_angle <= 22.5f)
                        {
                            m_players[i]->m_gun->m_canShoot = false;
                            m_enemies[j]->m_health -= m_players[i]->m_dmg;
                            //cout << "up right" << endl;
                        }
                    }
                }
            }
        }
    }
}

bool GameManager::checkForPause()
{
    const Uint8* state = SDL_GetKeyboardState(NULL);
    SDL_PollEvent(m_event);

    if (state[SDL_SCANCODE_ESCAPE] && !m_isPaused)
    {
        m_isPaused = true;
        m_saver->saveSession();
        return true;
    }
    else if (*m_mouseIsPressed && (MouseIsInRect(*m_mouseCoordinates, resumeButton.objRect) && m_isPaused) && m_isPaused)
    {
        m_soundManager->play("Button_Click.mp3");
        m_isPaused = false;
        return false;
    }
    if (*m_mouseIsPressed && (MouseIsInRect(*m_mouseCoordinates, exitButton.objRect)) && m_isPaused)
    {
        m_soundManager->play("Button_Click.mp3");
        world.m_quitScene = true;
        world.m_gameState = MENU;
    }
}

void GameManager::drawShipCollision()
{
    line a;

    for (int i = 0; i < m_collLines.size(); i++)
    {
        a = m_collLines[i];
        SDL_RenderDrawLine(m_renderer, (int)(m_camera.zoom_lvl * (float)(a.start.x - m_camera.camera_rect.x)), (int)(m_camera.zoom_lvl * (float)(a.start.y - m_camera.camera_rect.y)), (int)(m_camera.zoom_lvl * (float)(a.finish.x - m_camera.camera_rect.x)), (int)(m_camera.zoom_lvl * (float)(a.finish.y - m_camera.camera_rect.y)));
    }
}

void GameManager::addItem(ITEM type, Vector2 coor)
{
    Item* item = nullptr;
    switch (type)
    {
    case ITEM::LEATHER_BOOTS:
        item = new LeatherBoots(m_configManager.m_leatherBoots);
        break;
    }
    if (item)
    {
        item->setPos(coor);
        m_items.push_back(item);
    }
    else
    {
        string errorText = "error: trying to create an item with unknown type in line: " + to_string(__LINE__) + " in file " + __FILE__;
        fprintf(stderr, errorText.c_str());
        exit(EXIT_FAILURE);
    }
}

SDL_Rect GameManager::toScreenCoordinates(SDL_Rect rect)
{
    return {
        (int)(m_camera.zoom_lvl * (double)(rect.x - m_camera.camera_rect.x)),
        (int)(m_camera.zoom_lvl * (double)(rect.y - m_camera.camera_rect.y)),
        (int)(m_camera.zoom_lvl * rect.w),
        (int)(m_camera.zoom_lvl * rect.h),
    };
}
