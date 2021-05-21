#include "World.h"
#include <windows.h>
#include <fstream>
#include <iostream>

using namespace std;


World::World()
{
    m_endGame = false;
    m_quitScene = false;
    m_main_renderer = nullptr;
    m_main_window = nullptr;
    m_soundManager = new SoundManager;

    m_ironCollected = 110;
    m_aluminiumCollected = 110;
    m_titaniumCollected = 110;
}

World::~World()
{
    //dtor
}

void World::init()
{

    srand(time(NULL));

    m_SCREEN_WIDTH = 1920;
    m_SCREEN_HEIGHT = 1080;

    m_backgroundRect = {
        0,
        0,
        1920 * 3,
        1080 * 3
    };

    SDL_Init(SDL_INIT_EVERYTHING);
    TTF_Init();
    m_main_window = SDL_CreateWindow("Red Voyage", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED, 1366, 768, 0);
	m_main_renderer = SDL_CreateRenderer(m_main_window, -1, SDL_RENDERER_PRESENTVSYNC);
    improveRenderer();

    string config = "config\\world.txt";

    string titleScreenImg, shipInsideImg, cursorImg;

    ifstream file;

	file.open(config);

	if(file.is_open())
	{ 
	
		string tmp;
		file >> tmp >> m_backgroundImg;
		file >> tmp >> titleScreenImg;
		file >> tmp >> shipInsideImg;
		file >> tmp >> cursorImg;
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

    m_backgroundTexture = LoadTexture(m_backgroundImg, m_main_renderer);
    m_titleScreenTexture = LoadTexture(titleScreenImg, m_main_renderer);
    m_spaceshipInsideTexture = LoadTexture(shipInsideImg, m_main_renderer);

    resumeButton.objTexture = LoadTexture(m_resumeButtonImg, m_main_renderer);
    exitButton.objTexture = LoadTexture(m_exitButtonImg, m_main_renderer);
    m_pausedBackgroundTexture = LoadTexture(m_pausedBackgroundImg, m_main_renderer);

    resumeButton.objRect.x = 1920 / 2 - resumeButton.objRect.w - 10;
    resumeButton.objRect.y = 1080 / 2 - resumeButton.objRect.h / 2;

    exitButton.objRect.x = 1920 / 2 + 10;
    exitButton.objRect.y = 1080 / 2 - exitButton.objRect.h / 2;


    m_configManager.init("configManager.txt");
    m_menu.load("menu.txt");
    m_userInterface.load("ui.txt");
    m_generator.init("generator.txt");
    m_soundManager -> init("soundManager.txt");
   // m_soundManager -> play("Background_Music.mp3");
    readCollisionPoints("collpoints.txt");
    m_tutorial.init("tutorial.txt");

    cursorImg = "img\\" + cursorImg;

    SDL_Surface* loadSurface = SDL_LoadBMP((cursorImg.c_str()));
    SDL_Cursor* cursor = SDL_CreateColorCursor(loadSurface, 10, 5);
    SDL_SetCursor(cursor);

    loadSurface = nullptr;
    cursor = nullptr;

}

void World::initSession()
{
    m_food_spawner.init("food.txt");
    addPlayer("player1.txt");
    addPlayer("player2.txt");
    int taskNumber = rand() % m_generator.m_modelTasks.size();

    int ironNeeded = rand() % 9 + 10;
    int titaniumNeeded = rand() % 9 + 1;
    int aluminiumNeeded = rand() % 9 + 8;

    Task* task = new Task((*m_generator.m_modelTasks[taskNumber]), ironNeeded, titaniumNeeded, aluminiumNeeded);

    m_tasks.push_back(task);

    m_soundManager->play("Show_Task.mp3");

    m_generator.m_lastTaskCreation = chrono::steady_clock::now();
}

void World::input()
{
    m_mouseIsPressed = false;
    m_mouseIsDoubleClicked = false;

    SDL_PollEvent(&m_event);

    if(m_event.type == SDL_MOUSEBUTTONDOWN)
    {
        if (m_event.button.clicks >= 2)
        {
            m_mouseIsDoubleClicked = true;
        }

        m_mouseIsPressed = true;
    }

    if(m_event.type == SDL_MOUSEMOTION)
    {
        SDL_GetGlobalMouseState(&(m_mouseCoordinates.x), &(m_mouseCoordinates.y));
        m_mouseCoordinates.x *= m_MOUSE_MULTIPLY_X;
        m_mouseCoordinates.y *= m_MOUSE_MULTIPLY_Y;
    }

    m_camera.zoom();
}

void World::improveRenderer()
{
    SDL_DisplayMode DM;
    SDL_GetCurrentDisplayMode(0, &DM);
    auto desktopWidth = DM.w;
    auto desktopHeight = DM.h;

    m_MOUSE_MULTIPLY_X = (double) m_SCREEN_WIDTH / (double)desktopWidth;
    m_MOUSE_MULTIPLY_Y = (double) m_SCREEN_HEIGHT / (double)desktopHeight;


    if(SDL_SetWindowFullscreen(m_main_window, SDL_WINDOW_FULLSCREEN_DESKTOP) < 0)
    {
        cout << "SDL_IMPROVE_RENDERER FAILED: %s\n" << SDL_GetError() << endl;
    }


    SDL_RenderSetLogicalSize(m_main_renderer, 1920, 1080);
    SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "1");
}

void World::destroy()
{
    m_gameState = NONE;
    SDL_DestroyWindow(m_main_window);
    SDL_DestroyRenderer(m_main_renderer);
    m_soundManager -> destroyChunks();
}

void World::update()
{

    checkForPause();
    if(!m_isPaused)
    {
        m_generator.generateOre();
        m_generator.generateEnemy();
        m_generator.generateTask();

        m_animator.updateFrames();

		cout << __LINE__ << endl;

        for(int i = 0; i < m_players.size(); i ++)
        {
            m_players[i] -> update();
        }
		cout << __LINE__ << endl;

        for(int i = 0; i < m_bullets.size(); i ++)
        {
            m_bullets[i] -> update();
        }

        for(int i = 0; i < m_tasks.size(); i ++)
        {
            m_tasks[i] -> update();
        }

        for (auto enemy: m_enemies) {
            enemy->update();
        }
        for (auto bullet: m_enemyBullets) {
            bullet->update();
        }

        m_food_spawner.update_kitchen();
		cout << __LINE__ << endl;

        shoot();

        collision();

        m_userInterface.update();
		cout << __LINE__ << endl;

        m_tutorial.update();

        m_camera.update();
		cout << __LINE__ << endl;

        cleaner();

        endGameCheck();
		cout << __LINE__ << endl;

    }
}

void World::draw()
{
    SDL_RenderClear(m_main_renderer);

    drawObject(m_backgroundRect, m_backgroundTexture);

    if(isPlayerInShip())
    {
        drawObject(m_spaceshipRect, m_spaceshipInsideTexture);
    }
    else
    {
        drawObject(m_spaceshipRect, m_spaceshipTexture);
    }

    for(int i = 0; i < m_tasks.size(); i ++)
    {
        m_tasks[i] -> draw();
    }

    for(int i = 0; i < 6; i++){
        if(chicken_wings[i] != nullptr){
            chicken_wings[i]->draw();
        }
    }

    for(int i = 0; i < m_ores.size(); i ++)
    {
        m_ores[i]->draw();
    }

    for(int i = 0; i < m_players.size(); i ++)
    {
        m_players[i] -> draw();
    }

    for (auto enemy: m_enemies) {
        enemy->draw();
    }

    for(int i = 0; i < m_bullets.size(); i ++)
    {
        m_bullets[i] -> draw(m_main_renderer);
    }

    for (auto bullet: m_enemyBullets) {
        bullet->draw(m_main_renderer);
    }

	//drawShipCollision();

    m_userInterface.draw();

    for(int i = 0; i < m_players.size(); i ++)
    {
        m_players[i] -> m_healthBar -> draw(m_main_renderer);
    }

    m_tutorial.draw();

    if(m_isPaused)
    {
        SDL_RenderCopy(m_main_renderer, m_pausedBackgroundTexture, NULL , NULL);
        SDL_RenderCopy(m_main_renderer, resumeButton.objTexture, NULL , &resumeButton.objRect);
        SDL_RenderCopy(m_main_renderer, exitButton.objTexture, NULL , &exitButton.objRect);
    }

    SDL_RenderPresent(m_main_renderer);
}

void World::readCollisionPoints(string configFile)
{
    configFile = "config\\" + configFile;
    ifstream file;
    file.open(configFile);

    fcoordinates coor;
    fcoordinates first;
    line buff;
    string img;
    file >> img;

    m_spaceshipTexture = LoadTexture(img, m_main_renderer);


    file >> img >> m_spaceshipRect.x >> m_spaceshipRect.y >> m_spaceshipRect.w >> m_spaceshipRect.h;
    m_spaceshipRect.w *= 1.5;
    m_spaceshipRect.h *= 1.5;
    file >> coor.x >> coor.y;
    coor.x *= 1.5;
    coor.y *= 1.5;
    first = coor;
    while(!file.eof())
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

bool World::collisionWithShip(SDL_Rect rect)
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

    for(int i = 0; i < m_collLines.size(); i++)
    {
        if(collLineRect(m_collLines[i], top, bot, left, right)) return true;
    }
    return false;
}

bool World::collisionWithShip(line collLine)
{
    for(int i = 0; i < m_collLines.size(); i++)
    {
        if(collLineLine(m_collLines[i], collLine)) return true;
    }
    return false;
}

bool World::isPlayerInShip(){
    SDL_Rect ship = {0, 0, 2880, 1620};
    if(collRectRect(ship, m_players[0] -> m_objRect)){
        return 1;
    }else if(collRectRect(ship, m_players[1] -> m_objRect)){
        return 1;
    }else{
        return 0;
    }
}

void World::addPlayer(string configFile)
{
    if(configFile == "player1.txt")
    {
        Player* player1 = new Player();
        player1 -> init(m_main_renderer, configFile);
        m_players.push_back(player1);
    }
    else if(configFile == "player2.txt")
    {
        Player* player2 = new Player();
        player2 -> init(m_main_renderer, configFile);
        m_players.push_back(player2);
    }
}

void World::addBullet(SDL_Rect rect, coordinates coor)
{
    Bullet* bullet = new Bullet(&m_configManager.m_bullet, m_main_renderer, coor);
    bullet -> m_objRect.x = rect.x;
    bullet -> m_objRect.y = rect.y;
    bullet -> m_coor.x = rect.x;
    bullet -> m_coor.y = rect.y;
    bullet -> collLine.start.x = rect.x;
    bullet -> collLine.start.y = rect.y;
    bullet -> collLine.finish.x = rect.x;
    bullet -> collLine.finish.y = rect.y;
    m_bullets.push_back(bullet);
}


void World::shoot()
{
    for(int i = 0; i < m_players.size(); i ++)
    {
        for(int j = 0; j < m_players[i] -> m_guns.size(); j ++)
        {
            if(m_players[i] -> m_guns[j] -> m_canShoot)
            {
                addBullet(m_players[i] -> m_guns[j] -> m_objRect, m_players[i] -> m_guns[j] -> m_oldVelocity);
                m_players[i] -> m_guns[j] -> m_elapsed_engage = chrono::high_resolution_clock::now();
            }
        }
    }
}

void World::cleaner()
{
	/*! Cleans all the used/dead objects from the game
		It deletes the object, then removes it from the scene and from the vector
	*/
    for(int i = 0; i < m_players.size(); i ++)
    {
        if(m_players[i] -> m_health <= 0)
        {
            m_soundManager -> play("Player_Death.mp3");

            delete m_players[i];
            m_players.erase(m_players.begin() + i);
            i--;
        }
    }

    for(int i = 0; i < m_enemies.size(); i ++){
        if(m_enemies[i] -> m_health <= 0)
        {
            m_soundManager -> play("Enemy_Death.mp3");

            delete m_enemies[i];
            m_enemies.erase(m_enemies.begin() + i);
            i --;
        }
    }
    for(int i = 0; i < m_bullets.size(); i ++)
    {
        if(collisionWithShip(m_bullets[i]->collLine)){
            m_bullets[i] -> m_health --;
        }
        if(m_bullets[i] -> m_health <= 0 || checkInOffBounds(m_bullets[i] -> m_objRect, m_backgroundRect.w, m_backgroundRect.h))
        {
            delete m_bullets[i];
            m_bullets.erase(m_bullets.begin() + i);
            i --;
        }
    }

    for(int i = 0; i < m_ores.size(); i++){
        if(m_ores[i] -> m_health <= 0){
            if(m_ores[i] -> m_type == IRON)
            {
                m_ironCollected ++;
            }else if(m_ores[i] -> m_type == ALUMINIUM)
            {
                m_aluminiumCollected ++;
            }else if(m_ores[i] -> m_type == TITANIUM)
            {
                m_titaniumCollected ++;
            }
            delete m_ores[i];
            m_ores.erase(m_ores.begin() + i);
            i --;
        }
    }

    for(int i = 0; i < m_tasks.size(); i++)
    {
        if(m_tasks[i]->m_doneTask)
        {
            delete m_tasks[i];
            m_tasks.erase(m_tasks.begin() + i);
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
}

void World::loadTitleScreen()
{
    SDL_RenderCopy(m_main_renderer, m_titleScreenTexture, NULL, NULL);
    SDL_RenderPresent(m_main_renderer);
    SDL_Delay(3000);
}

void World::deleteSession()
{
	/*! After a session is used, delete all the objects in order to save memory.
		
	*/
    for(int i = 0; i < m_players.size(); i++)
    {
        delete m_players[i];
    }
    m_players.clear();

    for(int i = 0; i < m_enemies.size(); i++)
    {
        delete m_enemies[i];
    }
    m_enemies.clear();

    for(int i = 0; i < m_bullets.size(); i++)
    {
        delete m_bullets[i];
    }
    m_bullets.clear();

    for(int i = 0; i < m_enemyBullets.size(); i++)
    {
        delete m_enemyBullets[i];
    }
    m_enemyBullets.clear();

    for(int i = 0; i < m_tasks.size(); i++)
    {
        delete m_tasks[i];
    }
    m_tasks.clear();

    for(int i = 0; i < m_ores.size(); i++)
    {
        delete m_ores[i];
    }
    m_ores.clear();

    for(int i = 0; i < m_animator.m_animations.size(); i++)
    {
        delete  m_animator.m_animations[i];
    }
    m_animator.m_animations.clear();

    m_ironCollected = 0;
    m_chickenCollected = 0;
    m_aluminiumCollected = 0;
    m_titaniumCollected = 0;

    m_isPaused = false;
}

void World::endGameCheck()
{
    if(m_tasks.size() == 0){
        win = 1;
        m_soundManager -> play("Win.mp3");
        m_gameState = ENDGAME;
        m_quitScene = true;
    }

    if(m_players.size() == 0)
    {
        m_soundManager -> play("Lose.mp3");

        win = -1;
        m_gameState = ENDGAME;
        m_quitScene = true;
    }
}

void World::drawObject(SDL_Rect rect, SDL_Texture* texture)
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

    SDL_RenderCopy(m_main_renderer, texture, NULL, &m_presentRect);
}

void World::drawObjectWithSrc(SDL_Rect dstRect,SDL_Rect srcRect, SDL_Texture* texture)
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

    SDL_RenderCopy(m_main_renderer, texture, &srcRect, &m_presentRect);
}

void World::collision()
{
	/*! Checks for collision and makes following decisions - taking health, sometimes marking the object for delete or deleting it
	*/
    for(int i = 0; i < 6; i++){
        if(chicken_wings[i] != nullptr){
            if(collRectRect(chicken_wings[i]->wing_rect, m_players[0]->m_objRect)){

                m_soundManager->play("Food.mp3");
                m_players[0]->m_health += chicken_wings[i]->regen_amount;
                m_chickenCollected++;

                delete chicken_wings[i];
                chicken_wings[i] = nullptr;
                break;
            }
            if(collRectRect(chicken_wings[i]->wing_rect, m_players[1]->m_objRect)){
                m_soundManager->play("Food.mp3");

                m_players[1]->m_health += chicken_wings[i]->regen_amount;
                m_chickenCollected++;

                delete chicken_wings[i];
                chicken_wings[i] = nullptr;
                break;
            }
        }
    }
    for(int i = 0; i < m_bullets.size(); i ++)
    {
        for(int j = 0; j < m_ores.size(); j++){
            if(collRectRect(m_bullets[i] -> m_objRect, m_ores[j] -> m_rect)){
                m_ores[j] -> m_health -= m_bullets[i] -> m_damage;
                m_bullets[i] -> m_health --;
                m_soundManager->play("Mine.mp3");
            }
        }
        for(int j = 0; j < m_enemies.size(); j++){
            if(collRectRect(m_bullets[i] -> m_objRect, m_enemies[j] -> m_objectRect)){
                m_enemies[j] -> m_health -= m_bullets[i] -> m_damage;
                m_bullets[i] -> m_health --;
                m_soundManager->play("Mine.mp3");
            }
        }
    }
    for(int i = 0; i < m_enemyBullets.size(); i++)
    {
        buffBool = true;
        if(collisionWithShip(m_enemyBullets[i] -> m_objectRect)){
            delete m_enemyBullets[i];
            m_enemyBullets.erase(m_enemyBullets.begin() + i);
            i --;
            buffBool = false;
        }
        for(int j = 0; j < m_players.size() && buffBool; j ++)
        {
            if(collRectRect(m_enemyBullets[i] -> m_objectRect, m_players[j] -> m_objRect))
            {
                m_players[j] -> m_health -= m_enemyBullets[i] -> m_damage;
                delete m_enemyBullets[i];
                m_enemyBullets.erase(m_enemyBullets.begin() + i);
                i --;
                buffBool = false;
            }
        }
        if(buffBool)
        {
            if(checkInOffBounds(m_enemyBullets[i] -> m_objectRect, m_backgroundRect.w, m_backgroundRect.h))
            {
                buffBool = false;
                delete m_enemyBullets[i];
                m_enemyBullets.erase(m_enemyBullets.begin() + i);
                i --;
            }
        }
        if(buffBool)
        {
            for(int j = 0; j < m_ores.size(); j++){
                if(collRectRect(m_enemyBullets[i] -> m_objectRect, m_ores[j] -> m_rect)){
                    delete m_enemyBullets[i];
                    m_enemyBullets.erase(m_enemyBullets.begin() + i);
                    i --;
                    buffBool = false;
                    break;
                }
            }
        }
    }
}

bool World::checkForPause()
{
    const Uint8 *state = SDL_GetKeyboardState(NULL);
    SDL_PollEvent(&(m_event));

    if(state[SDL_SCANCODE_ESCAPE] && !m_isPaused)
    {
        m_isPaused = true;
        return true;
    }else if(m_mouseIsPressed && (MouseIsInRect(m_mouseCoordinates, resumeButton.objRect)) && m_isPaused)
    {
        m_isPaused = false;
        return false;
    }
    if(m_mouseIsPressed && (MouseIsInRect(m_mouseCoordinates, exitButton.objRect)))
    {
        m_quitScene = true;
        m_gameState = MENU;
    }
}

void World::drawShipCollision()
{
	line a;
	for (int i = 0; i < m_collLines.size(); i++)
	{
		a = m_collLines[i];
		SDL_RenderDrawLine(m_main_renderer, (int)(m_camera.zoom_lvl * (float)(a.start.x - m_camera.camera_rect.x)), (int)(m_camera.zoom_lvl * (float)(a.start.y - m_camera.camera_rect.y)), (int)(m_camera.zoom_lvl * (float)(a.finish.x - m_camera.camera_rect.x)), (int)(m_camera.zoom_lvl * (float)(a.finish.y - m_camera.camera_rect.y)));
	}
}
