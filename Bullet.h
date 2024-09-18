#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
<<<<<<< Updated upstream
#include "Player.h"
#include "Enemy.h"

class Enemy;
=======
#include <iostream>
>>>>>>> Stashed changes

class Player;
class Bullet{
    private:
        int dmg;
        int speed;
        sf::RectangleShape shape;
        sf::Vector2f position;
        bool markedForRemoval;

    public:
        Bullet(Player &player);
        int getDmg(){return dmg;};
        void updatePosition();
        sf::Vector2f getPosition(){return position;};
        sf::RectangleShape getShape(){return shape;};
        void collides(const std::vector<Enemy*> &enemies);
        void destroy();
};

#endif
