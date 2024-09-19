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

            default:
                break;
        }
    }   

    //smooth movement with keyboard
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        player->move(window->getSize().x,-1,0);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        player->move(window->getSize().x,1,0);        
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        player->move(window->getSize().y,0,-1);
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        player->move(window->getSize().y,0,1);
    }

    //SHOOT
    float fireRateTime = fireRate.getElapsedTime().asSeconds();
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        
        if(fireRateTime >=.25f){
            Bullet* bullet = new Bullet(player->getPosition());

            bullets.push_back(bullet);
            fireRate.restart();
        }
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
    for(Enemy* enemy:enemies){
        enemy->updatePosition(dt, WINDOW_HEIGHT);
    }

    // update bullet position
     for(Bullet* bullet:bullets){
        bullet->updatePosition(dt);
    }

    //update enemy collisions
    for(Enemy* enemy: enemies){
        enemy->collides(bullets);
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
    
}

void Game::render()
{
    window->clear(sf::Color::Black);
    
    //Render
    for(Enemy* enemy: enemies){
        window->draw(enemy->getSprite());
    }

     for(Bullet* bullet: bullets){
         
         window->draw(bullet->getSprite());
     }
    
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

