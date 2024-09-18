#include "Game.h"

void Game::initialize()
{
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Martian Invasion");
    //frame rate == monitor refresh to prevent tearing
    window->setVerticalSyncEnabled(true);
    // window->setKeyRepeatEnabled(false);
    
    //create player
    player = new Player();
    
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
                    // std::cout << "Key A Pressed!" << std::endl;
                    player->sprite.setTextureRect(sf::IntRect(31,0,30,32));
                    // std::cout << player->getSprite().getTextureRect().left << std::endl;
                    // std::cout << player->getSprite().getTextureRect().top << std::endl;
                    // std::cout << player->getSprite().getTextureRect().width << std::endl;
                    // std::cout << player->getSprite().getTextureRect().height << std::endl;
                }
                else if(event.key.code == sf::Keyboard::D){
                    player->getSprite().setTextureRect(sf::IntRect(92,0,29,32));
                };
            
            case sf::Event::KeyReleased:
                if(event.key.code == sf::Keyboard::A){
                    // std::cout << "Key A Released" << std::endl;
                    player->getSprite().setTextureRect(sf::IntRect(59,0,30,32));
                }
                else if(event.key.code == sf::Keyboard::D){
                    player->getSprite().setTextureRect(sf::IntRect(59,0,30,32));
                };

            default:
                break;
        }
    }   

    //smooth movement with keyboard
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        //character.move(-1, 0);
        player->getSprite().move(-1,0);
        player->getSprite().setTextureRect(sf::IntRect(31,0,30,32));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //character.move(1, 0);
        player->getSprite().move(1,0);
        player->getSprite().setTextureRect(sf::IntRect(92,0,29,32));
        
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //character.move(0, -1);
        player->getSprite().move(0,-1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //character.move(0, 1);
        player->getSprite().move(0,1);
    }

    //SHOOT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        //character.shoot();
        // bullets.push_back(player->shoot());
    }

}

void Game::update()
{
    //create new enemies
    float timeElapsed = enemySeedClock.getElapsedTime().asSeconds();
    if(timeElapsed >=1.f){
        createEnemies();
        enemySeedClock.restart();
    };

    //update Enemy Position
    for(std::vector<Enemy*>::iterator it= enemies.begin(); it != enemies.end();){
        Enemy* enemy = *it;
        enemy->updatePosition(dt);
        if(enemy->getPosition().y > window->getSize().y){
            enemy->destroy();
            enemies.erase(it);
        }
        else{
            it++;
        }
    }

    // update bullet position
     for(auto it = bullets.begin(); it !=bullets.end();){
        Bullet* bullet = *it;
        bullet->updatePosition();
        if(bullet->getPosition().y > window->getSize().y){
            bullet->destroy();
            bullets.erase(it);
        }
        else{
            it++;
        }
    }

    //update enemy collisions
    for(Enemy* enemy: enemies){
        enemy->collides(bullets);
        enemy->collides(player, window);
    }

    for(Bullet* bullet: bullets){
        bullet->collides(enemies);
    }
    
    //erase(remove_if position>y || health <= 0);

    //update player
        //updateHealth();
            //if needed calls destroy();
    player->collides(enemies);
}

void Game::render()
{
    window->clear(sf::Color::Black);
    
    //Render
    for(Enemy* enemy: enemies){
        window->draw(enemy->getSprite());
    }

    // for(bullet bullet: bullets){
    //     // window.draw(bullet)
    // }

    window->draw(player->getSprite());

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

