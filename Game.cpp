#include "Game.h"

void Game::initialize()
{
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Martian Invasion");
    //frame rate == monitor refresh to prevent tearing
    window->setVerticalSyncEnabled(true);
    
    //create player
    player = new Player();
    
    createEnemies();
}

void Game::createEnemies()
{
    Enemy* enemy = new Enemy();
    enemies.push_back(enemy);
}

void Game::processEvents()
{
    while(window->pollEvent(event)){
        switch(event.type){
            case sf::Event::Closed:
                window->close();
                break;

            default:
                break;
        }
    }   

    //smooth movement with keyboard
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A)||sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        //character.move(-1, 0);
        player->move(-1,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //character.move(1, 0);
        player->move(1,0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //character.move(0, -1);
        player->move(0,-1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //character.move(0, 1);
        player->move(0,1);
    }

    //SHOOT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        //character.shoot();
    }

}

void Game::update()
{
    //create new enemies
    window->clear(sf::Color::Black);
    // sf::Time time = gameClock.getElapsedTime();
    float timeElapsed = gameClock.getElapsedTime().asSeconds();
    if(timeElapsed >=1.f){
        createEnemies();
        gameClock.restart();
    };

    //update Enemy Position
    for(std::vector<Enemy*>::iterator it= enemies.begin(); it != enemies.end();){
        Enemy* enemy = *it;
        enemy->updatePosition();
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
        enemy->collides(player);
    }

    for(Bullet* bullet: bullets){
        bullet->collides(enemies);
    }
    
    //erase(remove_if position>y || health <= 0);

    //update player
        //updateHealth();
            //if needed calls destroy();
}

void Game::render()
{

    //Render
    for(Enemy* enemy: enemies){
        window->draw(enemy->shape);
    }

    // for(bullet bullet: bullets){
    //     // window.draw(bullet)
    // }

    window->draw(player->shape);

    window->display();
}

Game::Game()
{
    initialize();
}

void Game::run()
{
    while(window->isOpen()){
        processEvents();
        update();
        render();
    }
}

