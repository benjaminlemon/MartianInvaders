#ifndef BULLET_H
#define BULLET_H
#include "Player.h"
#include <SFML/Graphics.hpp>

class Bullet{
    private:
        int dmg;
        int speed;
        sf::RectangleShape shape;
        sf::Vector2f position;

    public:
        Bullet(Player &player);
        int getDmg(){return dmg;};
        void updatePosition(){};
        sf::Vector2f getPosition(){return position;};
        sf::RectangleShape getShape(){return shape;};
        void destroy(){};
};

#endif