#include "Game.h"

void Game::initialize()
{
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Martian Invasion");
    //frame rate == monitor refresh to prevent tearing
    window->setVerticalSyncEnabled(true);
    // window->setKeyRepeatEnabled(false);

    WINDOW_WIDTH = window->getSize().x;
    WINDOW_HEIGHT = window->getSize().y;

    
    //create player
    player = new Player();

    initializeTexture("resources/textures/backgroundSpace.png");
    intializeSprite();
    initializeEndGameMenu();
    initializeFont();
    initializeEndGameMenuText();
    initializeGameText();
    initializeSounds();
    createEnemies();
}

void Game::createEnemies()
{
    Enemy* enemy = new Enemy(window->getSize().x);
    enemies.push_back(enemy);
}

void Game::processEvents()
{
    while(window->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                break;
            
            case sf::Event::KeyPressed:
                if(event.key.scancode == sf::Keyboard::Scan::A){
                    player->getSprite().setTextureRect(sf::IntRect(31,0,30,32));
                }
                else if(event.key.scancode == sf::Keyboard::Scan::D){
                    player->getSprite().setTextureRect(sf::IntRect(92,0,29,32));
                }
                break;
            
            case sf::Event::KeyReleased:
                if(event.key.scancode == sf::Keyboard::Scan::A || event.key.scancode == sf::Keyboard::Scan::D){
                    player->getSprite().setTextureRect(sf::IntRect(59,0,30,32));
                }
                break;

            case sf::Event::MouseButtonPressed:
                if(event.mouseButton.button == sf::Mouse::Left && gameOver){
                    float x = event.mouseButton.x;
                    float y = event.mouseButton.y;

                    if(textExit.getGlobalBounds().contains(x, y)){
                        window->close();
                    }

                    if(textRestart.getGlobalBounds().contains(x,y)){
                        restart();
                    }
                    
                }

            default:
                break;
        }
    }   

    //smooth movement with keyboard
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player->move(window->getSize().x,window->getSize().y,-1,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player->move(window->getSize().x,window->getSize().y,1,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player->move(window->getSize().x,window->getSize().y,0,-1);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player->move(window->getSize().x,window->getSize().y,0,1);
    }

    //SHOOT
    float fireRateTime = fireRate.getElapsedTime().asSeconds();
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        
        if(fireRateTime >=.25f){
            Bullet* bullet = new Bullet(player->getPosition());

            bullets.push_back(bullet);
            pewPew.play();
            fireRate.restart();
        }
    }

}

void Game::update()
{
    updateBackground();

    //create new enemies
    float timeElapsed = enemySeedClock.getElapsedTime().asSeconds();
    if(timeElapsed >=1.f){
        createEnemies();
        enemySeedClock.restart();
    };

    //update Enemy Position
    for(Enemy* enemy:enemies){
        enemy->updatePosition(dt, WINDOW_HEIGHT, enemyScore);
    }

    // update bullet position
     for(Bullet* bullet:bullets){
        bullet->updatePosition(dt);
    }

    //update enemy collisions
    for(Enemy* enemy: enemies){
        enemy->collides(bullets, score);
        enemy->collides(player);
    }

    //update bullet collisions
    for(Bullet* bullet: bullets){
        bullet->collides(enemies);
    }

    player->collides(enemies);
    
    //clean up all dead enemies
    auto deadEnemyIteratorBegin = std::remove_if(enemies.begin(), enemies.end(),
     [](Enemy* enemy){
        return enemy->markedToDestroy;
     });

    for(Enemy* enemy: enemies){
        if(enemy->markedToDestroy){
            enemy->destroy();
        }
    }

    enemies.erase(deadEnemyIteratorBegin, enemies.end());

    for(auto it = bullets.begin(); it != bullets.end();){
        if((*it)->markedToDestroy){
            delete *it;
            it = bullets.erase(it);
        }
        else{
            it++;
        }
    }

    if(player->isDead || enemyScore == 10){
        gameOver = true;
    }

    //update onscreen text
    textScore.setString("Score: " + std::to_string(score));
    textEnemyScore.setString("Earths Health: " + std::to_string(10-enemyScore));
    textHighScore.setString("High Score: " + std::to_string(score));
        
}

void Game::render()
{
    window->clear(sf::Color::Black);
    
    //Render
    renderBackground();

    for(Enemy* enemy: enemies){
        window->draw(enemy->getSprite());
    }

     for(Bullet* bullet: bullets){
         
         window->draw(bullet->getSprite());
     }
    
    window->draw(player->getSprite());

    window->draw(textScore);
    window->draw(textEnemyScore);



    if(gameOver){
        window->draw(endGameMenu);
        window->draw(textHighScore);
        window->draw(restartOption);
        window->draw(exitOption);
        window->draw(textExit);
        window->draw(textRestart);
        music.stop();
    }
    window->display();
    
    
}

Game::Game()
{
    initialize();
}

void Game::run()
{
    while(window->isOpen()){
        dt = gameClock.getElapsedTime().asSeconds();
        gameClock.restart();
        processEvents();
        update();
        render();
    }
}

void Game::initializeTexture(std::string filepath)
{
    if(!backgroundTexture.loadFromFile(filepath)){
        std::cerr << "Background did not load!" << std::endl;
    }

    backgroundTexture.setSmooth(true);
}

void Game::intializeSprite()
{
    background1.setTexture(backgroundTexture);
    background2.setTexture(backgroundTexture);

    float scaleFactorX = WINDOW_WIDTH/backgroundTexture.getSize().x;
    float scaleFactorY = WINDOW_HEIGHT/backgroundTexture.getSize().y;
    background1.setScale(scaleFactorX, scaleFactorY);
    background2.setScale(scaleFactorX, scaleFactorY);

    background2.setPosition(0.f, 0-WINDOW_HEIGHT);
}

void Game::updateBackground()
{
    float dt = backgroundClock.getElapsedTime().asSeconds();

    background1.move(0.f, dt*20.f);
    background2.move(0.f, dt*20.f);

    if(background1.getPosition().y > WINDOW_HEIGHT){
        background1.setPosition(0.f, 0.f - WINDOW_HEIGHT);
    }
    
    if(background2.getPosition().y > WINDOW_HEIGHT){
        background2.setPosition(0.f, 0.f - WINDOW_HEIGHT);
    }

    backgroundClock.restart();

}

void Game::renderBackground()
{
    window->draw(background1);
    window->draw(background2);
}

void Game::initializeEndGameMenu()
{
    float endGameMenuScale = .875f;
    float endGameMenuPosX = (WINDOW_WIDTH*(1-endGameMenuScale)/2.f);
    float endGameMenuPosY = (WINDOW_HEIGHT*(1-endGameMenuScale)/2.f);

    sf::Vector2f endGameMenuPosition = sf::Vector2f(endGameMenuPosX, endGameMenuPosY);

    //End Game Menu
    endGameMenu = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH*endGameMenuScale, WINDOW_HEIGHT*endGameMenuScale));
    endGameMenu.setFillColor(sf::Color::Black);
    endGameMenu.setPosition(endGameMenuPosition);

    //Restart
    restartOption = sf::RectangleShape(sf::Vector2f(endGameMenu.getSize().x, endGameMenu.getSize().y));
    restartOption.setScale(1.f,.25f);
    restartOption.setFillColor(sf::Color::Black);
    restartOption.setPosition(endGameMenuPosition.x, .5*WINDOW_HEIGHT);

    //Exit 
    float exitOptionPositionY = .5*WINDOW_HEIGHT + .25*endGameMenu.getSize().y;

    exitOption = sf::RectangleShape(sf::Vector2f(endGameMenu.getSize().x, endGameMenu.getSize().y));
    exitOption.setScale(1.f, .25f);
    exitOption.setFillColor(sf::Color::Black);
    exitOption.setPosition(endGameMenuPosition.x, exitOptionPositionY);

}

void Game::initializeFont()
{
    if (!font.loadFromFile("resources/fonts/PixelifySans-Regular.ttf"))
    {
        std::cerr << "Font did not load!" << std::endl;
    }
}

void Game::initializeEndGameMenuText()
{
    float endGameMenuScale = .875f;
    float endGameMenuPosX = (WINDOW_WIDTH*(1-endGameMenuScale)/2.f);
    float endGameMenuPosY = (WINDOW_HEIGHT*(1-endGameMenuScale)/2.f);

    sf::Vector2f endGameMenuPosition = sf::Vector2f(endGameMenuPosX, endGameMenuPosY);

    textRestart.setFont(font);
    textExit.setFont(font);
    textHighScore.setFont(font);


    textExit.setString("Exit");
    textRestart.setString("Restart");
    textHighScore.setString("High Score!  ");

    // set the character size
    textExit.setCharacterSize(75);
    textRestart.setCharacterSize(75);
    textHighScore.setCharacterSize(75);

    // set the color
    textExit.setFillColor(sf::Color::White);
    textRestart.setFillColor(sf::Color::White);
    textHighScore.setFillColor(sf::Color::White);

    // set the text style
    textExit.setStyle(sf::Text::Bold);
    textRestart.setStyle(sf::Text::Bold);
    textHighScore.setStyle(sf::Text::Bold);

    float exitOptionPositionY = .5*WINDOW_HEIGHT + .25*endGameMenu.getSize().y;

    // float exitOptionPositionY = .5*WINDOW_HEIGHT;

    textExit.setPosition(WINDOW_WIDTH/2 - (textExit.getGlobalBounds().width/2), exitOptionPositionY);

    textRestart.setPosition(WINDOW_WIDTH/2 -(textRestart.getGlobalBounds().width/2), .5*WINDOW_HEIGHT);

    textHighScore.setPosition(WINDOW_WIDTH/2 -(textHighScore.getGlobalBounds().width/2), .25*WINDOW_HEIGHT);
}

void Game::initializeGameText()
{
    textScore.setFont(font);
    textEnemyScore.setFont(font);

    textScore.setString("Score: ");
    textEnemyScore.setString("Earth's Health: ");

    textScore.setCharacterSize(25);
    textEnemyScore.setCharacterSize(25);

    textScore.setStyle(sf::Text::Bold);
    textEnemyScore.setStyle(sf::Text::Bold);

    textScore.setPosition(0,0);
    textEnemyScore.setPosition(0, textScore.getGlobalBounds().height + 10);
}

void Game::initializeSounds()
{
    if (!music.openFromFile("resources/sounds/backgroundMusic.ogg")){
        std::cerr << "Music not loaded" << std::endl; // error
    }

    music.play();

     if (!soundBuffer.loadFromFile("resources/sounds/pewpew_1.wav")){
        std::cerr << "Sound not loaded" << std::endl;
     }

     pewPew.setBuffer(soundBuffer);
}

void Game::restart()
{
    //scores
    score = 0;
    enemyScore = 0;
    gameOver = false;

    //enemies
    for(Enemy* enemy:enemies){
        enemy->destroy();
    }
    enemies.erase(enemies.begin(), enemies.end());

    //bullets
    for(Bullet* bullet:bullets){
        bullet->destroy();
    }
    bullets.erase(bullets.begin(), bullets.end());

    //player
    player->isDead = false;
    player->getSprite().setPosition(400.f, 500.f);

    //music
    music.play();
}