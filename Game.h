#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <vector> 
#include <algorithm>
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"

class Player;
class Bullet;
class Enemy;

class Game{
    private:
        std::vector<Bullet*> bullets;
        std::vector<Enemy*> enemies;
        Player* player;
        sf::Clock gameClock;
        sf::Clock enemySeedClock;
        sf::RenderWindow* window = nullptr;
        sf::Event event;

        //Functions
        void initialize();
        void createEnemies();
        void processEvents();
        void update();
        void render();
    
    public:
        float dt = 0;
        //constructor
        Game();
        void run();
};

#endif
