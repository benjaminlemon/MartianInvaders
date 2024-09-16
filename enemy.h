#ifndef ENEMY_H
#define ENEMY_H

#include <SFML/Graphics/VertexArray.hpp>
#include <SFML/Graphics.hpp>

class enemy{
    private:
        int health, speed;
        int position[2];
        sf::RectangleShape shape;
    public:
        enemy();
        enemy(int health, int speed, int position[2], sf::RectangleShape shape);
        void updatePosition();
        void updateHealth();
        void destroy();
        sf::RectangleShape getShape()const;
};

#endif