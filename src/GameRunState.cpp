#include "GameRunState.h"

void GameRunState::setWindowDimensions(float windowWidth, float windowHeight){this->windowHeight = windowHeight; this->windowWidth = windowWidth;}; 

void GameRunState::setFont(sf::Font font){this->font = font;};

void GameRunState::initializeBackGround()
{
    //Texture
    if(!backgroundTexture.loadFromFile("../resources/textures/backgroundSpace.png")){
        std::cerr << "Background did not load!" << std::endl;
    }

    backgroundTexture.setSmooth(true);

    //Sprites
    background1.setTexture(backgroundTexture);
    background2.setTexture(backgroundTexture);

    float scaleFactorX = windowWidth/backgroundTexture.getSize().x;
    float scaleFactorY = windowHeight/backgroundTexture.getSize().y;
    background1.setScale(scaleFactorX, scaleFactorY);
    background2.setScale(scaleFactorX, scaleFactorY);

    background2.setPosition(0.f, 0-windowHeight);
}

void GameRunState::initializeGameScreenText()
{
    scoreText.setFont(font);
    playerHealthDisplayText.setFont(font);

    scoreText.setString("Score: ");
    playerHealthDisplayText.setString("Health: ");

    scoreText.setCharacterSize(25);
    playerHealthDisplayText.setCharacterSize(25);

    scoreText.setStyle(sf::Text::Bold);
    playerHealthDisplayText.setStyle(sf::Text::Bold);

    scoreText.setPosition(0,0);
    playerHealthDisplayText.setPosition(0, scoreText.getGlobalBounds().height + 10);
}

void GameRunState::initializeMusic()
{
    if (!backgroundMusic.openFromFile("../resources/sounds/backgroundMusic.ogg")){
    std::cerr << "Music not loaded" << std::endl;
    }
}

void GameRunState::spawnEnemies()
{
    Enemy* enemy = new Enemy(windowWidth);
    enemies.push_back(enemy);
}

void GameRunState::updateBackground(float deltaTime)
{
    background1.move(0.f, deltaTime*20.f);
    background2.move(0.f, deltaTime*20.f);

    if(background1.getPosition().y > windowHeight){
        background1.setPosition(0.f, 0.f - windowHeight);
    }
    
    if(background2.getPosition().y > windowHeight){
        background2.setPosition(0.f, 0.f - windowHeight);
    }

    backgroundClock.restart();
};

void GameRunState::initializeState(sf::RenderWindow* window, sf::Font font){
    setWindowDimensions(window->getSize().x, window->getSize().y);

    setFont(font);

    initializeBackGround();

    initializeGameScreenText();

    initializeMusic();

    //init game objs
    player = new Player();
    spawnEnemies();
};

void GameRunState::handleInput(sf::RenderWindow* window){
    sf::Event event;

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

            default:
                break;
        }
    }   

    //smooth movement with keyboard
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A))
    {
        player->move(windowWidth,windowHeight,-1,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D))
    {
        player->move(windowWidth,windowHeight,1,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W))
    {
        player->move(windowWidth,windowHeight,0,-1);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S))
    {
        player->move(windowWidth,windowHeight,0,1);
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        bullets.push_back(player->shoot());
    }
};

void GameRunState::update(float deltaTime){
    updateBackground(deltaTime);

    //update enemies
    float timeElapsed = enemySpawnClock.getElapsedTime().asSeconds();
    if(timeElapsed >= 1.f){
        spawnEnemies();
        enemySpawnClock.restart();
    }

    for(Enemy* enemy:enemies){
        enemy->updatePosition(deltaTime, windowHeight);
    }

    //update bullet position
    for(Bullet* bullet:bullets){
        bullet->updatePosition(deltaTime);
    }

    //update bullet collisions
    for(Bullet* bullet: bullets){
        bullet->collides(enemies);
    }

    //player collisions
    player->collides(enemies);
    
    //clean up all dead enemies
    for(auto it = enemies.begin(); it != enemies.end();){
        if((*it)->markedToDestroy){
            delete *it;
            it = enemies.erase(it);
        }
        else{
            it++;
        }
    }

    //clean up all stray bullets
    for(auto it = bullets.begin(); it != bullets.end();){
        if((*it)->markedToDestroy){
            delete *it;
            it = bullets.erase(it);
        }
        else{
            it++;
        }
    }

    //update onscreen text
    scoreText.setString("Score: " + std::to_string(score));

    //change gamestate!
    if(player->isDead){
        gameOver = true;
    }
};

void GameRunState::render(sf::RenderWindow* window){
    window->clear(sf::Color::Black);

    //Render
    window->draw(background1);
    window->draw(background2);

    for(Enemy* enemy: enemies){
        window->draw(enemy->getSprite());
    }

    for(Bullet* bullet: bullets){
        
        window->draw(bullet->getSprite());
    }
    
    window->draw(player->getSprite());

    window->draw(scoreText);
};

GameRunState::GameRunState(sf::RenderWindow* window, sf::Font font){
    initializeState(window, font);
}