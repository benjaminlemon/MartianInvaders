#include "Game.h"

void Game::initialize()
{
    window = new sf::RenderWindow(sf::VideoMode(800,600), "Martian Invasion");
    //frame rate == monitor refresh to prevent tearing
    window->setVerticalSyncEnabled(true);

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
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D)||sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        //character.move(1, 0);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::W)||sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        //character.move(0, 1);
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::S)||sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        //character.move(0, -1);
    }

    //SHOOT
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
    {
        //character.shoot();
    }

}

void Game::update()
{
    //Update
    window->clear(sf::Color::Black);
    // createEnemies();

    //update Enemy
    for(std::vector<Enemy*>::iterator it= enemies.begin(); it != enemies.end(); it++){
        (*it)->updatePosition();
        if((*it)->getPosition().y > 600){
            (*it)->destroy();
            enemies.erase(it);
            it--;
        }
        //*iterator->updateHealth();


    }
    // for(Enemy* enemy: enemies){
    //     enemy->updatePosition();
    //     // enemy->updateHealth();
    // }

    // update bullet location
    //  for(bullet bullet: bullets){
    //      bullet.updatePosition()
    //  }

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

    //window.draw(player);

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

