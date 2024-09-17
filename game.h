#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include "Enemy.h"
#include "Bullet.h"

class Game{
    private:
        // std::vector<bullet> bullets = {};
        std::vector<Enemy*> enemies = {};
        sf::Clock gameClock;
        sf::RenderWindow* window = nullptr;
        sf::Event event;

        //Functions
        void initialize();
        void createEnemies();
        void processEvents();
        void update();
        void render();
    
    public:
        //constructor
        Game();

        void run();
};

#endif