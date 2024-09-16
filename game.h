#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "enemy.h"
#include "bullet.h"

class Game{
    private:
        std::vector<Enemy*> enemies = {};
        // std::vector<bullet> bullets = {};
        sf::RenderWindow* window = nullptr;
        sf::Event event;
        void initialize();
        void createEnemies();
        void processEvents();
        void update();
        void render();
    
    public:
        Game();
        void run();
};

#endif