#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include <SFML/Window/VideoMode.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <SFML/System/Clock.hpp>
#include <SFML/System/Time.hpp>
#include <SFML/Audio.hpp>
#include <vector> 
#include <algorithm>
#include "Enemy.h"
#include "Bullet.h"
#include "Player.h"
#include "GameState.h"
#include "GameRunState.h"

class Game{
    private:

        //Functions
        void initialize();
        void initializeFont();
    
    public:
        sf::Clock gameClock;
        sf::RenderWindow* window = nullptr;
        sf::Font font;
        GameRunState* currentState;
        //constructor
        Game();
};

#endif
