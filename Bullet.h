#ifndef BULLET_H
#define BULLET_H
#include <SFML/Graphics.hpp>
#include "Player.h"
#include "Enemy.h"

class Enemy;

class Player;
class Bullet{
    private:
        int dmg;
        int speed;
        sf::RectangleShape shape;
        sf::Vector2f position;
        bool markedToDestroy;

    public:
//        Bullet(Player &player);
        Bullet(sf::Vector2f playerPosition);
        int getDmg(){return dmg;};
        void updatePosition();
        sf::Vector2f getPosition(){return position;};
        sf::RectangleShape getShape(){return shape;};
        void collides(const std::vector<Enemy*> &enemies);
        void destroy();
};

#endif
