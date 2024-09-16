#include "game.h"

void Game::run()
{
    std::vector<sf::VideoMode> modes = sf::VideoMode::getFullscreenModes();
    sf::VideoMode fullScreen = modes[0];
    sf::RenderWindow window(fullScreen, "Martian Invasion");
    //frame rate == monitor refresh to prevent tearing
    window.setVerticalSyncEnabled(true);

    while(window.isOpen()){
        //PROCESS EVENTS
        sf::Event event;
        while(window.pollEvent(event)){
            switch(event.type){
                case sf::Event::Closed:
                    window.close();
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

    //Update
    window.clear();
    //update NPC location
    createEnemies();
    for(enemy enemy: enemies){
        enemy.updatePosition();
        enemy.updateHealth();
    }

    //update bullet location
    for(bullet bullet: bullets){
        bullet.updatePosition();
    }

    //update player
        //updateHealth();
            //if needed calls destroy();
    
    //Render
    for(enemy enemy: enemies){
        window.draw(enemy.getShape());
    }

    for(bullet bullet: bullets){
        // window.draw(bullet)
    }

}

