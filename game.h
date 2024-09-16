#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Keyboard.hpp>
#include "enemy.h"
#include "bullet.h"

class Game{
    //private:
    std::vector<enemy> enemies = {};
    std::vector<bullet> bullets = {};
    void run();
    
    /**
     * Add enemies to game environment
     */
    void createEnemies();
};

#endif